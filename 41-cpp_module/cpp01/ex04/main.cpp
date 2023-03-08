//
// Created by Junhyuk Ji on 3/8/23.
//

#include <iostream>
#include <string>
#include <fstream>

void    put_error(const char *str)
{
    std::cout << str << '\n';
    exit(1);
}


int main(int argc, char *argv[])
{
    std::string buffer;
    std::string file_name;

    file_name = argv[1];
    file_name.append(".replace");
    if (argc != 4)
        put_error("인자가 올바르지 않습니다.");
    std::ifstream infile;
    infile.open(argv[1]);
    if (infile.fail())
    {
        std::cout << strerror(errno);
        return (1);
    }
    infile >> buffer;
    infile.close();
    std::ofstream outfile;
    outfile.open(file_name);
    std::string is_found;
    is_found = buffer.find("hello");

    std::cout << is_found << '\n';

    std::cout << buffer;
}
