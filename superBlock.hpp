#ifndef SUPER_BLOCK_HPP
#define SUPER_BLOCK_HPP

#include "inode.hpp"
#include "block.hpp"

#define NUM_OF_INODES 10
#define NUM_OF_BLOCKS 100
#define SIZE_OF_INODE sizeof(Inode)
#define SIZE_OF_BLOCK sizeof(Block)

class SuperBlock
{
    private:
    int numOfInodes;
    int numOfBlocks;
    int sizeOfBlock;
    int sizeOfInode;
    int numOfFreeBlocks;
    int numOfFreeInodes;

    public:
    SuperBlock();
    SuperBlock(int numOfInodes, int numOfBlocks);
    ~SuperBlock();

    int getNumOfInodes(){return this->numOfInodes;}
    int getNumOfBlocks(){return this->numOfBlocks;}
    int getSizeOfBlock(){return this->sizeOfBlock;}
    int getSizeOfInode(){return this->sizeOfInode;}
    int getNumOfFreeBlocks(){return this->numOfFreeBlocks;}
    int getNumOfFreeInodes(){return this->numOfFreeInodes;}

    void setNumOfInodes(int numOfInodes){this->numOfInodes = numOfInodes;}
    void setNumOfBlocks(int numOfBlocks){this->numOfBlocks = numOfBlocks;}
    void setSizeOfBlock(int sizeOfBlock){this->sizeOfBlock = sizeOfBlock;}
    void setSizeOfInode(int sizeOfInode){this->sizeOfInode = sizeOfInode;}
    void setNumOfFreeBlocks(int numOfFreeBlocks){this->numOfFreeBlocks = numOfFreeBlocks;}
    void setNumOfFreeInodes(int numOfFreeInodes){this->numOfFreeInodes = numOfFreeInodes;}
};

#endif