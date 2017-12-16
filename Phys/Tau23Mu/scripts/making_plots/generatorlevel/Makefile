script: script.o generatorclass.o
sc: sc.o dalitz.o
rec: rec.o flat.o
true: true.o flat.o

CPPFLAGS=$(shell root-config --cflags) -g -Wall -Wshadow -O2 -march=native 
LDFLAGS=$(shell root-config --libs) -lGenVector -lRooStats -lRooFitCore -lRooFit
