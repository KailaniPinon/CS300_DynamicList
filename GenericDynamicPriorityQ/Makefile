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

#TARGETS: executables
TARGETS=bin/pqueuedriver ../GenericDynamicList/bin/list

all: bin bin/pqueuedriver

bin:
	mkdir -p bin

#note to self: \ indicates break in line, for reading conveniences
bin/pqueuedriver: bin/pqueuedriver.o bin/pqueue.o \
../GenericDynamicList/bin/list.o
	${CC} ${CFLAGS} bin/pqueuedriver.o bin/pqueue.o \
	../GenericDynamicList/bin/list.o -o bin/pqueuedriver

bin/pqueuedriver.o: src/pqueuedriver.c include/pqueue.h
	${CC} ${CFLAGS} -c -o src/pqueuedriver.c bin/pqueuedriver.o

bin/pqueue.o: src/pqueue.c include/pqueue.h
	${CC} ${CFLAGS} -c -o src/pqueue.c bin/pqueue.o
	
../GenericDynamicList/bin/list.o:
	cd ../GenericDynamicList; make bin/list.o

valgrind: bin/pqueuedriver
	valgrind -v --leak-check=yes --track-origins=yes --leak-check=full \
	 --showleak-kinds=all bin/pqueuedriver

tarball: clean
	tar czf ../cs300_3_pino3567.tar.gz ../../CS300_DynamicList

clean:
	rm -rf bin/*.o ${TARGETS}
	