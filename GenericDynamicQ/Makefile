#############################################################################
# File name:	Makefile
# Author:		Kailani Pinon
# Date:			10..2020
# Class:		CS 300
# Assignment:	Generic Dynamic Queue
# Purpose:		This file defines terminal-friendly actions for the
#				GenericDynamicQ
#############################################################################

CC=gcc
CFLAGS=-Wall -g

.PHONY: all clean

all: bin bin/queuedriver

bin:
	mkdir -p bin
	
#executable and dependencies
bin/queuedriver: bin/queuedriver.o bin/queue.o \
../GenericDynamicPriorityQ/bin/pqueue.o \
../GenericDynamicList/bin/list.o
	${CC} ${CFLAGS} -o bin/queuedriver bin/queuedriver.o \
	bin/queue.o \
	../GenericDynamicPriorityQ/bin/pqueue.o \
	../GenericDynamicList/bin/list.o
	
	
#driver object and dependencies
bin/queuedriver.o: src/queuedriver.c include/queue.h \
../GenericDynamicPriorityQ/src/pqueue.c \
../GenericDynamicList/src/list.c \
../GenericDynamicPriorityQ/include/pqueue.h \
../GenericDynamicList/include/list.h
	${CC} ${CFLAGS} -c src/queuedriver.c -o bin/queuedriver.o
#get rid of src (.c)	
#dependencies objects
bin/pqueue.o: ../GenericDynamicPriorityQ/src/pqueue.c \
../GenericDynamicPriorityQ/src/pqueue.c \
../GenericDynamicList/src/list.c \
../GenericDynamicPriorityQ/include/pqueue.h \
../GenericDynamicList/include/list.h
	${CC} ${CFLAGS} -c src/pqueue.c -o bin/pqueue.o

bin/queue.o: src/queue.c include/queue.h \
../GenericDynamicPriorityQ/include/pqueue.h \
../GenericDynamicList/include/list.h
	${CC} ${CFLAGS} -c src/queue.c -o bin/queue.o
	
#rebuild list and priority queue
../GenericDynamicList/bin/list.o:
	cd ../GenericDynamicList; make bin/list.o
	
../GenericDynamicPriorityQ/bin/pqueue.o:
	cd ../GenericDynamicPriorityQ; make bin/pqueue.o

#valgrind for memory leak debugging
valgrind: bin/pqueuedriver
	valgrind -v --leak-check=yes --track-origins=yes --leak-check=full \
	 --showleak-kinds=all bin/pqueuedriver

#zipping (tarball)
tarball: clean
	tar czf ../../cs300_3_pino3567.tar.gz ../../CS300_DynamicList

#clean
clean:
	cd ../GenericDynamicList; make clean
	cd ../GenericDynamicPriorityQ; make clean
	cd ../GenericDynamicQueue; make clean
	rm -f bin/*.o bin/airportdriver
	