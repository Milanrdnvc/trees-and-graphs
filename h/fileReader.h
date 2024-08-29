#ifndef _fileReader_h_
#define _fileReader_h_

#include <iostream>

using namespace std;

class FileReader {
public:
    static FileReader* createFileReader(string name);

    void loadStacks();
private:
    FileReader(string name);
    FileReader(const FileReader&) = delete;

    FileReader& operator=(const FileReader&) = delete;

    string name;
    string* stackArray;
    int len;
    static int cnt;
};

#endif