#include<cstdlib>
#include<signal.h>
#include "simulator.h"
#include<thread>
#include <cstdlib>
#include<iostream>
#include <ctime>
using namespace std;

LogSimulator::LogSimulator(string &filename)
{
        file.open(filename,fstream::in | fstream::out | fstream::app);
}
LogSimulator::LogSimulator()
{
 //       file.close();
}
LogSimulator::~LogSimulator()
{
        file.close();
}
string LogSimulator::randomLevel(vector<string> &v)
{
        int r = rand();
        int i = r % v.size();
        return v[i];
}
string LogSimulator::randoMsg(){

        int rand1 = rand();
        if(rand1%2==0)
        {
                return ("[main] org.apache.hadoop.mapreduce.v2.app.MRAppMaster: Using var= mapred newApiCommitter.");
        }
        else if(rand1%3==0)
        {

                return ("[LeaseRenewer:msrabi@msra-sa-41:9000] org.apache.hadoop.hdfs.LeaseRenewer: Failed to renew lease");
        }
        return ("[RMCommunicator Allocator] org.apache.hadoop.mapreduce.v2.app.rm.RMContainerAllocator: IN CONTACTING RM");
}
int LogSimulator::randomTimeStamp(vector<string> &v)
{
        int r = rand();
        int i = r % v.size();
        //return v[i];
        cout<<"data of i ::"<<i<<endl;
        //string op = currenttimeTotimeformat(i);
        return i;
}
vector<string> LogSimulator::setLevel(vector<vector<string>> &logLevels, int &findex)
{
        vector<string> temp;
        if(findex%2)
        {
                for(int i=0; i<logLevels[0].size(); i++)
                {
                        temp.push_back(logLevels[0][i]);
                }
                return temp;
        }
        else
        {
                for(int i=0;i< logLevels[1].size(); i++)
                {
                        temp.push_back(logLevels[1][i]);
                }
                return temp;
        }
}

void LogSimulator::simulateLogFile(vector<string> &timeStampFormats,vector<vector<string>> &logLevels, int &findex)
{
        //string timestamp = randomTimeStamp(timeStampFormats);
        vector<string> vec_Level =  setLevel(logLevels,findex);
        if(findex <timeStampFormats.size())
        {       file <<currenttimeTotimeformat(findex) <<"  " <<randomLevel(vec_Level)<<"  "<<randoMsg()<<endl;
                cout <<currenttimeTotimeformat(findex) <<"  " <<randomLevel(vec_Level)<<"  "<<randoMsg()<<endl;
                this_thread::sleep_for(chrono::milliseconds(500));
        }
        else
        {       int index = findex - timeStampFormats.size();
                //int index = randomTimeStamp(timeStampFormats);
                file <<currenttimeTotimeformat(index) <<"  " <<randomLevel(vec_Level)<<"  "<<randoMsg()<<endl;
                cout <<currenttimeTotimeformat(index) <<"  " <<randomLevel(vec_Level)<<"  "<<randoMsg()<<endl;
                this_thread::sleep_for(chrono::milliseconds(500));
        }
}
string LogSimulator::currenttimeTotimeformat(const int &index)
{
        time_t rawtime;
        struct tm * timeinfo;
        time(&rawtime);

        switch(index)
        {

                case 0: {       //Apache
                                const int size(sizeof("Sun Dec 04 04:47:44 2005"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%a %b %d %T %G",
                                                timeinfo);
                        //      cout <<string(buffer);
                                return string(buffer);
                        };
                case 1: {       //BGL
                                const int size(sizeof("2005-06-03-15.42.50.675872"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%G-%m-%d-%T.675872",
                                                timeinfo);
                                return string(buffer);
                        };
                 case 2: {       //HADOOP/ZOOKEEPER
                                const int size(sizeof("2015-10-18 18:01:47,978"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%G-%m-%d %T,978",
                                                timeinfo);
                                return string(buffer);
                        };
                case 3: {       //HEALTH APP
                                const int size(sizeof("20171223-22:15:29:606"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%G%m%d-%T:606",
                                                timeinfo);
                                return string(buffer);
                        };
                case 4: {       //MAC
                                const int size(sizeof("Jun 14 15:16:01"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%b %d %T",
                                                timeinfo);
                                return string(buffer);
                        };
                 case 5: {       //OpenStack
                                const int size(sizeof("2017-05-16_13:53:08"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%G-%m-%d_%T",
                                                timeinfo);
                                return string(buffer);
                        };
                case 6: {       //Proxifier
                                const int size(sizeof("10.30 16:49:06"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%m.%d %T",
                                                timeinfo);
                                 return string(buffer);
                        };
                case 7: {       //SPARX
                                const int size(sizeof("17/06/09 20:10:40"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%g/%m/%d %T",
                                                timeinfo);
                                return string(buffer);
                        };
                case 8: {       //WINDOWS
                                const int size(sizeof("2016/09/28 04:30:30"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%G/%m/%d %T",
                                                timeinfo);
                                return string(buffer);
                        };
                case 9: {       //2017-04-12 19:37:50
                                const int size(sizeof("2017-04-12 19:37:50"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%G-%m-%d %T",
                                                timeinfo);
                                return string(buffer);
                        };
                case 10: {       //ZOOKEEPER
                                const int size(sizeof("2015-07-29 17:41:44,747"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%G-%m-%d %T,747",
                                                timeinfo);
                                return string(buffer);
                        };
                case 11: {
                                const int size(sizeof("2018-08-20'T'13:20:10*633+0000"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%G-%m-%d\'T\'%T*633%z",
                                                timeinfo);
                                return string(buffer);
                        };
                case 12: {      //2017 Mar 03 05:12:41.211 PDT
                                const int size(sizeof("2017 Mar 03 05:12:41.211 PDT"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%G %b %d %T.211 %Z",
                                                timeinfo);
                                return string(buffer);
                        };
                case 13: {      //2017-10-14T22:11:20+0000
                                const int size(sizeof("2017-10-14T22:11:20+0000"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%G-%m-%dT%T%z",
                                                timeinfo);
                                return string(buffer);
                        };
                case 14: {      //2017-07-01T14:59:55.711'+0000'
                                const int size(sizeof("2017-07-01T14:59:55.711'+0000'"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%G-%m-%dT%T.711\'%z\'",
                                                timeinfo);
                                return string(buffer);
                        };
                case 15: {      //2017-07-01T14:59:55.711Z
                                const int size(sizeof("2017-07-01T14:59:55.711Z"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%G-%m-%dT%T.711%Z",
                                                timeinfo);
                                return string(buffer);
                        };
                case 16: {      //2017-08-19 12:17:55 -0400
                                const int size(sizeof("2017-08-19 12:17:55 -0400"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%G-%m-%d %T %z",
                                                timeinfo);
                                return string(buffer);
                        };
                case 17: {      //2017-08-19 12:17:55-0400
                                const int size(sizeof("2017-08-19 12:17:55 -0400"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%G-%m-%d %T%z",
                                                timeinfo);
                                return string(buffer);
                        };
                case 18: {      //2017/04/12*19:37:50
                                const int size(sizeof("2017/04/12*19:37:50"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%G/%m/%d*%T",
                                                timeinfo);
                                return string(buffer);
                        };
                case 19: {      //2018 Apr 13 22:08:13.211*PDT
                                const int size(sizeof("2018 Apr 13 22:08:13.211*PDT"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%G %b %d %T.211*%Z",
                                                timeinfo);
                                return string(buffer);
                        };
                case 20: {      //2017 Mar 10 01:44:20.392
                                const int size(sizeof("2017 Mar 10 01:44:20.392"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%G %b %d %T.211",
                                                timeinfo);
                                return string(buffer);
                        };
                 case 21: {      //2017-03-10 14:30:12,655+0000
                                const int size(sizeof("2017-03-10 14:30:12,655+0000"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%G-%m-%d %T,711%z",
                                                timeinfo);
                                return string(buffer);
                        };
                case 22: {      //2018-02-27 15:35:20.311
                                const int size(sizeof("2018-02-27 15:35:20.311"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%G-%m-%d %T.311",
                                                timeinfo);
                                return string(buffer);
                        };
                case 23: {      //2017-03-12 13:11:34.222-0700
                                const int size(sizeof("2017-03-12 13:11:34.222-0700"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%G-%m-%d %T.222%z",
                                                timeinfo);
                                return string(buffer);
                        };
                case 24: {      //2017-07-22'T'16:28:55.444
                                const int size(sizeof("2017-07-22'T'16:28:55.444"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%G-%m-%d\'T\'%T.444",
                                                timeinfo);
                                return string(buffer);
                        };
                case 25: {      //2017-09-08'T'03:13:10
                                const int size(sizeof("2017-09-08'T'03:13:10"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%G-%m-%d\'T\'%T",
                                                timeinfo);
                                return string(buffer);
                        };
                case 26: {      //2017-03-12'T'17:56:22'-0700'
                                const int size(sizeof("2017-03-12'T'17:56:22'-0700'"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%G-%m-%d\'T\'%T\'%z\'",
                                                timeinfo);
                                return string(buffer);
                        };
                case 27: {      //2017-10-30*02:47:33:899
                                const int size(sizeof("2017-10-30*02:47:33:899"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%G-%m-%d*%T:711",
                                                timeinfo);
                                return string(buffer);
                        };
                case 28: {      //2017-07-04*13:23:55
                                const int size(sizeof("2017-07-04*13:23:55"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%G-%m-%d*%T",
                                                timeinfo);
                                return string(buffer);
                        };
                case 29: {      //11-02-11 16:47:35,985 +0000
                                const int size(sizeof("11-02-11 16:47:35,985 +0000"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%g-%m-%d %T,985 %z",
                                                timeinfo);
                                return string(buffer);
                        };
                case 30: {      //10-06-26 02:31:29,573
                                const int size(sizeof("10-06-26 02:31:29,573"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                 "%g-%m-%d %T,985",
                                                timeinfo);
                                return string(buffer);
                        };
                case 31: {      //10-04-19 12:00:17
                                const int size(sizeof("10-04-19 12:00:17"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%g-%m-%d %T",
                                                timeinfo);
                                return string(buffer);
                        };
                case 32: {      //150423 11:42:35
                                const int size(sizeof("150423 11:42:35"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%g%m%d %T",
                                                timeinfo);
                                return string(buffer);
                        };
                case 33: {      //20150423 11:42:35.173
                                const int size(sizeof("20150423 11:42:35.173"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%G%m%d %T.173",
                                                timeinfo);
                                return string(buffer);
                        };
                case 34: {      //Dec 2, 2017 2:39:58 AM
                                const int size(sizeof("Dec 2, 2017 2:39:58 AM"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%b %d, %G %T %p",
                                                timeinfo);
                                return string(buffer);
                        };
                case 35: {      //Jun 09 2018 15:28:14
                                const int size(sizeof("Jun 09 2018 15:28:14"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%b %d %G %T",
                                                timeinfo);
                                return string(buffer);
                        };
                case 36: {      //08/10/11*13:33:56
                                const int size(sizeof("08/10/11*13:33:56"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%m/%d/%g*%T",
                                                timeinfo);
                                return string(buffer);
                        };
                case 37: {      //11/22/2017*05:13:11
                                const int size(sizeof("11/22/2017*05:13:11"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%m/%d/%G*%T",
                                                timeinfo);
                                return string(buffer);
                        };
                case 38: {      //05/09/2017*08:22:14*612
                                const int size(sizeof("05/09/2017*08:22:14*612"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%m/%d/%G*%T*612",
                                                timeinfo);
                                return string(buffer);
                        };
                case 39: {      //04/23/17 04:34:22 +0000
                                const int size(sizeof("04/23/17 04:34:22 +0000"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%m/%d/%g %T %z",
                                                timeinfo);
                                return string(buffer);
                        };
                 case 40: {      //10/03/2017 07:29:46 -0700
                                const int size(sizeof("10/03/2017 07:29:46 -0700"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%m/%d/%G %T %z",
                                                timeinfo);
                                return string(buffer);
                        };
                case 41: {      //8/5/2011 3:31:18 AM:234
                                const int size(sizeof("8/5/2011 3:31:18 AM:234"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%m/%d/%G %T %p:234",
                                                timeinfo);
                                return string(buffer);
                        };
                case 42: {      //9/28/2011 2:23:15 PM
                                const int size(sizeof("9/28/2011 2:23:15 PM"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%m/%d/%G %T %p",
                                                timeinfo);
                                return string(buffer);
                        };
                case 43: {      //19/Apr/2017:06:36:15 -0700
                                const int size(sizeof("19/Apr/2017:06:36:15 -0700"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%d/%b/%G:%T %z",
                                                timeinfo);
                                return string(buffer);
                        };
                case 44: {      //23/Apr 11:42:35,173
                                const int size(sizeof("23/Apr 11:42:35,173"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%d/%b %T,173",
                                                timeinfo);
                                return string(buffer);
                        };
                case 45: {      //23/Apr/2017:11:42:35
                                const int size(sizeof("23/Apr/2017:11:42:35"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%d/%b/%G:%T",
                                                timeinfo);
                                return string(buffer);
                        };
                case 46: {      //23/Apr/2017 11:42:35
                                const int size(sizeof("23/Apr/2017 11:42:35"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%d/%b/%G %T",
                                                timeinfo);
                                return string(buffer);
                        };
                case 47: {      //23-Apr-2017 11:42:35
                                const int size(sizeof("23-Apr-2017 11:42:35"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%d-%b-%G %T",
                                                timeinfo);
                                return string(buffer);
                        };
                case 48: {      //3-Apr-2017 11:42:35.883
                                const int size(sizeof("3-Apr-2017 11:42:35.883"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%d-%b-%G %T.883",
                                                timeinfo);
                                return string(buffer);
                        };
                case 49: {      //23 Apr 2017 11:42:35
                                const int size(sizeof("23 Apr 2017 11:42:35"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%d %b %G %T",
                                                timeinfo);
                                return string(buffer);
                        };
                case 50: {      //23 Apr 2017 10:32:35*311
                                const int size(sizeof("23 Apr 2017 10:32:35*311"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%d %b %G %T*311",
                                                timeinfo);
                                return string(buffer);
                        };
                case 51: {      //Jan 21 18:20:11 +0000 2017
                                const int size(sizeof("Jan 21 18:20:11 +0000 2017"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%b %d %T %z %G",
                                                timeinfo);
                                return string(buffer);
                        };
                case 52: {      //Apr 20 00:00:35 2010
                                const int size(sizeof("Apr 20 00:00:35 2010"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%b %d %T %G",
                                                timeinfo);
                                return string(buffer);
                        };
                case 53: {      //Sep 28 19:00:00 +0000
                                const int size(sizeof("Sep 28 19:00:00 +0000"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%b %d %T %z",
                                                timeinfo);
                                 return string(buffer);
                        };
                case 54: {      //0423_11:42:35
                                const int size(sizeof("0423_11:42:35"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%m%d_%T",
                                                timeinfo);
                                return string(buffer);
                        };
                case 55: {      //0423_11:42:35.883
                                const int size(sizeof("0423_11:42:35.883"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%m%d_%T.883",
                                                timeinfo);
                                return string(buffer);
                        };
                case 56: {      //11:42:35
                                const int size(sizeof("11:42:35"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%T",
                                                timeinfo);
                                return string(buffer);
                        };
                case 57: {      //11:42:35.173
                                const int size(sizeof("11:42:35.173"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%T.173",
                                                timeinfo);
                                return string(buffer);
                        };
                case 58: {      //11:42:35,173
                                const int size(sizeof("11:42:35,173"));
                                char buffer[size + 10];
                                timeinfo = localtime (&rawtime);
                                strftime (buffer, (size +10),
                                                "%T,173",
                                                timeinfo);
                                return string(buffer);
                        };

                default:{
                                cout<<"unknown format : "<<index<<endl;

                                return "default";
                        }
        }

}
