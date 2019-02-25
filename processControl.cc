//James Dunlap
//Jcd160230@utdallas.edu
//3377.501

#include "program5.h"
#include <unistd.h>
#include <stdio.h>
#include <csignal>
#include <sys/stat.h>
#include <fstream>


void processControl()
{
  pid_t forkvalue;

  forkvalue = fork();

  //fork error occurred
  if (forkvalue < 0)
    exit(EXIT_FAILURE);

  // kill parent
  if (forkvalue > 0)
    exit(EXIT_SUCCESS);

  // child found
  if (setsid() < 0)
    exit(EXIT_FAILURE);
 
  signal(SIGINT, signalHandler);
  signal(SIGHUP, signalHandler);
  signal(SIGTERM, signalHandler);
  //fork again
  forkvalue = fork();
  ofstream outputFile("cs3377dirmond.pid");
  outputFile << getpid();;
  outputFile.close();

  // error
  if (forkvalue < 0)
    exit(EXIT_FAILURE);

  // kill the parent
  if (forkvalue > 0)
    exit(EXIT_SUCCESS);
}
