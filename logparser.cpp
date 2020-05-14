#include<iostream>
#include<string>
#include<map>
#include<unistd.h>
#include<fstream>
#include<sstream>
#include<thread>
#include<vector>
#include<dirent.h>
#include<cstring>
#include<sys/socket.h>
#include<mutex>
#include<jsoncpp/json/json.h>
#include "dateParse.cpp"
using namespace std;
using namespace std::chrono;
vector<string>parsedFiles;
map<string,pair<string,string>>  matchedFormat;
class logParser{
    public:
        map<string,string> confData;
        string conFileName;
        char hostname[256];
        logParser(const string &conFileName)
        {
            this->conFileName = conFileName;
            cout<<conFileName<<endl;
        }
        map<std::string, std::string> getData()
        {
            string s,key,val;
            ifstream ifs(conFileName);
            map<string,string> m;
            while(getline(ifs,s))
            {
                istringstream tokenStream(s);
                while(getline(getline(tokenStream,key,'=')>> ws,val))
                    m[key]=val;
            }
            return m;
        }
        vector<string> getFiles(string &s)
        {
            vector<string> filenames;
            DIR *dr;
            struct dirent *en;
            char *ptr;
            dr = opendir(s.c_str());
            if (dr) 
            {
                while ((en = readdir(dr))!=NULL) 
                {
                    string fname=s+"/"+string(en->d_name);
                    if ( !strcmp(en->d_name , "." ) || !strcmp(en->d_name , "..."   )||en->d_name[0]=='.') continue;
                    if((strtok(en->d_name,"."))!=NULL)
                    {
                        ptr=strtok(NULL,".");
                        if(ptr!=NULL && strcmp(ptr,"log")==0)
                            filenames.push_back(fname);
                            //cout<<fname<<endl;  
                    }
                }
            }
            return filenames;
        }
        void writeJson(const Json :: Value &val)
        {
            mutex writmut;
            cout<<"in write func"<<endl;
            ofstream file;
            file.open("jsonout.txt",ios::out|ios::app);
            const lock_guard<mutex> lock(writmut);
            file<<val<<endl;    
        }
        void parseLogFile(string fn,string datpat,string level)
        {
            string logline;
            ofstream file;
            file.open("jsonout.txt",ios::out|ios::app);
            //cout<<"inisde pasre for "<<fn<<endl; 
            int pos=0,flag=0;
            char dest[]="file";
            smatch match;
            string log;
            while(true)
            {
                flag=0;
                ifstream inp(fn);
                sleep(3);
                inp.seekg(pos);
                //cout<<"reading from pos"<<pos<<endl; 
                while(getline(inp,logline))
                {
                    flag=1;
                    Json::Value obj;
                    obj["hostname"]="megha";
                    obj["filename"]=fn;
                    if(regex_search(logline,match,regex(level,regex::icase)))
                        obj["loglevel"]=match.str(0);
                    cout<<match.str(0)<<endl;
                    int startpos=match.position(0)+(strlen(match.str(0).c_str()));
                    cout<<logline<<endl;
                    //cout<<logline<<endl<<startpos<<endl<<match.str(0)<<endl;
                    obj["Message"]=logline.substr(startpos);
                    if(!strcmp(confData["Log_sink"].c_str(),dest))
                        //file<<obj<<endl;
                        writeJson(obj);
                    else
                        cout<<"no destination found"<<endl;
                    pos=inp.tellg();

                }
                if(flag==0)
                {
                    cout<<"no more logs"<<endl;
                    sleep(3);
                }
                inp.close();
            }
        }      
};
int main()
{ 
    vector<string> filenames;
    logParser lp= logParser("config.conf");
    lp.confData=lp.getData(); 
    filenames=lp.getFiles(lp.confData.at("Log_files"));
    thread *fileThread;
    vector<thread> threads;
    for(string f:filenames)
    {
            string initial,logLine;
            ifstream fs(f);
            getline(fs,initial);
            fs.close();
            auto start = high_resolution_clock::now();
            identifyParser(f,initial);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<chrono::milliseconds>(stop - start);
            cout << "Time taken by function: "
            << duration.count() << "milliseconds" << endl;
    }
    for(auto f=matchedFormat.begin();f!=matchedFormat.end();f++)
    {
        //cout<<"filename: "<<f->first<<endl;
        threads.emplace_back(&logParser::parseLogFile,lp,f->first,f->second.first,f->second.second);
        

    }

    for(auto& t: threads)
    {
        t.join();
    }

    return 0;
}