//James Dunlap
//Jcd160230@utdallas.edu
//3377.501

#ifndef program5_H_
#define program5_H_

#include <iostream>
#include <stdio.h>
#include <map>
#include <string>
#include <tclap/CmdLine.h>

using namespace std;
//enum from option map
enum myArgs{DAEMON, CONFIG, VERBOSE, LOGFILE, PASSWORD, NUMVERSIONS, WATCHDIR};
//option map to hold given values
extern map<int, string> optionMap;
//prototypes
void parseCommandLine(int, char**);
void parseConfigFile(bool);
void inotifyFunction();
void processControl();
void signalHandler(int);
void loggingFunction();
void numVersions(string);


#endif /*program5_H_*/
