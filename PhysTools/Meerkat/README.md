# Meerkat

## Introduction

Meerkat is the multidimensional kernel density estimation package. 

It uses a variation of kernel density estimation (KDE) technique, 
relative KDE, where kernel density provides the correction on top 
of some approximation PDF. The approximation PDF defines the behaviour
of the resulting PDF estimate at the edges of the phase space and 
in the region of rapidly-changing structures. This approach allows
to use kernel density estimation in a multidimensional case, for 
the phase spaces with have non-trivial boundaries (such as for 
Dalitz plots). 

The code uses ROOT NTuples as input data sets, and can output 
the resulting estimated distributions as ROOT histograms (for 1D 
and 2D distributions), therefore it should be easily integrated into 
the analyses using e.g. Laura++. For analyses in more than 2 dimensions, 
the estimated PDFs can be calculated as the multilinear interpolation 
on the binned grid, to allow fast calculation as part of the unbinned 
amplitude fits. 


## Building the Code

The package depends only on ROOT.  Before building the code, it is necessary
that either the ROOTSYS environment variable be set or that the root-config
program be in the PATH.

To build the shared library:

```bash
> cd Meerkat
> make
```

A shared library will be created in the lib sub-directory:

lib/libMeerkat.so


## Examples and Documentation

Example code is included in the examples/ directory.

To build the example code:

```bash
> cd examples
> make
```

Examples using PyROOT interface are in python/ directory. 

To run PyROOT examples with ROOT6, one has to set ROOT_INCLUDE_PATH 
variable to point to Meerkat/inc/ 

To build the online doxygen documentation just run doxygen in the top level
Meerkat directory and then load the index.html file found in doxygen/html.


## Contents of this package 

  * doc/      - Documentation
  * src/      - C++ source file of the Meerkat library
  * inc/      - Header files 
  * examples/ - Examples of compiled programs
  * python/   - PyROOT examples 
  * doxygen/  - Doxygen documentation

## Authors

Contact: Anton Poluektov

  Anton.Poluektov@cern.ch
  A.O.Poluektov@warwick.ac.uk
