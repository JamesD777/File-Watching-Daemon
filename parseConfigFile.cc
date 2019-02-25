//James Dunlap
//Jcd160230@utdallas.edu
//3377.501

#include <rude/config.h>
#include "program5.h"
#include <stdlib.h>

using namespace rude;
void parseConfigFile(bool daemon)
{
  // Create config object
  Config config;
  
  // load the config file
  if(!config.load(optionMap[CONFIG].c_str())){
    cerr << "Config file missing" << endl;
    exit(0);
  }
    
  config.load(optionMap[CONFIG].c_str());
  // read in the data
  if(!config.setSection("Parameters")){
    cerr << "parameters section missing" << endl;
    exit(0);
  }
  if(!config.setSection("Verbose")){
    cerr << "verbose section missing" << endl;
    exit(0);
  }
  if(!config.setSection("LogFile")){
    cerr << "logfile section missing" << endl;
    exit(0);
  }
  if(!config.setSection("NumVersions")){
    cerr << "numversions section missing" << endl;
    exit(0);
  }
  if(!config.setSection("Password")){
    cerr << "Password section missing" << endl;
    exit(0);
  }
  if(!config.setSection("WatchDir")){
    cerr << "watchdir section missing" << endl;
    exit(0);
  }

  config.setSection("Parameters");
  optionMap[VERBOSE] = config.getStringValue("Verbose");
  optionMap[LOGFILE] = config.getStringValue("LogFile");
  optionMap[NUMVERSIONS] = config.getStringValue("NumVersions");
  //if the daemon is running, dont allow change to password or watchdir
  if(!daemon){
    optionMap[PASSWORD] = config.getStringValue("Password");
    optionMap[WATCHDIR] = config.getStringValue("WatchDir");
  }
  //print more data if verbose is true
  if(optionMap[VERBOSE] == "true"){
    cout << "Verbose: " << optionMap[VERBOSE] << endl;
    cout << "Logfile: " << optionMap[LOGFILE] << endl;
    cout << "Numversions: " << optionMap[NUMVERSIONS] << endl;
    cout << "Password: " << optionMap[PASSWORD] << endl;
    cout << "Watchdir: " << optionMap[WATCHDIR] << endl;

  }
}
