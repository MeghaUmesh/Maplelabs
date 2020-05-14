#include<string>
#include<vector>
#include<regex>
using namespace std;
    //auto start = high_resolution_clock::now(); 
    string day("(([0-9]{2})|MON|TUE|WED|THU|FRI|SAT|SUN)");
    string month("(((0{0,1})[1-9]|1[012])|JAN|FEB|MAR|APR|MAY|JUN|JUL|AUG|SEP|OCT|NOV|DEC)");
    string year("[0-9]{2,4}");
    string time_stamp("([01]*[0-9]|2[0-3]):([0-5][0-9]|6[0]):([0-5][0-9]|6[0])[\\s]{0,1}([AP]M?)?([,.*:]?)(([0-9]{3})?)[\\s]{0,1}[']{0,1}[+-]{0,1}([0-9]{0,4}[']{0,1})");
    string regex5(""+time_stamp+"");
    string regex1(""+year+"[-,/,\\s]?"+month+"[-,/,\\s]?"+day+"[\\s'T'*]?"+time_stamp+"");
    string regex2(""+month+"[\\s/]?"+day+"[,\\s/]"+year+"[\\s*]"+time_stamp+"");
    string regex3(""+month+"[-\\s]?"+day+"[-\\s_]"+time_stamp+"[\\s]?"+"([0-9]{2,4})?");
    string regex4(""+day+"[-/\\s]"+month+"[-/\\s]"+"(\\d{2,4})?[\\s:]?"+time_stamp+"");
    string level("INFO|WARN|DEBUG|ERROR|TRACE|FATAL|NOTICE|ALERT");
    //smatch match;
    vector <string> date={regex1,regex2,regex3,regex4,regex5};
    //vector <string> level={loglevel};

    
   