ROOTCFLAGS    = $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLIBS      = $(shell $(ROOTSYS)/bin/root-config --libs)
ROOTGLIBS     = $(shell $(ROOTSYS)/bin/root-config --glibs)
 
CXX           = g++
CXXFLAGS      = -g -Wall -fPIC
CXXFLAGS      = -g -Wall -fPIC
LD            = g++
LDFLAGS       = -g
SOFLAGS       = -shared


NGLIBB         = $(ROOTGLIBS) 
NGLIBB        += -lMinuit
#NGLIBB        += -lTMVA
#NGLIBB        += -lMLP
NGLIBB        += -lTreePlayer


GLIBB          = $(filter-out -lNew, $(NGLIBB))
ROOFIT         = -lRooFit -lRooFitCore  -lFoam -lRooStats
OTHLIB         = -lEG
CXXFLAGS      += $(ROOTCFLAGS)
LIBS           = $(ROOTLIBS) $(OTHLIB)


%.o : %.C
	$(CXX) $(CXXFLAGS) -c $<


# ================================================================================
lambders.o: lambders.cc lambders.h 
# ================================================================================
utilities.o:  utilities.cc utilities.h 
# ================================================================================
sb_sub.o:  sb_sub.cpp sb_sub.h 
# ================================================================================
confinte.o: confinte.cpp confinte.h
# ================================================================================
vai: main.o
	$(LD) $(LDFLAGS) $^ $(LIBS) -lMinuit $(ROOFIT) -o$@
	@echo "$@ done"
lime: calculate_limit.o utilities.o
	$(LD) $(LDFLAGS) $^ $(LIBS) -lMinuit $(ROOFIT) -o$@
	@echo "$@ done"
calca: calca.o confinte.o 
	$(LD) $(LDFLAGS) $^ $(LIBS) -lMinuit $(ROOFIT) -o$@
	@echo "$@ done"
test: testFC.o confinte.o 
	$(LD) $(LDFLAGS) $^ $(LIBS) -lMinuit $(ROOFIT) -o$@
	@echo "$@ done"
merge: mergeFC.o 
	$(LD) $(LDFLAGS) $^ $(LIBS) -lMinuit $(ROOFIT) -o$@
	@echo "$@ done"
interval: intervalFC.o 
	$(LD) $(LDFLAGS) $^ $(LIBS) -lMinuit $(ROOFIT) -o$@
	@echo "$@ done"
read: read.o confinte.o
	$(LD) $(LDFLAGS) $^ $(LIBS) -lMinuit $(ROOFIT) -o$@
	@echo "$@ done"
ktree: ktree.o confinte.o
	$(LD) $(LDFLAGS) $^ $(LIBS) -lMinuit $(ROOFIT) -o$@
	@echo "$@ done"
work: fd_ws.o
	$(LD) $(LDFLAGS) $^ $(LIBS) -lMinuit $(ROOFIT) -o$@
	@echo "$@ done"

# ================================================================================
clean:
	rm -f *.o plot


