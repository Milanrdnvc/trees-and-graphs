#ifndef _fileReader_h_
#define _fileReader_h_

#include <iostream>

using namespace std;

class FileReader {
public:
    struct StackNode {
        string stack;
        StackNode* next;
        StackNode* prev;

        StackNode(string stack): stack(stack), next(nullptr), prev(nullptr) {}
    };

    static FileReader* createFileReader(string name);
    void loadStacks();
    string* getStackArray() const;
    int getStackArrayLen() const;
    StackNode* getHead() const;
    StackNode* getTail() const;

    ~FileReader();
private:
    FileReader(string name);
    FileReader(const FileReader&) = delete;
    FileReader& operator=(const FileReader&) = delete;

    string name;
    StackNode* head;
    StackNode* tail;
    static int cnt;
};

#endif