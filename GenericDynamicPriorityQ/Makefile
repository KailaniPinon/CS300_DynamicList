#############################################################################
# File name:	Makefile
# Author:		Kailani Pinon
# Date:			10.11.2020
# Class:		CS 300
# Assignment:	Generic Dynamic Priority Queue
# Purpose:		This file defines terminal-friendly actions for the
#				GenericDynamicPriorityQ
#############################################################################

CC=gcc
CFLAGS=-Wall -g

.PHONY: all clean

all: bin bin/pqueuedriver

bin:
	mkdir -p bin

#executable and dependencies
bin/pqueuedriver: bin/pqueuedriver.o bin/pqueue.o \
../GenericDynamicList/bin/list.o
	${CC} ${CFLAGS} bin/pqueuedriver.o bin/pqueue.o \
	../GenericDynamicList/bin/list.o -o bin/pqueuedriver

#driver object and dependencies, needed for executable (see line 22)
bin/pqueuedriver.o: src/pqueuedriver.c include/pqueue.h
	${CC} ${CFLAGS} -c src/pqueuedriver.c -o bin/pqueuedriver.o

#pqueue object and dependencies, needed for executable (see line 22)
bin/pqueue.o: src/pqueue.c include/pqueue.h \
../GenericDynamicList/include/list.h
	${CC} ${CFLAGS} -c src/pqueue.c -o bin/pqueue.o

#rebuild list
../GenericDynamicList/bin/list.o:
	cd ../GenericDynamicList; make bin/list.o

#for memory leak debugging in the terminal
valgrind: bin/pqueuedriver
	valgrind -v --leak-check=yes --track-origins=yes --leak-check=full \
	 --showleak-kinds=all bin/pqueuedriver

#one directory out from list and pq
tarball: clean
	tar czf ../cs300_3_pino3567.tar.gz ../../CS300_DynamicList

clean:
	rm -rf bin/*.o bin/pqueuedriver #../GenericDynamicList/bin/list.o
	#still haven't decided if I need the list.o yet. so still commented out
	