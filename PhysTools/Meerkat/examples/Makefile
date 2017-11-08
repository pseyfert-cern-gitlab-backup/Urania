
# --- External configuration ----------------------------------

# first check that ROOTSYS is defined
ifndef ROOTSYS
  ROOTSYS := $(shell root-config --prefix)
  ROOTBINDIR := $(shell root-config --bindir)
  ifeq ($(ROOTSYS), )
    $(error running of root-config failed or reported null value)
  endif 
else
  ROOTBINDIR := $(ROOTSYS)/bin
endif

ROOTCONFIG := $(ROOTBINDIR)/root-config
ARCH       := $(shell $(ROOTCONFIG) --arch)
PLATFORM   := $(shell $(ROOTCONFIG) --platform)

INCLUDES = 
WORKDIR  = tmp

ifeq ($(findstring linux, $(ARCH)),linux)
# This set here should work for Linux.
CXX      = g++
LD       = g++
CXXFLAGS = -g -O2 -Wall -Wextra -Wshadow -Woverloaded-virtual -fPIC
MFLAGS   = -MM
LDFLAGS  = -g
SOFLAGS  = -shared
endif

ifeq ($(ARCH),macosx64)
# For Mac OS X you may need to put -m64 in CXXFLAGS and SOFLAGS.
CXX      = g++
LD       = g++
CXXFLAGS = -g -O3 -Wall -Wextra -Wshadow -Woverloaded-virtual -fPIC -m64
MFLAGS   = -MM
LDFLAGS  = -g
SOFLAGS  = -m64 -dynamiclib -single_module -undefined dynamic_lookup
endif

# --- Internal configuration ----------------------------------
INCDIR=$(MEERKATROOT)
DEPDIR=$(WORKDIR)/dependencies
OBJDIR=$(WORKDIR)/objects

SHLIBFILE=$(PWD)/$(WORKDIR)/libMeerkatUtils.so

ROOTLIBS      = $(shell root-config --libs)
NLIBS         = $(ROOTLIBS) 
#NLIBS        += -lEG
NLIBS        += -lRooFit
NLIBS        += -lMinuit
NLIBS        += -lTreePlayer
NLIBS        += ${PWD}/../lib/libMeerkat.so
LIBS          = $(filter-out -lNew, $(NLIBS))

INCLUDES += -I$(INCDIR) -I$(shell $(ROOTBINDIR)/root-config --incdir)
CXXFLAGS += $(INCLUDES)

default: bin

# List of all source files
CCLIST:=$(wildcard *.cpp)

# List of all source files that contain main functions
BINCCLIST:=$(shell egrep -l "^[[:space:]]*int[[:space:]]*main\>" $(CCLIST))

# List of all source files to be compiled into the library
LIBCCLIST:=$(filter-out $(BINCCLIST), $(CCLIST))

# List of all object files to build
OLIST:=$(patsubst %.cpp,%.o,$(addprefix $(OBJDIR)/,$(notdir $(CCLIST))))

# List of all object files to be combined into library
LIBOLIST:=$(patsubst %.cpp,%.o,$(addprefix $(OBJDIR)/,$(notdir $(LIBCCLIST))))

# List of all dependency files to make
DLIST:=$(patsubst %.cpp,%.d,$(addprefix $(DEPDIR)/,$(notdir $(CCLIST))))

# List of all binary files to make
BINLIST:=$(patsubst %.cpp,%,$(notdir $(BINCCLIST)))

# Implicit rule making all dependency Makefiles included at the end of this makefile
$(DEPDIR)/%.d: %.cpp
	@echo "Making $@"
	@mkdir -p $(DEPDIR)
	@set -e; $(CXX) $(MFLAGS) $(CXXFLAGS) $< \
	          | sed 's#\($(notdir $*)\)\.o[ :]*#$(OBJDIR)/\1.o $@ : #g' > $@; \
	        [ -s $@ ] || rm -f $@

# Implicit rule to compile all sources
$(OBJDIR)/%.o : %.cpp
	@echo "Compiling $<"
	@mkdir -p $(OBJDIR)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to combine objects into a shared library
$(SHLIBFILE): $(LIBOLIST)
	@echo "Making $(SHLIBFILE)"
	@rm -f $(SHLIBFILE)
	@$(CXX) $(LIBOLIST) $(SOFLAGS) -o $(SHLIBFILE)

# Rule to compile all binaries
% : $(OBJDIR)/%.o
	@echo "Linking $@"
	@$(CXX) $(LDFLAGS) $< -o $@ $(LIBS)

bin: $(BINLIST)

clean:
	rm -f $(BINLIST)
	rm -f $(SHLIBFILE)
	rm -rf $(WORKDIR)

.PHONY : bin default clean

-include $(DLIST)
