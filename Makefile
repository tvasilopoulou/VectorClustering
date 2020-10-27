#
# In order to execute this "Makefile" just type "make"
#

OBJS 	= main.o genericFuncs.o classFuncs.o
SOURCE	= main.c genericFuncs.cpp classFuncs.cpp
HEADER  = header.hpp funcHeader.hpp
OUT  	= lsh
CC	= g++
FLAGS   = -c #-g -Wall
# flags=$(shell gpgme-config --libs --cflags)
#-g -c -pedantic -ansi  -Wall
# -g option enables debugging mode
# -c flag generates object code for separate files

$(OUT): $(OBJS)
	$(CC) -g $(OBJS) -o $@

# create/compile the individual files >>separately<< 
main.o: main.cpp
	$(CC) $(FLAGS) main.cpp

genericFuncs.o: genericFuncs.cpp
	$(CC) $(FLAGS) genericFuncs.cpp

# clean house
clean:
	rm -f $(OBJS) $(OUT) gpgme*
