//James Dunlap
//Jcd160230@utdallas.edu
//3377.501

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include "program5.h"
#include <unistd.h>
#include <iostream>
#include <time.h>
#include <string>
#include <fstream>
#include <cryptopp/cryptlib.h>
#include <cryptopp/files.h>
#include <cryptopp/default.h>

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )

using namespace CryptoPP;

void inotifyFunction(){
  int len, i = 0, inst = inotify_init(), watchD;
  char buffer[BUF_LEN];
  //error if inotify instance fails
  if(inst < 0){ perror("inotify init fail");}
  //define watch  variables
  watchD = inotify_add_watch(inst, optionMap[WATCHDIR].c_str(), IN_MODIFY | IN_CREATE | IN_DELETE | IN_CLOSE_WRITE);
  len = read( inst, buffer, BUF_LEN );  
 
  if ( len < 0 ) {perror( "read" );}  
  //loop through checking against each event to determine what is happening
  while ( i < len ) {
    struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];
    if ( event->len ) {
      if ( event->mask & IN_CREATE ) {//file or directory created
        if ( event->mask & IN_ISDIR ) {printf( "The directory %s was created.\n", event->name );}
        else { printf( "The file %s was created.\n", event->name );}
      }
      else if ( event->mask & IN_DELETE ) {//file or directory deleted
        if ( event->mask & IN_ISDIR ) {
          printf( "The directory %s was deleted.\n", event->name );       
        }
        else {
          printf( "The file %s was deleted.\n", event->name );
        }
      }
      else if (( event->mask & IN_MODIFY) | (event->mask & IN_CLOSE_WRITE)) {//if a file is modified
  	if( optionMap[DAEMON] == "true" ){//if daemon is running, update versions and secure with a copy of the modified file
	  printf( "The file %s was modified and added to ./.versions.\n", event->name );
	  string move = "./.versions";
	  time_t rtime;//time to get the current date
	  struct tm * timeinfo;
	  char buffer[80];
	  time(&rtime);
	  timeinfo = localtime(&rtime);
	  strftime(buffer, sizeof(buffer), ".%Y.%m.%d-%H:%M:%S", timeinfo);
	  string str(buffer);
	  string name = event->name;
	  //moving and copying of the files into the .versions and .secure folders
	  string fullname = name + str;
	  move = "mv " + name + str + " " + move;
	  string str2 = "cp " + name + " " + name + str;
       	  system(str2.c_str());
	  system(move.c_str());
	  move = "./.secure";
	  str2 = "cp " + name + " " + name + str;
	  move = "mv " + name + str + " " + move;
	  system(str2.c_str());

	  ifstream in;
          in.open(name.c_str());
          ofstream out;
          out.open(fullname.c_str());
	  //decrypting of the secure file
	  FileSource f(in, true, new DefaultEncryptorWithMAC(optionMap[PASSWORD].c_str(), new FileSink(out)));
	  system(move.c_str());

	  numVersions(event->name);
	}
	else//modified but not in daemon mode
	  printf( "The file %s was modified.\n", event->name );
      }
    }
    i += EVENT_SIZE + event->len;
    }
 
  ( void ) inotify_rm_watch( inst, watchD );
  ( void ) close( inst );
}
