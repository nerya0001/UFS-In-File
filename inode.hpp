#ifndef INODE_HPP
#define INODE_HPP

#include <string>


enum InodeType {
    MYFILE,
    MYDIRECTORY
};



class Inode {
    private :
        int size;
        std::string name;
        InodeType type;
        int firstBlockNum;
        int permissions[3]; //bitmap for permissions (read, write, execute) will check with &

    public :
        Inode();
        Inode(std::string name, int permissions[3]);
        ~Inode();

        int getSize(){return this->size;}
        std::string getName(){return this->name;}
        InodeType getType(){return this->type;}
        int getFirstBlockNum(){return this->firstBlockNum;}
        int getPermissions(int index){return this->permissions[index];}

        void setSize(int size){this->size = size;}
        void setName(std::string name){this->name = name;}
        void setType(InodeType type){this->type = type;}  
        void setFirstBlockNum(int firstBlockNum){this->firstBlockNum = firstBlockNum;}
        void setPermissions(int permissions[3]){
            this->permissions[0] = permissions[0];
            this->permissions[1] = permissions[1];
            this->permissions[2] = permissions[2];
        }
        
};
    

#endif