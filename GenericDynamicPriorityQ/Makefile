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

#-g 	: includes debug symbols
#-Wall	: shows gcc warnings

.PHONY: all clean

TARGETS= bin/pqueuedriver  bin/pqueuedriver

all: bin ${TARGETS}

bin:
	mkdir -p bin
#current issue: make clean removes from bin, and issues
#repopulating bin

#executable and dependencies
bin/pqueuedriver: bin/pqueuedriver.o bin/pqueue.o \
	../GenericDynamicList/bin/list.o
	${CC} ${CFLAGS} -o bin/pqueuedriver bin/pqueuedriver.o \
	bin/pqueue.o ../GenericDynamicList/bin/list.o

#driver object and dependencies, needed for executable
bin/pqueuedriver.o: src/pqueuedriver.c include/pqueue.h \
	../GenericDynamicList/include/list.h
	${CC} ${CFLAGS} -c -o bin/pqueuedriver.o src/pqueuedriver.c

#pqueue object and dependencies, needed for executable
bin/pqueue.o: src/pqueue.c include/pqueue.h \
	../GenericDynamicList/include/list.h
	${CC} ${CFLAGS} -c -o bin/pqueue.o src/pqueue.c 

#rebuild list
../GenericDynamicList/bin/list.o:
	cd ../GenericDynamicList; \
	make bin/list.o

#for memory leak debugging in the terminal
valgrind: bin/pqueuedriver
	valgrind -v --leak-check=yes --track-origins=yes --leak-check=full \
	--show-leak-kinds=all bin/pqueuedriver

#one directory out from list and pq
tarball: clean
	tar czf ../cs300_3_pino3567.tar.gz ../../CS300_DynamicList \
	../CS300_DynamicPriorityQ

clean:
	rm -rf bin/*.o ${TARGETS}