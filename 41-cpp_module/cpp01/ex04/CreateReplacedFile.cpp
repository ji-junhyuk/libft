//
// Created by Junhyuk Ji on 3/9/23.
//

#include "CreateReplacedFile.hpp"

CreateReplacedFile::CreateReplacedFile(const char *file_name) {
    mReplacedFileName = file_name;
    mReplacedFileName.append(".replace");
}

void CreateReplacedFile::ReadBuffer(const char *file_name) {
    mInfile.open(file_name);
    if (mInfile.fail())
    {
        std::cout << strerror(errno);
        exit(1);
    }
    mInfile.seekg(0, std::ios::end);
    std::streampos size = mInfile.tellg();
    mBuffer.resize(size);
    mInfile.seekg(0, std::ios::beg);
    mInfile.read(&mBuffer[0], size);
    mInfile.close();
}

void CreateReplacedFile::ReplaceContent(const char *before, const char *after) {

    mOutfile.open(mReplacedFileName);
    std::size_t is_found = mBuffer.find(before);
    while (is_found != std::string::npos)
    {
        mBuffer.erase(is_found, strlen(before));
        mBuffer.insert(is_found, after);
        is_found = mBuffer.find(before);
    }
    mOutfile << mBuffer;
    mOutfile.close();
}
