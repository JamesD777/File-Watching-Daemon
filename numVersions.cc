//James Dunlap
//Jcd160230@utdallas.edu
//3377.501

#include <stdio.h>
#include "program5.h"
#include <stdlib.h>
#include <sstream>

void numVersions(string event){
  //use popen to get the file count
  FILE *fp;
  char buffer[1024];
  string path = ".versions/" + event;
  string pop = "ls " + path + "* | wc -l";
  fp = popen(pop.c_str(), "r");

  char* line = fgets(buffer, 1024, fp);
  //get the current num from the buffer and the limit from option map
  int num = atoi(line);
  int confnum = atoi(optionMap[NUMVERSIONS].c_str());

  //compare the two, deleting if there is a differece
  fflush(stdout);
  if(num > confnum)
    {
      stringstream s;
      s << num - confnum;
      cout << "removed " << num - confnum  << " versions of " + event << endl;
      string rm = "ls " + path + "* | head -" + s.str() + " | xargs rm";
      system(rm.c_str());
    }
  pclose(fp);
}
