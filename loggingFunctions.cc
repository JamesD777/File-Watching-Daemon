//James Dunlap
//Jcd160230@utdallas.edu
//3377.501

#include "program5.h"
#include <stdio.h>


void loggingFunction(){
  //redirect the output to the logfile
  FILE* log;
  log = freopen(optionMap[LOGFILE].c_str(), "w+", stdout);
  (void)(log);
}
