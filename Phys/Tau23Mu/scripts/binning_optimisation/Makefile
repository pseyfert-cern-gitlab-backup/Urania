ROOTCONFIG = root-config
#CPP = g++-color
#CXX = g++-color
#CC = g++-color
CPPFLAGS = $(shell $(ROOTCONFIG) --cflags) -g -O2 -mtune=native -Wall
LDFLAGS = $(shell $(ROOTCONFIG) --libs) -O2 -mtune=native -Wall
CXXFLAGS = $(CPPFLAGS)

all: main_2 main_3

deltaLQ.o: deltaLQ.cpp logstream.h deltaLQ.h

%.o: %.cc logstream.h deltaLQ.h

main_2: main_2.o deltaLQ.o logstream.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

short: short.o deltaLQ.o logstream.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

main_9: main_9.o deltaLQ.o logstream.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

main_8: main_8.o deltaLQ.o logstream.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

main_4: main_4.o deltaLQ.o logstream.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

main_7: main_7.o deltaLQ.o logstream.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

main_6: main_6.o deltaLQ.o logstream.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

main_5: main_5.o deltaLQ.o logstream.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

main_51: main_51.o deltaLQ.o logstream.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

main_52: main_52.o deltaLQ.o logstream.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

main_3: main_3.o deltaLQ.o logstream.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

main: main.o deltaLQ.o logstream.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@
