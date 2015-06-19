ROOTCFLAGS   := $(shell root-config --cflags)
#ROOTLIBS     := -L$(ROOTSYS)/lib -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lRooFit -lRooFitCore -lRooStats -lFoam -lMinuit -lThread -pthread -lm -ldl -rdynamic
ROOTLIBS := -L$(ROOTSYS)/lib  `root-config --libs`  -lGenVector -lRooFit -lRooFitCore -lRooStats -lFoam -lMinuit -lMathMore

########################################################################################
# explicitly written these variables are:
# ROOTCFLAGS   := -pthread -I/usr/local/cern/root//include
# ROOTLIBS     := -L/usr/local/cern/root//lib -lCore -lCint -lHist \
#	-lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix \
#	-lPhysics -pthread -lm -ldl -rdynamic
########################################################################################

CPPFILES = $(filter-out teacher.cpp makemctuple.cpp makePIDtuple.cpp expert.cpp weighting.cpp optimise.cpp, $(wildcard *.cpp))
CFILES = $(wildcard *.C)
CCFILES = $(wildcard *.cc)
OBJS = $(patsubst %.cpp,%.o, $(CPPFILES)) $(patsubst %.C,%.o, $(CFILES)) $(patsubst %.cc,%.o, $(CCFILES))

# set the compiler options
# http://stackoverflow.com/questions/5083047/linker-problem-with-libstdc-so-6-in-connection-with-cuda/5088954#5088954
CXX           = g++
CXXFLAGS      = -c -g -fPIC  #set compiler options
                                   #-g compile with debug information
                                   #-O optimize
                                   #-Wall show warnings for everything
                                   #-fPIC compile source file as sharable object 
DOTH = $(wildcard *.h) $(wildcard *.icpp)

# set the linker options
LD            = g++
LDFLAGS       = -O 
SOFLAGS       = -shared

#NeuroBayes (R) libraries
NBLIBS        =  -L$(NEUROBAYES)/lib 
DOTO := $(wildcard *.cpp)

#######################
CXXFLAGS      += $(ROOTCFLAGS) -I. -I$(NEUROBAYES)/include -Iinc 
LIBSNB        = $(ROOTLIBS) $(NBLIBS) -lNeuroBayesTeacherCPP 
LIBS          = $(ROOTLIBS) 

default : weighting.exe optimise.exe makemctuple.exe makePIDtuple.exe expert.exe teacher.exe 

clean:
	@rm -rf *.o *.exe

update : clean all

%.o: %.cpp $(DOTH)
	@echo now compile $<
	$(CXX) $(CXXFLAGS) -c $< -o  $@

%.o: %.C $(DOTH)
	@echo now compile $<
	$(CXX) $(CXXFLAGS) -c $< -o  $@

makemctuple.exe: makemctuple.o $(OBJS)
	@echo now link makemctuple
	$(LD) $(LDFLAGS) $^ $(ROOTLIBS)  -o $@

makePIDtuple.exe: makePIDtuple.o $(OBJS)
	@echo now link makePIDtuple
	$(LD) $(LDFLAGS) $^ $(ROOTLIBS)  -o $@

optimise.exe: optimise.o $(OBJS)
	@echo now link optimise
	$(LD) $(LDFLAGS) $^ $(ROOTLIBS)  -o $@

weighting.exe: weighting.o $(OBJS)
	@echo now link weighting
	$(LD) $(LDFLAGS) $^ $(ROOTLIBS)  -o $@

teacher.exe: teacher.o $(OBJS)
	@echo now link Teacher
	$(LD) $(LDFLAGS) $^ $(LIBSNB)  -o $@

expert.exe: expert.o $(OBJS)
	@echo now link expert
	$(LD) $(LDFLAGS) $^ $(LIBSNB)  -o $@

print :
	@echo $(DOTH) $(OBJS)
