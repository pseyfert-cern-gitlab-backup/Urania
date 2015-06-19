ROOTCFLAGS   := $(shell root-config --cflags)
#ROOTLIBS     := -L$(ROOTSYS)/lib -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lRooFit -lRooFitCore -lRooStats -lFoam -lMinuit -lThread -pthread -lm -ldl -rdynamic
ROOTLIBS := -L$(ROOTSYS)/lib  `root-config --libs`  -lRooFit -lRooFitCore -lRooStats -lFoam -lMinuit -lMathMore

########################################################################################
# explicitly written these variables are:
# ROOTCFLAGS   := -pthread -I/usr/local/cern/root//include
# ROOTLIBS     := -L/usr/local/cern/root//lib -lCore -lCint -lHist \
#	-lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix \
#	-lPhysics -pthread -lm -ldl -rdynamic
########################################################################################

CPPFILES = $(filter-out teacher.cpp expert.cpp, $(wildcard *.cpp))
CFILES = $(wildcard *.C)
OBJS = $(patsubst %.cpp,%.o, $(CPPFILES)) $(patsubst %.C,%.o, $(CFILES))

# set the compiler options
CXX           = g++
CXXFLAGS      = -c -g -I$(ROOTSYS)/include  -fPIC  #set compiler options
                                   #-g compile with debug information
                                   #-O optimize
                                   #-Wall show warnings for everything
                                   #-fPIC compile source file as sharable object 
DOTH = $(wildcard *.h) $(wildcard *.icpp)

CXXOUT	    = -o 				   
# set the linker options
LD            = gcc
LDFLAGS       = -O 
SOFLAGS       = -shared

#NeuroBayes (R) libraries
NBLIBS        =  -L$(NEUROBAYES)/lib 
DOTO := $(wildcard *.cpp)

#######################
CXXFLAGS      += $(ROOTCFLAGS) -I. -I$(NEUROBAYES)/include -Iinc 
LIBSNB        = $(ROOTLIBS) $(NBLIBS) -lNeuroBayesTeacherCPP 
LIBS          = $(ROOTLIBS) 

default : teacher.exe expert.exe

clean:
	@rm -rf *.o *.exe

%.o: %.cpp $(DOTH)
	@echo now compile $<
	@$(CXX) $(CXXFLAGS) $(CXXOUT)$@ -c $<

%.o: %.C $(DOTH)
	@echo now compile $<
	@$(CXX) $(CXXFLAGS) $(CXXOUT)$@ -c $<

teacher.exe: teacher.o $(OBJS)
	@echo now link Teacher
	@$(LD) $(LDFLAGS) $^ $(LIBSNB)  -o $@

expert.exe: expert.o $(OBJS)
	@echo now link expert
	@$(LD) $(LDFLAGS) $^ $(LIBSNB)  -o $@

print :
	@echo $(DOTH) $(OBJS)
