#include <fstream>
#include <sstream>
#include "../h/fileReader.h"

using namespace std;

int FileReader::cnt = 0;

FileReader::FileReader(string name) {
    this->name = name;
    this->head = this->tail = nullptr;
}

FileReader::~FileReader() {
    StackNode* curr = head;

    while (curr) {
        StackNode* old = curr;
        curr = curr->next;
        delete old;
    }

    head = tail = nullptr;
}

FileReader *FileReader::createFileReader(string name)  {
    cnt++;
    if (cnt > 1) return nullptr;
    return new FileReader(name);
}

void FileReader::loadStacks() {
    if (head) return;

    ifstream file(name);
    string stack;

    while (getline(file, stack)) {
        if (!head) {
            head = tail = new StackNode(stack);
            continue;
        }

        if (!head->next) {
            head->next = new StackNode(stack);
            head->next->prev = head;
            tail = head->next;
            continue;
        }

        tail->next = new StackNode(stack);
        tail->next->prev = tail;
        tail = tail->next;
    }

    file.close();
}

FileReader::StackNode* FileReader::getHead() const {
    return head;
}

FileReader::StackNode* FileReader::getTail() const {
    return tail;
}



