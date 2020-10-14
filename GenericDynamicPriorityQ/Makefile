#############################################################################
# File name:	Makefile
# Author:		Kailani Pinon
# Date:			10.11.2020
# Class:		CS 300
# Assignment:	Generic Dynamic Priority Queue
# Purpose:		This file defines terminal-friendly actions in realtion to
#				the Generic Dynamic Priority Queue project.
#############################################################################

CC=gcc
CFLAGS=-Wall -g

.PHONY: all clean

all: bin bin/pqueuedriver

bin:
	mkdir -p bin

#creating Priority Queue - related files	
bin/pqueuedriver: bin/pqueuedriver.o bin/pqueue.o
	${CC} ${CFLAGS} bin/pqueuedriver.o bin/pqueue.o -o bin/pqueuedriver

bin/pqueuedriver.o: src/pqueuedriver.c include/pqueue.h
	${CC} ${CFLAGS} -c src/pqueuedriver.c -o bin/pqueuedriver.o

bin/pqueue.o: src/pqueue.c include/pqueue.h
	${CC} ${CFLAGS} -c src/pqueue.c -o bin/pqueue.o
	
#linking List and Priority Queue
bin/pqueue: bin/pqueue.o \
../GenericDynamicList/bin/list.o
	gcc -o bin/pqueue bin/pqueue.o \ 
	../GenericDynamicList/bin/list.o -g -Wall
	#do I even need lines 34-35 if I'm doing similar on line 28?
	
bin/pqueue.o: src/pqueue.c \
../GenericDynamicList/include/list.h
	gcc -c -o bin/pqueue.o src/pqueue.c -g -Wall
	#do I even need lines 34-35 if I'm doing similar on line 26?
		
../GenericDynamicList/bin/GenericDynamicList.o:
	cd ../GenericDynamicList; make bin/GenericDynamicList.o

#additional commands
valgrind: bin/pqueuedriver
	valgrind -v --leak-check=yes --track-origins=yes --leak-check=full --showleak-kinds=all bin/pqueuedriver

tarball: clean
	tar czf ../cs300_3_pino3567.tar.gz ../../CS300_DynamicList

clean:
	rm -rf bin/*.o bin/GenericDynamicPriorityQ ../GenericDynamicList/bin/GenericDynamicList.o
	