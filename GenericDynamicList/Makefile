#############################################################################
# File name:	Makefile
# Author:		Kailani Pinon
# Date:			10.05.2020
# Class:		CS 300
# Assignment:	Generic Dynamic List
# Purpose:		This file defines terminal-friendly actions in realtion to
#				the Generic Dynamic List project.
#############################################################################
 
CC=gcc
CFLAGS=-Wall -g

.PHONY: all clean

all: bin bin/listdriver

bin:
	mkdir -p bin

bin/listdriver: bin/listdriver.o bin/list.o
	${CC} ${CFLAGS} bin/listdriver.o bin/list.o -o bin/listdriver

bin/listdriver.o: src/listdriver.c include/list.h
	${CC} ${CFLAGS} -c src/listdriver.c -o bin/listdriver.o

bin/list.o: src/list.c include/list.h
	${CC} ${CFLAGS} -c src/list.c -o bin/list.o

tarball: clean
	tar czf ../cs300_2B_pino3567.tar.gz ../GenericDynamicList

clean:
	rm -rf bin/*.o bin/listdriver