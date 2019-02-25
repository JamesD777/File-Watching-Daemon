//James Dunlap
//Jcd160230@utdallas.edu
//3377.501
#include "program5.h"
#include <tclap/CmdLine.h>
#include <stdlib.h>
#include <string>
#include <map>

using namespace std;

void parseCommandLine(int argc, char **argv){

  try{
    //Make the appropriate args needed for this programs arg parsing
    TCLAP::CmdLine cmd("CS3377.501 Program 5",' ',"1.0");
    TCLAP::UnlabeledValueArg<string> configArg("config", "The name of the configuration file. Defaults to cs3376dirmond.conf", false, "cs3377dirmond.conf", "config filename", false);
    TCLAP::SwitchArg daemonSwitch("d", "daemon", "Run in daemon mode(forks to run as a daemon).", cmd, false);
    //Add the args and then parse the given cmd line args from main
    cmd.add(configArg);
    cmd.parse(argc, argv);
    //Fill the mapTable with  relevant info from command line
    optionMap[CONFIG] = configArg.getValue();
    //update daemon
    if(daemonSwitch.getValue())
      optionMap[DAEMON] = "true";
    else
      optionMap[DAEMON] = "false";
    //Catches any errors thrown due to tclap and prints all relevant info
  }catch (TCLAP::ArgException &e)  // catch any exceptions
    { cerr << "error: " << e.error() << " for arg " << e.argId() << endl; }
}
