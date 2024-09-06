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

void Tree::addStacksToTree(FileReader::StackNode *head) {
    if (!head) return;

    this->head = head;
    FileReader::StackNode* curr = head;

    while (curr->next) {
        addStackToTree(curr->stack);
        curr = curr->next;
    }
    addStackToTree(curr->stack);
    this->tail = curr;
}

void Tree::addStackToLinkedList(string stack) {
    if (!head) {
        head = tail = new FileReader::StackNode(stack);
        return;
    }

    if (!head->next) {
        head->next = new FileReader::StackNode(stack);
        head->next->prev = head;
        tail = head->next;
        return;
    }

    tail->next = new FileReader::StackNode(stack);
    tail->next->prev = tail;
    tail = tail->next;
}

bool Tree::removeStackFromLinkedList(string stack) {
    if (!head) return false;
    bool found = false;

    FileReader::StackNode* curr = head;

    while (curr) {
        if (curr->stack == stack) {
            found = true;
            break;
        }
        curr = curr->next;
    }

    if (!found) return false;

    if (curr == head) {
        FileReader::StackNode* old = head;
        head = curr->next;
        if (head) head->prev = nullptr;
        else head = tail = nullptr;
        delete old;
        return true;
    }

    if (curr == tail) {
        FileReader::StackNode* old = tail;
        tail = curr->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete old;
        return true;
    }

    FileReader::StackNode* old = curr;
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
    delete old;
    return true;
}

void Tree::rebuildTree() {
    freeTree();
    addStacksToTree(head);
}

void Tree::printTree() const {
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

        cout << currNode->f << " ";

        Node* curr = currNode->next;

        while (curr) {
            if (curr->left != nullptr) {
                q.insertQ(curr->left);
            }
            cout << curr->f << " ";
            curr = curr->next;
        }

        if (q.frontQ() == nullptr) {
            q.insertQ(nullptr);
            q.deleteQ();
            cout << endl;
            cout << "-----------" << endl;
        }
    }
}

void Tree::freeTree() {
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

Tree::Node* Tree::getRoot() const {
    return root;
}

Tree::~Tree() {
    freeTree();
}