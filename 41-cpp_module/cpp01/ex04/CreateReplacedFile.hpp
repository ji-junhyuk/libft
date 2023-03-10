//
// Created by Junhyuk Ji on 3/9/23.
//

#ifndef INC_42COURSE_CREATEREPLACEDFILE_HPP
#define INC_42COURSE_CREATEREPLACEDFILE_HPP

#include <string>
#include <fstream>
#include <iostream>

class CreateReplacedFile {

private:
    std::string mReplacedFileName;
    std::string mBuffer;
    std::ifstream mInfile;
    std::ofstream mOutfile;

public:
    CreateReplacedFile(const char *file_name);
    void ReadBuffer(const char *file_name);
    void ReplaceContent(const char *before, const char *after);
};

#endif //INC_42COURSE_CREATEREPLACEDFILE_HPP