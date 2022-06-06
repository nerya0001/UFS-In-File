CC=g++
AR=ar
FLAGS=-Wall -g


all: main

main: main.o libufs.a
	$(CC) $(FLAGS) -o main main.o libufs.a

libufs.a: block.o inode.o superBlock.o
	$(AR) -rcs libufs.a block.o inode.o superBlock.o

main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp

block.o: block.cpp block.hpp 
	$(CC) $(FLAGS) -c block.cpp

inode.o: inode.cpp inode.hpp 
	$(CC) $(FLAGS) -c inode.cpp

superBlock.o: superBlock.cpp superBlock.hpp 
	$(CC) $(FLAGS) -c superBlock.cpp



.PHONY: clean all

clean:
	rm -f *.o *.a main 



