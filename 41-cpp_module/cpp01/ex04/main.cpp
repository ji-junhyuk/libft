//
// Created by Junhyuk Ji on 3/8/23.
//

#include "CreateReplacedFile.hpp"

void    put_error(const char *str)
{
    std::cout << str << '\n';
    exit(1);
}

int main(int argc, char *argv[])
{
    if (argc != 4)
        put_error("인자가 올바르지 않습니다.");
    CreateReplacedFile createReplacedFile(argv[1]);

    createReplacedFile.ReadBuffer(argv[1]);
    createReplacedFile.ReplaceContent(argv[2], argv[3]);
}
