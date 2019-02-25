//James Dunlap
//Jcd160230@utdallas.edu
//3377.501

#include <csignal>
#include "program5.h"
#include <stdio.h>

void signalHandler( int signum ) {
  //switch statement to determine which signal is captured
  switch(signum){
     //sigint and sigterm lead to the same code
      case SIGINT:
      case SIGTERM:
	cout <<"SIGINT signal found, exiting and deleting PID file"<< endl;
	remove("cs3377dirmond.pid");
	exit(signum);
	break;
	//parse config file with daemon bool set to true
      case SIGHUP:
	cout <<"SIGHUP signal found, exiting and deleting PID file"<< endl;
	parseConfigFile(true);
     	break;
      default:
	cout <<"unknown signal found";
	break;
  }
}
