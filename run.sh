#!/bin/bash
#James Dunlap
#Jcd160230@utdallas.edu
#3377.501


#compile and link the decrypt extra credit as well as call make for Program 5
echo Creating decrypt!
echo g++ -Wall -I ~/program5/include -c -o program5e.o program5e.cc
g++ -Wall -I ~/program5/include -c -o program5e.o program5e.cc
echo g++ -static -o decrypt program5e.o -L/home/012/j/jc/jcd160230/program5/lib -lcryptopp
g++ -static -o decrypt program5e.o -L/home/012/j/jc/jcd160230/program5/lib -lcryptopp
echo Compiling and linking main project using the Makefile!
make
echo ./myProject to run the main project, ./decrypt to decrypt the files
echo Make sure to add the necessary flags!
