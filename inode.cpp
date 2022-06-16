#include "inode.hpp"


Inode::Inode()
{
    this->size = 0;
    this->name = "";
}



Inode::Inode(std::string name, int permissions[3]) {
    this->name = name;
    this->permissions[0] = permissions[0];
    this->permissions[1] = permissions[1];
    this->permissions[2] = permissions[2];
 
}


Inode::~Inode()
{
}