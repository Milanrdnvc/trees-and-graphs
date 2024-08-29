#include "../h/fileReader.h"

int FileReader::cnt = 0;

FileReader::FileReader(string name) {
    this->name = name;
    this->len = -1;
    this->stackArray = nullptr;
}

FileReader *FileReader::createFileReader(string name)  {
    cnt++;
    if (cnt > 1) return nullptr;
    return new FileReader(name);
}
