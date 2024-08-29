#include <fstream>
#include <sstream>
#include "../h/fileReader.h"

using namespace std;

int FileReader::cnt = 0;

FileReader::FileReader(string name) {
    this->name = name;
    this->len = -1;
    this->stackArray = nullptr;
}

FileReader::~FileReader() {
    delete[] stackArray;
}

FileReader *FileReader::createFileReader(string name)  {
    cnt++;
    if (cnt > 1) return nullptr;
    return new FileReader(name);
}

void FileReader::loadStacks() {
    if (len != -1 || stackArray != nullptr) return;

    ifstream file(name);
    string stack;

    while (getline(file, stack)) {
        len++;
    }
    len++;

    file.close();
    file.open(name);

    stackArray = new string[len];
    int idx = 0;

    while (getline(file, stack)) {
        stackArray[idx++] = stack;
    }

    file.close();
}

