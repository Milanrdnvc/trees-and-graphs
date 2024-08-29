#ifndef _tree_h_
#define _tree_h_

#include <iostream>

using namespace std;

class Tree {
public:
    void addStackToTree();

private:
    struct Node {
        string f;
        Node* left;
        Node* next;

        Node(string f, Node* left = nullptr, Node* next = nullptr) : f(f), left(left), next(next) {}
    };

    Node* root = nullptr;
};

#endif