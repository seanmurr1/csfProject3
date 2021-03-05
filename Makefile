#
# Makefile for CSF Assignment 3
#


CPP_SRCS = Cache.cpp main.cpp Set.cpp
CFLAGS = -g -Wall -Wextra -pedantic 

%.o : %.cpp
	g++ $(CFLAGS) -c $<

all : csim

csim : Cache.o main.o Set.o
	g++ -o $@ Cache.o main.o Set.o -lm


clean :
	rm -f *.o csim depend.mak 

depend.mak :
	touch $@

depend :
	g++ -M $(CPP_SRCS) > depend.mak

include depend.mak