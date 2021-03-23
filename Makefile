#
# Makefile for CSF Assignment 3
#

CPP_SRCS = Cache.cpp main.cpp Set.cpp
CONSERVATIVE_FLAGS = -Wall -Wextra -pedantic
DEBUGGING_FLAGS = -g -O0
CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS)

all: csim

csim: main.o Cache.o Set.o helper.o
	g++ -o csim main.o Cache.o Set.o helper.o -lm

main.o: main.cpp Cache.h Set.h helper.h
	g++ -c main.cpp $(CFLAGS)

helper.o: helper.cpp helper.h Cache.h Set.h
	g++ -c helper.cpp $(CFLAGS)

Cache.o: Cache.cpp Cache.h Set.h
	g++ -c Cache.cpp $(CFLAGS)

Set.o: Set.cpp Set.h
	g++ -c Set.cpp $(CFLAGS)

clean :
	rm -f *.o csim depend.mak 

depend.mak :
	touch $@

depend :
	g++ -M $(CPP_SRCS) > depend.mak

include depend.mak
