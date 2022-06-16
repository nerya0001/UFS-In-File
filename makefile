CC=g++
AR=ar
FLAGS=-Wall -g


all: main

main: main.o libufs.so
	$(CC) $(FLAGS) -o main main.o ./libufs.so

libufs.so: block.o inode.o superBlock.o fileSystem.o
	$(CC) -shared -fPIC -o libufs.so block.o inode.o superBlock.o fileSystem.o

main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp

block.o: block.cpp block.hpp 
	$(CC) $(FLAGS) -c block.cpp

inode.o: inode.cpp inode.hpp 
	$(CC) $(FLAGS) -c inode.cpp

superBlock.o: superBlock.cpp superBlock.hpp 
	$(CC) $(FLAGS) -c superBlock.cpp

fileSystem.o: fileSystem.cpp fileSystem.hpp 
	$(CC) $(FLAGS) -c fileSystem.cpp



.PHONY: clean all

clean:
	rm -f *.o *.a *.so main 



