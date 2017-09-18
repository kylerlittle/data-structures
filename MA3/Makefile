#
# Makefile framework for CptS223
#
# Hacked up by Aaron Crandall, 2017
#

# Variables
GPP     = g++
CFLAGS  = -g -std=c++11 #-static
RM      = rm -f
BINNAME = levelsort

# Shell gives make a full user environment
# Adding this to PATH will find the newer g++ compiler on the old EECS servers.
SHELL := /bin/bash
PATH := /opt/rh/devtoolset-3/root/usr/bin/:$(PATH)


# Default is what happenes when you call make with no options
#  In this case, it requires that 'all' is completed
default: all

# All is the normal default for most Makefiles
#  In this case, it requires that build is completed
all: build

# build depends upon main.cpp, then runs the command:
#  g++ -g -std=c++11 -o levelsort
build: main.cpp
	$(GPP) $(CFLAGS) -o $(BINNAME) main.cpp

run: build
	./$(BINNAME)

test: build
	./$(BINNAME) --test

bigtest: build
	./$(BINNAME) --bigtest

# If you call "make clean" it will remove the built program
#  rm -f levelsort
clean veryclean:
	$(RM) $(BINNAME)

# If you call "make starwars" it'll give you Star Wars!"
starwars:
	telnet towel.blinkenlights.nl

