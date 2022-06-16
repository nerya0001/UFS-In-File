
#include <iostream>
#include <string>

#include "fileSystem.hpp"
#include "inode.hpp"
#include "block.hpp"
#include "superBlock.hpp"


int main()
{
    std::cout << "writing the sentence: hello my name is josh and i am a student to a file" << std::endl;
    std::string s = "hello my name is josh and i am a student"; // string to write to file
    std::string s2;
    int p[3] = {0,1,0};
    int p2[3] = {1,1,0};
    std::cout << "Creating file system..." << std::endl;
    FileSystem fs = FileSystem(10, 100);
    std::cout << "Creating file..." << std::endl;
    int fd = fs.myOpen("hello.txt", p);
    std::cout << "Writing to file..." << std::endl;
    fs.myWrite(fd, s, s.length());
    std::cout << "Reading from file..." << std::endl;
    fs.myClose(fd);
    std::cout << "Writing file system to file..." << std::endl;
    fs.writeToFile("test.txt");
    std::cout << "Reading file..." << std::endl;
    int fd2 = fs.myOpen("hello.txt", p2);
    std::cout << fs.myRead(fd2, s2, s.length()) << std::endl;
    return 0;
}