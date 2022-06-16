#ifndef BLOCK_HPP
#define BLOCK_HPP


#define BLOCK_SIZE 256

#include <string>

class Block {
    private:
        int nextBlockNum;
        std::string data;
    
    public:
        Block();
        Block(int nextBlockNum, std::string data);
        ~Block();
    
        int getNextBlockNum(){return this->nextBlockNum;}
        std::string getData(){return this->data;}
    
        void setNextBlockNum(int nextBlockNum){this->nextBlockNum = nextBlockNum;}
        void setData(std::string data){this->data = data;}
};

#endif