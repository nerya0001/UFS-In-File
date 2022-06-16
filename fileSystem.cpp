#include "fileSystem.hpp"


FileSystem::FileSystem()
{
    this->superBlock = SuperBlock(10, 100);
    this->inodes = new Inode[this->superBlock.getNumOfInodes()];
    this->blocks = new Block[this->superBlock.getNumOfBlocks()];
    this->openFileDescriptors = new fdstruct[100];

    // Initialize the inodes
    for (int i = 0; i < this->superBlock.getNumOfInodes(); i++)
    {
        this->inodes[i].setSize(-1);
        this->inodes[i].setName("");
    }

    // Initialize the blocks
    for (int i = 0; i < this->superBlock.getNumOfBlocks(); i++)
    {
        this->blocks[i].setNextBlockNum(-1);
    }
}


FileSystem::FileSystem(int inodes, int blocks)
{
    this->superBlock = SuperBlock(inodes, blocks);
    this->inodes = new Inode[this->superBlock.getNumOfInodes()];
    this->blocks = new Block[this->superBlock.getNumOfBlocks()];
    this->openFileDescriptors = new fdstruct[100];

    // Initialize the inodes
    for (int i = 0; i < 2; i++)
    {
        this->inodes[i].setSize(-1);
        this->inodes[i].setName("");
    }

    // Initialize the blocks
    for (int i = 0; i < 3; i++)
    {
        this->blocks[i].setNextBlockNum(-1);
    }
}


FileSystem::~FileSystem()
{
    delete[] this->inodes;
    delete[] this->blocks;
    delete[] this->openFileDescriptors;
}


void FileSystem::writeToFile(std::string filename)
{
    // Open the file
    FILE *file = fopen(filename.c_str(), "w");

    // Write the super block
    fwrite(&this->superBlock, sizeof(SuperBlock), 1, file);

    // Write the inodes
    fwrite(this->inodes, sizeof(Inode), this->superBlock.getNumOfInodes(), file);

    // Write the blocks
    fwrite(this->blocks, sizeof(Block), this->superBlock.getNumOfBlocks(), file);

    // Close the file
    fclose(file);
}

// create a file with the given name and permissions add the fd to the open fds table
// and return the file descriptor
int FileSystem::createFile(std::string fileName, int permissions[3])
{
    // find the first available inode
    int inodeIndex = -1;
    for (int i = 0; i < this->superBlock.getNumOfInodes(); i++)
    {
        if (this->inodes[i].getSize() == -1)
        {
            inodeIndex = i;
            break;
        }
    }

    // if no inode is available, return -1
    if (inodeIndex == -1)
    {
        return -1;
    }

    this->inodes[inodeIndex].setName(fileName);
    this->inodes[inodeIndex].setType(MYFILE);
    this->inodes[inodeIndex].setPermissions(permissions);
    this->inodes[inodeIndex].setSize(0);
    fdstruct newfd;
    newfd.fd = this->nextavailablefd;
    this->nextavailablefd++;
    // set the permissions of the file
    newfd.permissions[0] = permissions[0];
    newfd.permissions[1] = permissions[1];
    newfd.permissions[2] = permissions[2];

    this->openFileDescriptors[newfd.fd] = newfd;
    return newfd.fd;
}

int FileSystem::myOpen(std::string fileName, int permissions[3])
{
    // Check if the file exists if not create it
    int inodeIndex = this->getInodeIndex(fileName);
    int fd = -1;
    fdstruct newfd;
    // Check if the file is a directory
    if (this->inodes[inodeIndex].getType() == MYDIRECTORY)
    {
        return -1;
    }

    if (inodeIndex == -1)
    {
        fd = this->createFile(fileName, permissions);
        return fd;
    }
    else
    {
        fd = this->nextavailablefd;
        this->nextavailablefd++;
        newfd.fd = fd;
        newfd.permissions[0] = permissions[0];
        newfd.permissions[1] = permissions[1];
        newfd.permissions[2] = permissions[2];
        this->openFileDescriptors[fd] = newfd;
        return fd;
    }
}

std::string FileSystem::myRead(int fd, std::string buffer, int size)
{
    std::string fileContents = "";
    // Check if the file is open
    if (this->openFileDescriptors[fd].fd == -1)
    {
        return "file is not open";
    }

    // Check if the file is a directory
    if (this->inodes[fd].getType() == MYDIRECTORY)
    {
        return "file is a directory";
    }
    // check permissions
    if (this->openFileDescriptors[fd].permissions[0] == 0)
    {
        return "permission denied";
    }
    // Read the file
    for (int i = 0; i < size; i++)
    {
        fileContents += this->blocks[this->inodes[fd].getFirstBlockNum()].getData()[i];
    }
    return fileContents;
}

int FileSystem::myClose(int fd)
{
    // Check if the file is open
    if (this->openFileDescriptors[fd].fd == -1)
    {
        return -1;
    }

    // Close the file
    this->openFileDescriptors[fd].fd = -1;
    
    return 0;
}

int FileSystem::myWrite(int fd, std::string buffer, int size)
{
    // Check if the file is open
    if (this->inodes[fd].getSize() == -1)
    {
        return -1;
    }

    // Check if the file is a directory
    if (this->inodes[fd].getType() == MYDIRECTORY)
    {
        return -1;
    }

    // Check if the file is a file
    if (this->inodes[fd].getType() == MYFILE)
    {
        // Check if the file is writable
        if (this->inodes[fd].getPermissions(1) == 1)
        {
            // Check if the file is empty
            if (this->inodes[fd].getSize() == 0)
            {
                // Check if the file is too large
                if (size > this->superBlock.getSizeOfBlock())
                {
                    return -1;
                }

                // Write the file
                for (int i = 0; i < size; i++)
                {
                    this->blocks[this->inodes[fd].getFirstBlockNum()].setData(buffer);
                }

                this->inodes[fd].setSize(size);

                return size;
            }

            // Check if the file is too large
            if (size > this->superBlock.getSizeOfBlock())
            {
                return -1;
            }

            // Write the file
            for (int i = 0; i < size; i++)
            {
                this->blocks[this->inodes[fd].getFirstBlockNum()].getData()[i] = buffer[i];
            }

            this->inodes[fd].setSize(size);

            return size;
        }
    }

    // File is not writable
    return -1;
}



int FileSystem::getInodeIndex(std::string name)
{
    for (int i = 0; i < this->superBlock.getNumOfInodes(); i++)
    {
        if (this->inodes[i].getName() == name)
        {
            return i;
        }
    }

    return -1;
}