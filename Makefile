CXX=g++
CC=$(CXX)

DEBUG=-g
EXTRA_CCFLAGS=-Wall -std=c++11
CXXFLAGS=$(DEBUG) $(EXTRA_CCFLAGS)
CCFLAGS=$(CXXFLAGS)

CPPFLAGS=-I.
LDFLAGS=-L.
LDLIBS=

EXEC=hnStat
SRC_FILES=src/main.cpp

RM=rm -rf

all: $(O_FILES)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(EXEC) $(SRC_FILES) $(LDLIBS)

clean:
	$(RM) $(EXEC)