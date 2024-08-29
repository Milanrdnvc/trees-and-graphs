#ifndef _fileReader_h_
#define _fileReader_h_

#include <iostream>

using namespace std;

class FileReader {
public:
    FileReader* createFileReader(string name);

private:
    FileReader(string name);

    string name;
    string* stackArray;
    int len;
    static int cnt;
};

#endif