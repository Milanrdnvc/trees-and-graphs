#ifndef _graph_h
#define _graph_h_

#include <iostream>
#include "tree.h"

using namespace std;

class Graph {
    struct Node {
        string f;
        Node* next;
        Node* head;

        Node (string f, Node* next, Node* head): f(f), next(next), head(head) {}
    };

public:
    Graph() = default;
    Graph(const Graph &) = delete;
    Graph &operator=(const Graph &) = delete;

    void convertTreeToGraph(Tree::Node* root);
    Node* existsInAhl(Node* head, string f);
    Node* addToAhl(Node* head, string f);
    Node* addToAl(Node* head, string f);
    bool existsInAl(Node* head, string f);
    void printGraph() const;

    ~Graph();

private:
    Node* ahlHead = nullptr;
};

#endif
