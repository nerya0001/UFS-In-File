#include "superBlock.hpp"

SuperBlock::SuperBlock()
{
    this->numOfInodes = 10;
    this->numOfBlocks = 100;
    this->numOfFreeInodes = this->numOfInodes;
    this->numOfFreeBlocks = this->numOfBlocks;
    this->sizeOfInode = sizeof(Inode);
    this->sizeOfBlock = sizeof(Block);
}


SuperBlock::SuperBlock(int numOfInodes, int numOfBlocks)
{
    this->numOfInodes = numOfInodes;
    this->numOfBlocks = numOfBlocks;
    this->numOfFreeInodes = this->numOfInodes;
    this->numOfFreeBlocks = this->numOfBlocks;
    this->sizeOfInode = sizeof(Inode);
    this->sizeOfBlock = sizeof(Block);
}


SuperBlock::~SuperBlock()
{
}
