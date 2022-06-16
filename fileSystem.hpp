#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include <string>
#include "inode.hpp"
#include "block.hpp"
#include "superBlock.hpp"

typedef struct fdstruct {
    int fd = -1;
    int permissions[3] = {0, 0, 0};
    int offset = 0;
} fdstruct;

class FileSystem {
    private:
    SuperBlock superBlock;
    Inode* inodes;
    Block* blocks;
    //table of open file descriptors
    fdstruct* openFileDescriptors;
    int nextavailablefd = 0;

    public:
    FileSystem();
    FileSystem(int inodes, int blocks);
    ~FileSystem();


    int myOpen(std::string fileName, int permissions[3]);
    int myClose(int fd);
    std::string myRead(int fd, std::string buffer, int count);
    int myWrite(int fd, std::string buffer, int size);
    int mylSeek(int fd, int offset, int whence);
    int createFile(std::string fileName, int permissions[3]);
    void writeToFile(std::string filename); // write the file system to a file


    SuperBlock getSuperBlock(){return this->superBlock;}
    Inode* getInodes(){return this->inodes;}
    Block* getBlocks(){return this->blocks;}
    fdstruct* getOpenFileDescriptors(){return this->openFileDescriptors;}
    int getInodeIndex(std::string fileName);
   


    void setSuperBlock(SuperBlock superBlock){this->superBlock = superBlock;}
    void setInodes(Inode* inodes){this->inodes = inodes;}
    void setBlocks(Block* blocks){this->blocks = blocks;}
    void setOpenFileDescriptors(fdstruct* openFileDescriptors){this->openFileDescriptors = openFileDescriptors;}
};

#endif