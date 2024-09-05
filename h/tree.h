#ifndef _tree_h_
#define _tree_h_

#include <iostream>
#include "../h/fileReader.h"

using namespace std;

class Tree {
    struct Node {
        string f;
        Node* left;
        Node* next;

        Node(string f, Node* left = nullptr, Node* next = nullptr) : f(f), left(left), next(next) {}
    };

    friend class Graph;

public:
    Tree() = default;
    Tree(const Tree&) = delete;
    Tree& operator=(const Tree&) = delete;

    void addStackToTree(string stack);
    void addStacksToTree(FileReader::StackNode* head);
    void addStackToLinkedList(string stack);
    bool removeStackFromLinkedList(string stack);
    void rebuildTree();
    void freeTree();
    Node* searchLevelOrder(Node* root, string f);
    void printTree() const;

    ~Tree();

private:
    Node* root = nullptr;
    FileReader::StackNode* head = nullptr;
    FileReader::StackNode* tail = nullptr;
};

#endif