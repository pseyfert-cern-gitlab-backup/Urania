ROOTCFLAGS    = $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLIBS      = $(shell $(ROOTSYS)/bin/root-config --libs)
ROOTGLIBS     = $(shell $(ROOTSYS)/bin/root-config --glibs)
ROOTGLIBS     += $(ROOTSYS)/lib/libMinuit.so 
ROOTGLIBS     += $(ROOTSYS)/lib/libFoam.so 
ROOTGLIBS     += $(ROOTSYS)/lib/libRooFit.so 
ROOTGLIBS     += $(ROOTSYS)/lib/libRooFitCore.so 
ROOTGLIBS     += $(ROOTSYS)/lib/libRooStats.so 
 
CXX           = g++ 
CXXFLAGS      = -g -Wall -fPIC
LD            = g++ 
LDFLAGS       = -g 
#SOFLAGS       = -shared $(ROOTGLIBS) -dynamiclib
SOFLAGS       = -shared $(ROOTGLIBS)


NGLIBB         = $(ROOTGLIBS) 
#NGLIBB        += $(PWD)/RooRadiativeTail_cxx.so
#NGLIBB        += $(PWD)/RooBetaFun_cxx.so
#NGLIBB        += $(PWD)/RooGaussian3_cxx.so
#NGLIBB        += $(PWD)/RooMassBeta_cxx.so
#NGLIBB        += $(PWD)/RooPhysBkg_cxx.so
GLIBB          = $(filter-out -lNew, $(NGLIBB))

CXXFLAGS      += $(ROOTCFLAGS)
LIBS           = $(ROOTLIBS) 

.SUFFIXES: .cc,.cxx,.C

.cc.o:
	$(CXX) $(CXXFLAGS) -c $<


shabuild:
	$(ROOTSYS)/bin/root -q -b -l 'build.C("RooRadiativeTail.cxx")' 
	$(ROOTSYS)/bin/root -q -b -l 'build.C("RooGaussian3.cxx")' 
	$(ROOTSYS)/bin/root -q -b -l 'build.C("RooBetaFun.cxx")' 
	$(ROOTSYS)/bin/root -q -b -l 'build.C("RooMassBeta.cxx")' 
	$(ROOTSYS)/bin/root -q -b -l 'build.C("RooPhysBkg.cxx")' 

# ================================================================================
#lib:  shabuild
#---------------------------------------------------------------
#	$(CXX) $(SOFLAGS) -o  RooMassBeta_cxx.so RooBetaFun_cxx.so RooPhysBkg_cxx.so RooRadiativeTail_cxx.so RooGaussian3_cxx.so


#FitNG:  BhhFit_NG.o shabuild
Fitbs:  Fittone.o 
# -----------------------------------------------------------------------------
	$(LD) $(LDFLAGS)  -o Fitbs Fittone.o $(GLIBB) 

FitSim:  FitSim.o 
# -----------------------------------------------------------------------------
	$(LD) $(LDFLAGS)  -o FitSim FitSim.o $(GLIBB) 

clean:
	rm -f *.so
	rm -f *.o
	rm -f *Dict*
	rm -f *cxx.d
	rm -f Fitbs



