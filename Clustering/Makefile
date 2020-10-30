#
# In order to execute this "Makefile" just type "make"
#
OBJS 	= main.o clustering_functions.o class_functions.o
SOURCE	= main.c clustering_functions.cpp class_functions.cpp
HEADER  = classes.hpp
OUT  	= cluster
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

class_functions.o: class_functions.cpp
	$(CC) $(FLAGS) class_functions.cpp

clustering_functions.o: clustering_functions.cpp
	$(CC) $(FLAGS) clustering_functions.cpp

# clean house
clean:
	rm -f $(OBJS) $(OUT) gpgme*
