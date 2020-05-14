#include<iostream>
#include<thread>
#include<vector>
#include<regex>
#include "pattern.h"
using namespace std;
void identifyParser(string filename,string &ini)
{
    extern map<string,pair<string,string>>  matchedFormat;
    extern vector<string>parsedFiles;
    pair<string,string>timelevel;
    //cout<<ini<<endl;
    smatch match,match1;
    for(auto v:date)
    {
        if(regex_search(ini,match,regex(v,regex::icase)))
        {
            cout<<"matched: "<<match[0];
            //timelevel.first=v;
            if(regex_search(ini,match1,regex(level,regex::icase)))
            {
                cout<<match1[0];
                timelevel=make_pair(v,level);
                if(timelevel.first!="" && timelevel.second!="")
                {
                    matchedFormat[filename]=timelevel;
                    parsedFiles.push_back(filename);
                }
                break;
            }  
        } 
    }
}



