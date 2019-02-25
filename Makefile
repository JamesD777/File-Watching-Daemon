# James Dunlap
# Jcd160230@utdallas.edu
# CS 3377.501

#
# Set up info for C++ implicit rule
CXX = g++
CXXFLAGS = -Wall
CPPFLAGS = -I ~/program5/include

#
# Set up any Linker Flags
LDFLAGS = -L/home/012/j/jc/jcd160230/program5/lib
LDLIBS = -lrudeconfig -lcryptopp 
#
# We choose the project name.  This is used in building the file name for the backup target
PROJECTNAME = Project5

#
# We choose the source files to include and name the output
SRCS = program5.cc parseCommandLine.cc parseConfigFile.cc inotifyFunctions.cc loggingFunctions.cc processControl.cc signalHandling.cc numVersions.cc
#
# We choose the name of the executable to be created
EXEC = myProject

#
# You normally don't need to change anything below here.
# ======================================================
#
OBJS = $(SRCS:cc=o)

all: $(EXEC)

clean:
	rm -f $(OBJS) *.d *~ \#* $(EXEC)
	rm -rf program5e.o .secure/ .versions/ decrypt

Makefile: $(SRCS:.cc=.d)

# Pattern for .d files.
%.d:%.cc
	@echo Updating .d Dependency File
	@set -e; rm -f $@; \
	$(CXX) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

#  This is a rule to link the files.  Pretty standard
$(EXEC): $(OBJS)
	$(CXX) -static -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)


# Backup Target
backup:	clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename `pwd`))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME)
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!


# Include the dependency files
-include $(SRCS:.cc=.d)

