#include "../h/tree.h"
#include "../h/queue.h"
#include <sstream>

Tree::Node *Tree::searchLevelOrder(Node* root, string f) {
    Queue<Node> q;

    Node* currNode = root;

    if (currNode->left != nullptr) {
        q.insertQ(currNode->left);
    }
    else {
        q.insertQ(nullptr);
    }

    Node* currLevelNode = q.deleteQ();

    if (currLevelNode == nullptr) return nullptr;

    if (currLevelNode->f == f) {
        return currLevelNode;
    }

    Node* curr = currLevelNode->next;

    while (curr) {
        if (curr->f == f) return curr;
        curr = curr->next;
    }

    return nullptr;
}

void Tree::addStackToTree(string stack) {
    istringstream iss(stack);
    string function;

    Node* currNode = nullptr;

    while (getline(iss, function, ' ')) {
        if (function == "main") {
            if (root) {
                currNode = root;
                continue;
            }

            root = new Node("main");
            currNode = root;
        }

        else {
            if (currNode == nullptr) return;

            Node* foundNode = searchLevelOrder(currNode, function);

            if (foundNode == nullptr) {
                Node* newNode = new Node(function);

                if (currNode->left == nullptr) {
                    currNode->left = newNode;
                    currNode = newNode;
                }
                else {
                    Node* curr = currNode->left;

                    while (curr->next != nullptr) {
                        curr = curr->next;
                    }

                    curr->next = newNode;
                    currNode = newNode;
                }
            }
            else {
                currNode = foundNode;
            }
        }
    }
}

Tree::~Tree() {
    if (!root) return;

    Queue<Node> q;

    Node* currNode = root;

    q.insertQ(currNode);
    q.insertQ(nullptr);

    while (q.frontQ() != nullptr) {
        currNode = q.deleteQ();

        if (currNode->left != nullptr) {
            q.insertQ(currNode->left);
        }

        Node* curr = currNode->next;

        delete currNode;

        while (curr) {
            if (curr->left != nullptr) {
                q.insertQ(curr->left);
            }
            Node* old = curr;
            curr = curr->next;
            delete old;
        }

        if (q.frontQ() == nullptr) {
            q.insertQ(nullptr);
            q.deleteQ();
        }
    }

    root = nullptr;
}