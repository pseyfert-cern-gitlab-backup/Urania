ROOTCFLAGS    = $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLIBS      = $(shell $(ROOTSYS)/bin/root-config --libs)
ROOTGLIBS     = $(shell $(ROOTSYS)/bin/root-config --glibs)

CXX           = g++
CXXFLAGS      = -g -Wall -fPIC
LD            = g++
LDFLAGS       = -g 
#SOFLAGS       = -shared $(ROOTGLIBS) -dynamiclib
SOFLAGS       = -lTreePlayer -lRooFit -lRooFitCore -lRooStats -shared $(ROOTGLIBS)


NGLIBB         = $(PWD)/libFitTools.so
NGLIBB        += $(ROOTGLIBS) 
GLIBB          = $(filter-out -lNew, $(NGLIBB))

NGLIBT         = $(PWD)/libTemplate.so
NGLIBT        += $(ROOTGLIBS) 
GLIBT          = $(filter-out -lNew, $(NGLIBT))

NGLIBR        += $(ROOTGLIBS) 
GLIBR          = $(filter-out -lNew, $(NGLIBR))

#PHYSBK         = $(PWD)/RooPhysBkg_cxx.so

NTUPLEB = FitTools.o 
NTUPLEB += FitToolsDict.o 

NTUPLET = TemplateTools.o 
NTUPLET += TemplateToolsDict.o 


CXXFLAGS      += $(ROOTCFLAGS)
LIBS           = $(ROOTLIBS) 

.SUFFIXES: .cc,.cxx,.C

.cc.o:
	$(CXX) $(CXXFLAGS) -c $<


##shabuild:
	#$(ROOTSYS)/bin/root -q -b -l 'build.C("RooPhysBkg.cxx")' 

# ================================================================================
libs:  $(NTUPLEB) 
#---------------------------------------------------------------
	$(CXX) $(NTUPLEB) $(SOFLAGS) -o libFitTools.so

FitToolsDict.cc:  FitTools.h
	$(ROOTSYS)/bin/rootcint -f FitToolsDict.cc -c FitTools.h


FullFit:  FullFitter.o libs
# -----------------------------------------------------------------------------
	$(LD) $(LDFLAGS)  -o FullFit FullFitter.o $(GLIBB) -lRooFit -lRooFitCore -lRooStats

libsTem:  $(NTUPLET) 
#---------------------------------------------------------------
	$(CXX) $(NTUPLET) $(SOFLAGS) -o libTemplate.so

TemplateToolsDict.cc:  TemplateTools.h
	$(ROOTSYS)/bin/rootcint -f TemplateToolsDict.cc -c TemplateTools.h


Templater:  TemplateCreator.o libsTem
# -----------------------------------------------------------------------------
	$(LD) $(LDFLAGS)  -o Templater TemplateCreator.o $(GLIBT) -lRooFit -lRooFitCore -lRooStats

Rookyfier:  RookeysCreator.o
# -----------------------------------------------------------------------------
	$(LD) $(LDFLAGS)  -o Rookyfier RookeysCreator.o $(GLIBR) -lRooFit -lRooFitCore -lRooStats

clean:
	rm -f *.so
	rm -f *.o
	rm -f *Dict*
	rm -f *cxx.d
	rm -f FullFit

