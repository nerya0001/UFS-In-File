
#include <iostream>
#include <string>

#include "fileSystem.hpp"
#include "inode.hpp"
#include "block.hpp"
#include "superBlock.hpp"


int main()
{
    std::string s = "hello my name is josh and i am a student"; // string to write to file
    std::string s2;
    int p[3] = {0,1,0};
    int p2[3] = {1,1,0};
    FileSystem fs = FileSystem(10, 100);
    int fd = fs.myOpen("hello.txt", p);
    fs.myWrite(fd, s, s.length());
    fs.myClose(fd);
    fs.writeToFile("test.txt");
    int fd2 = fs.myOpen("hello.txt", p2);
    std::cout << fs.myRead(fd2, s2, s.length()) << std::endl;
    return 0;
}