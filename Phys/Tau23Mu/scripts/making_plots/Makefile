ROOTCFLAGS   := $(shell root-config --cflags)
ROOTLIBS     := $(shell root-config --libs)


########################################################################################
# explicitly written these variables are:
# ROOTCFLAGS   := -pthread -I/usr/local/cern/root//include
# ROOTLIBS     := -L/usr/local/cern/root//lib -lCore -lCint -lHist \
#	-lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix \
#	-lPhysics -pthread -lm -ldl -rdynamic
########################################################################################

# set the compiler options
CXX           = g++
CXXFLAGS      = -g -O  -fPIC -Wall #set compiler options
                                   #-g compile with debug information
                                   #-O optimize
                                   #-Wall show warnings for everything
                                   #-fPIC compile source file as sharable object                                              
CXXOUT	    = -o 				   
# set the linker options
LD            = gcc
LDFLAGS       = -O 
SOFLAGS       = -shared

#######################
CXXFLAGS      += $(ROOTCFLAGS) -I. -I$(NEUROBAYES)/include -Iinc 
LIBS          = $(ROOTLIBS) -lRooFit 

default : 

clean:
	@rm -rf *.o 

%.o: %.cc 
	@echo now compile $<
	@$(CXX) $(CXXFLAGS) $(CXXOUT)$@ -c $<

readNtuple.h: 
	@echo now creating header
	@root -l -b -q getheader.C

MVAntuple.o: MVAntuple.h MVAntuple.C

teacher: teacher.o  readNtuple.o 
	@echo now link Teacher
	@$(LD) $(LDFLAGS) $^ $(LIBS)  -o $@

expert: expert.cc readNtuple.o 
	$(CXX) $(CXXFLAGS) $(LDFLAGS) readNtuple.o $(ROOTLIBS) $(NBLIBS) -lNeuroBayesExpertCPP $(CXXOUT)$@  $<

.PHONY: check clean default
