#include "../h/graph.h"
#include "../h/queue.h"

Graph::Node* Graph::existsInAhl(Node *head, string f) {
    Node* curr = head;

    while (curr) {
        if (curr->f == f) return curr;
        curr = curr->next;
    }

    return nullptr;
}

bool Graph::existsInAl(Node *head, string f) {
    Node* curr = head;

    while (curr) {
        if (curr->f == f) return true;
        curr = curr->next;
    }

    return false;
}

Graph::Node *Graph::addToAhl(Node *head, string f) {
    Node* curr = head;

    if (!head) {
        head = new Node(f, nullptr, nullptr);
        return head;
    }

    while (curr->next != nullptr) {
        curr = curr->next;
    }

    curr->next = new Node(f, nullptr, nullptr);
    return curr->next;
}

Graph::Node *Graph::addToAl(Node *head, string f) {
    if (!head) {
        head = new Node(f, nullptr, nullptr);
        return head;
    }

    Node* curr = head;

    if (!existsInAl(head, f)) {
        while (curr->next) {
            curr = curr->next;
        }

        curr->next = new Node(f, nullptr, nullptr);
        return curr->next;
    }
}


void Graph::convertTreeToGraph(Tree::Node *root) {
    if (!root) return;

    Node* headAdj = nullptr;

    Queue<Tree::Node> q;

    Tree::Node* currNode = root;

    q.insertQ(currNode);
    q.insertQ(nullptr);

    while (q.frontQ() != nullptr) {
        currNode = q.deleteQ();

        if (currNode->left != nullptr) {
            q.insertQ(currNode->left);
        }

        Tree::Node* currSibling = currNode->next;

        while (currSibling) {
            q.insertQ(currSibling->left);
            currSibling = currSibling->next;
        }

        currSibling = currNode;

        while (currSibling) {
            Node* exists = existsInAhl(headAdj, currSibling->f);

            if (!exists) {
                if (!headAdj) {
                    headAdj = addToAhl(headAdj, currSibling->f);
                    exists = headAdj;
                }
                else {
                    exists = addToAhl(headAdj, currSibling->f);
                }
            }

            Tree::Node* curr = currSibling->left;

            while (curr) {
                if (!exists->head) exists->head = addToAl(exists->head, curr->f);
                else addToAl(exists->head, curr->f);
                curr = curr->next;
            }

            currSibling = currSibling->next;
        }
        if (q.frontQ() == nullptr) {
            q.insertQ(nullptr);
            q.deleteQ();
        }
    }

    ahlHead = headAdj;
}

void Graph::printGraph(Node *head) const {
    Node* curr = head;

    while (curr) {
        cout << curr->f << " ";
        curr = curr->next;
    }
}

