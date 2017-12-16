ROOTCFLAGS   := $(shell root-config --cflags)
ROOTLIBS     := $(shell root-config --libs)

PHIT_LICENCE_PATH  =$(shell echo /afs/cern.ch/sw/lcg/external/neurobayes/license)
#NEUROBAYES         =$(shell echo $(LCG_external_area)/neurobayes/10.12/$(CMTCONFIG))

# heidelberg
NEUROBAYES = /local/lcg/external/neurobayes_expert/10.12/x86_64-slc5-gcc43-opt

# lxplus
NEUROBAYES = /afs/cern.ch/sw/lcg/external/neurobayes/10.12/x86_64-slc5-gcc43-opt
LD_LIBRARY_PATH    += :$(NEUROBAYES)/lib/

########################################################################################
# explicitly written these variables are:
# ROOTCFLAGS   := -pthread -I/usr/local/cern/root//include
# ROOTLIBS     := -L/usr/local/cern/root//lib -lCore -lCint -lHist \
#	-lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix \
#	-lPhysics -pthread -lm -ldl -rdynamic
########################################################################################

# set the compiler options
CXX           = g++
CXXFLAGS      = -ggdb -O  -fPIC -Wall #set compiler options
                                   #-g compile with debug information
                                   #-O optimize
                                   #-Wall show warnings for everything
                                   #-fPIC compile source file as sharable object                                              
CXXOUT	    = -o 				   
# set the linker options
LD            = gcc
LDFLAGS       = -O  -ggdb
SOFLAGS       = -shared

#NeuroBayes (R) libraries
NBLIBS        =  -L$(NEUROBAYES)/lib 

#######################
CXXFLAGS      += $(ROOTCFLAGS) -I. -I$(NEUROBAYES)/include -Iinc -ggdb
CFLAGS      += $(ROOTCFLAGS) -I. -I$(NEUROBAYES)/include -Iinc -ggdb
CPPFLAGS      += $(ROOTCFLAGS) -I. -I$(NEUROBAYES)/include -Iinc -ggdb
LIBS          = $(ROOTLIBS) -lRooFit  $(NBLIBS) -lNeuroBayesTeacherCPP 

default : teacher expert

clean:
	@rm -rf *.o teacher expert

check:
	@echo $(NEUROBAYES)
	@echo $(PHIT_LICENCE_PATH)
	@echo $(LD_LIBRARY_PATH)

%.o: %.cc 
	@echo now compile $<
	$(CXX) $(CXXFLAGS) $(CXXOUT)$@ -c $<

readNtuple.h: 
	@echo now creating header
	root -l -b -q getheader.C

readNtuple.o: readNtuple.h readNtuple.C

teacher: teacher.o  readNtuple.o 
	@echo now link Teacher
	$(LD) $(LDFLAGS) $^ $(LIBS)  -o $@

expertP: expertP.cc readNtuple.o 
	$(CXX) $(CXXFLAGS) $(LDFLAGS) readNtuple.o $(ROOTLIBS) $(NBLIBS) -lNeuroBayesExpertCPP $(CXXOUT)$@  $<

expert: expert.cc readNtuple.o 
	$(CXX) $(CXXFLAGS) $(LDFLAGS) readNtuple.o $(ROOTLIBS) $(NBLIBS) -lNeuroBayesExpertCPP $(CXXOUT)$@  $<

.PHONY: check clean default
