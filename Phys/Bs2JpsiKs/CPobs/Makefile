ROOTCFLAGS   := $(shell root-config --cflags)
#ROOTLIBS     := -L$(ROOTSYS)/lib -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lRooFit -lRooFitCore -lRooStats -lFoam -lMinuit -lThread -pthread -lm -ldl -rdynamic
ROOTLIBS := -L$(ROOTSYS)/lib  `root-config --libs`  -lRooFit -lRooFitCore -lRooStats -lFoam -lMinuit -lMathMore -lTMVA

########################################################################################
# explicitly written these variables are:
# ROOTCFLAGS   := -pthread -I/usr/local/cern/root//include
# ROOTLIBS     := -L/usr/local/cern/root//lib -lCore -lCint -lHist \
#	-lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix \
#	-lPhysics -pthread -lm -ldl -rdynamic
########################################################################################

CPPFILES = $(filter-out TMVA_expert.cpp TMVA_teacher.cpp createTuple.cpp expert.cpp teacher.cpp weighting.cpp slimtuple.cpp, $(wildcard *.cpp))
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
DOTO          = $(wildcard *.cpp)

#######################
CXXFLAGS      += $(ROOTCFLAGS) -I. -I$(NEUROBAYES)/include -Iinc 
LIBSNB        = $(ROOTLIBS) $(NBLIBS) -lNeuroBayesTeacherCPP --verbose
LIBS          = $(ROOTLIBS) 

default : slimtuple.exe weighting.exe teacher.exe expert.exe createTuple.exe TMVA_teacher.exe TMVA_expert.exe

clean:
	@rm -rf *.o *.exe

%.o: %.cpp $(DOTH)
	@echo now compile $<
	@$(CXX) $(CXXFLAGS) $(CXXOUT)$@ -c $<

%.o: %.C $(DOTH)
	@echo now compile $<
	@$(CXX) $(CXXFLAGS) $(CXXOUT)$@ -c $<

slimtuple.exe: slimtuple.o $(OBJS)
	@echo now linking slimtuple
	@$(LD) $(LDFLAGS) $^ $(LIBS) -o $@

weighting.exe: weighting.o $(OBJS)
	@echo now linking weighting
	@$(LD) $(LDFLAGS) $^ $(LIBS) -o $@

teacher.exe: teacher.o $(OBJS)
	@echo now link Teacher
	@$(LD) $(LDFLAGS) $^ $(LIBSNB)  -o $@

expert.exe: expert.o $(OBJS)
	@echo now link expert
	@$(LD) $(LDFLAGS) $^ $(LIBSNB)  -o $@

createTuple.exe: createTuple.o $(OBJS)
	@echo now link createTuple
	@$(LD) $(LDFLAGS) $^ $(LIBSNB)  -o $@

TMVA_teacher.exe: TMVA_teacher.o $(OBJS)
	@echo now link TMVA Teacher
	@$(LD) $(LDFLAGS) $^ $(LIBSNB)  -o $@

TMVA_expert.exe: TMVA_expert.o $(OBJS)
	@echo now link TMVA Expert
	@$(LD) $(LDFLAGS) $^ $(LIBSNB)  -o $@

print :
	@echo $(DOTH) $(OBJS) $(NBLIBS)
