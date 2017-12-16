# ROOT part
EXECUTABLES = prompter counter
LIBNAME = LimitROOT

ROOTCONFIG = root-config
CXX = $(shell $(ROOTCONFIG) --cxx)
CXXso = $(shell $(ROOTCONFIG) --cxx)
LD = $(shell $(ROOTCONFIG) --ld)
TUNEFLAG = $(shell $(CXX) --version | \
	   awk '// { for (i = 1; i <= NF; ++i) if ($$i ~ /[0-9]*\.[0-9]*\.[0-9]*$$/) {if ($$i < "4.2") print "-mtune=opteron"; else print "-mtune=native"; }; }')
LDFLAGS = -ggdb -fPIC $(shell $(ROOTCONFIG) --libs)
CXXFLAGS = -Wall -Wextra -O2 $(TUNEFLAG) $(shell $(ROOTCONFIG) --cflags) -fpermissive -ggdb
SOFLAGS = -fPIC -shared $(LDFLAGS)

# source and dictionary files
alldicts = LimitDict.cpp
allsrc = $(wildcard *.cpp) $(alldicts)

.PHONY: dox dep clean cleandeps cleandicts dicts

# general targets
all: dep lib$(LIBNAME).a lib$(LIBNAME).so $(EXECUTABLES)
# dox

dox:
	doxygen

dep: dicts $(patsubst %.cpp,%.d,$(allsrc) $(alldicts))

dicts: $(alldicts)

clean: cleandicts
	rm -f *.o *.os *~

cleandicts:
	rm -f *Dict.cpp
	rm -f *Dict.h

cleandeps:
	rm -f *.d

distclean: cleandeps clean
	rm -f lib$(LIBNAME).so lib$(LIBNAME).a

$(EXECUTABLES): LDLIBS += -L. -l$(LIBNAME)

# how to link libZooROOT.so
lib$(LIBNAME).so: $(patsubst %.cpp,%.os,$(allsrc))
	$(CXXso) $(SOFLAGS) $^ -o $@

lib$(LIBNAME).a: lib$(LIBNAME).a($(patsubst %.cpp,%.o,$(allsrc)))

LimitDict.cpp: $(filter-out LimitDict.h,$(wildcard *.h))

# General rules
%.d: %.cpp
	$(CXX) -MM $(CXXFLAGS) $< > $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
		rm -f $@.$$$$

%.os: %.cpp
	$(CXXso) -fPIC $(CXXFLAGS) -c $< -o $@

# ROOT rules (??? should I include them from somewhere in ROOT ???)
#dependency here
%Dict.cpp:
	$(shell $(ROOTCONFIG) --bindir)/rootcint -f $@ -c -p $(filter-out %LinkDef.h,$^) $(filter %LinkDef.h,$^) || rm -f $@
	mv $@ $@.tmp
	awk '/.*<.*>::fgIsA = 0/ { if (!($$0 ~ /^template *<>/)) $$0 = "template <> " $$0; } // { print; }' < $@.tmp > $@
	rm $@.tmp

# include dependencies
include $(patsubst %.cpp,%.d,$(allsrc))

