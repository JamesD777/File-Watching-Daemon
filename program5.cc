//James Dunlap
//Jcd160230@utdallas.edu
//3377.501

#include "program5.h"
#include <sys/stat.h>

map<int, string> optionMap;

int main(int argc, char *argv[]){
  //parse the command line and the config file
  parseCommandLine(argc, argv);
  parseConfigFile(false);
  //if daemon, make and update the versions and secure folders
  if(optionMap[DAEMON] == "true"){
    mkdir("./.versions", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    mkdir("./.secure", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    struct stat buffer;
    if(stat ("cs3377dirmond.pid", &buffer) == 0){
      cout << "daemon already running, exiting" << endl;
      exit(EXIT_FAILURE);
    }
    //set up logging and fork
    loggingFunction();
    processControl();
  }
  // run inotify and flush the buffers of stdout
  while(1){
    inotifyFunction();
    fflush(stdout);
  }
  return 0;

}
