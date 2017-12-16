 ### CLUSTER IN HEIDELBERG
#GSLCONFIG = /local/lcg/external/GSL/1.10/x86_64-slc5-gcc43-opt/bin/gsl-config
 
### Paul's private computer, and lxplus
GSLCONFIG = gsl-config

CXXFLAGS = $(shell root-config --cflags) -g -O0 $(shell $(GSLCONFIG) --cflags)
LDFLAGS = $(shell root-config --libs) -lTMVA -lXMLIO -lXMLParser -lMLP -lTreePlayer -lMinuit -g -O0 $(shell $(GSLCONFIG) --libs)
TMVA_write_Geo : TMVA_write_Geo.o flat2013.o Rich1DTabFunc.o

overtrainingtest: overtrainingtest.o TMVAntuple.o useTMVAntuple.o
overtrainingtest2: overtrainingtest2.o flatntuple.o useflatntuple.o

###main: main.o MVAntuple.o Rich1DTabFunc.o
###	c++-color -L/home/pseyfert/coding/v5-34-01/lib -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -pthread -lm -ldl -rdynamic -lRooStats -lRooFitCore -lRooFit -lMinuit -lFoam -lMathMore -lstdc++ -L/usr/lib -lgsl -lgslcblas -lm -m64  main.o MVAntuple.o Rich1DTabFunc.o  -o main
