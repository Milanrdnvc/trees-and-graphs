#ifndef _tree_h_
#define _tree_h_

#include <iostream>

using namespace std;

class Tree {
    struct Node {
        string f;
        Node* left;
        Node* next;

        Node(string f, Node* left = nullptr, Node* next = nullptr) : f(f), left(left), next(next) {}
    };

public:
    Tree() = default;
    Tree(const Tree&) = delete;
    Tree& operator=(const Tree&) = delete;

    void addStackToTree(string stack);
    Node* searchLevelOrder(Node* root, string f);

    ~Tree();
private:
    Node* root = nullptr;
};

#endif