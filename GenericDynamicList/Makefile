#############################################################################
# File name:	Makefile
# Author:		Kailani Pinon
# Date:			10.05.2020
# Class:		CS 300
# Assignment:	Generic Dynamic List
# Purpose:		This file defines terminal-friendly actions for the
#				Generic Dynamic List.
#############################################################################
 
CC=gcc
CFLAGS=-g -Wall

#-g 	: includes debug symbols
#-Wall	: shows gcc warnings

.PHONY: all clean

TARGETS=bin/listdriver

all: bin ${TARGETS}

bin:
	mkdir -p bin

#Create listdriver
bin/listdriver: bin/listdriver.o \
bin/list.o
	${CC} ${CFLAGS} -o bin/listdriver bin/listdriver.o \
	bin/list.o

bin/listdriver.o: src/listdriver.c include/list.h
	${CC} ${CFLAGS} -c -o bin/listdriver.o src/listdriver.c 

bin/list.o: src/list.c include/list.h
	${CC} ${CFLAGS} -c -o bin/list.o src/list.c 

tarball: clean
	tar czf ../cs300_2B_pino3567.tar.gz ../GenericDynamicList

clean:
	rm -rf bin/*.o ${TARGETS}