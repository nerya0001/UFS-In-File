#include "block.hpp"


Block::Block()
{
    this->data = new char[BLOCK_SIZE];
    // Initialize the data
    for (int i = 0; i < 2; i++)
    {
        this->data[i] = '$';
    }
    this->nextBlockNum = 0;
}


Block::Block(int nextBlockNum, std::string data)
{
    this->data = new char[BLOCK_SIZE];
    this->nextBlockNum = 0;
    this->data = data;
}


Block::~Block()
{
    
}