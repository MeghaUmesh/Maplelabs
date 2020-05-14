#pragma once
#include<string>
#include<iostream>
#include<fstream>
#include<ctime>
#include<iomanip>
#include<chrono>
#include <unistd.h>
#include<vector>
#include<algorithm>
#define NUMOFTHREADS 5;
using namespace std;
class LogSimulator
{
        private:
                fstream file;

        public:
                LogSimulator(string &filename);
                LogSimulator();
                ~LogSimulator();
                //      void check_File_Type();
                //      void simulate_Hadoop_Log();
                void simulateLogFile(vector<string> &timeStampFormats,vector<vector<string>> &logLevels, int &findex);
                string randomLevel(vector<string> &v);
                string randoMsg();
                int randomTimeStamp(vector<string> &v);
                vector<string> setLevel(vector<vector<string>> &logLevels, int &findex);
                string currenttimeTotimeformat(const int &index);
};
