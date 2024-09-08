#include "../h/graph.h"
#include "../h/queue.h"
#include "../h/stack.h"

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

    return nullptr;
}


void Graph::convertTreeToGraph(Tree::Node *root) {
    if (!root || ahlHead) return;

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

void Graph::printGraph() const {
    Node* curr = ahlHead;

    while (curr) {
        cout << curr->f << " | ";

        Node* currAl = curr->head;

        while (currAl) {
            cout << currAl->f;
            if (currAl->next) cout << " -> ";
            currAl = currAl->next;
        }

        cout << "\n";
        curr = curr->next;
    }
}

Graph::Node *Graph::getAhlHead() const {
    return ahlHead;
}

int Graph::getAhlLen() const {
    Node* curr = ahlHead;
    int cnt = 0;

    while (curr) {
        cnt++;
        curr = curr->next;
    }

    return cnt;
}


bool Graph::hasCycle() const {
     struct NodeFlagPair {
         Node* node;
         int idx;
         bool visited;

         NodeFlagPair(Node* node = nullptr, int idx = -1, bool visited = false) : node(node), idx(idx), visited(visited) {}
     };

     int ahlLen = getAhlLen();

     NodeFlagPair* visited = new NodeFlagPair[ahlLen];
     NodeFlagPair* pathVisited = new NodeFlagPair[ahlLen];

     Node* curr = ahlHead;
     for (int i = 0; i < getAhlLen() && curr; i++) {
         pathVisited[i].node = visited[i].node = curr;
         pathVisited[i].idx = visited[i].idx = i;
         curr = curr->next;
     }

     Stack<NodeFlagPair> s;

     s.push(&visited[0]);

     while (!s.emptyS()) {
         NodeFlagPair* v = s.pop();

         if (pathVisited[v->idx].visited == true) {
             delete[] visited;
             delete[] pathVisited;
             return true;
         }

         if (!visited[v->idx].visited) {
             visited[v->idx].visited = true;
             pathVisited[v->idx].visited = true;

             Node* curr = visited[v->idx].node->head;
             while (curr) {
                 for (int i = 0; i < getAhlLen(); i++) {
                     if (curr->f == visited[i].node->f) {
                         if (!visited[i].visited) {
                             s.push(&visited[i]);
                         } else if (pathVisited[i].visited) {
                             delete[] visited;
                             delete[] pathVisited;
                             return true;
                         }
                         break;
                     }
                 }
                 curr = curr->next;
             }
         }

         pathVisited[v->idx].visited = false;
     }

     delete[] visited;
     delete[] pathVisited;
     return false;
}

Graph::~Graph() {
    Node* curr = ahlHead;

    while (curr) {
        Node* currAl = curr->head;

        while (currAl) {
            Node* old = currAl;
            currAl = currAl->next;
            delete old;
        }

        Node* old = curr;
        curr = curr->next;
        delete old;
    }

    ahlHead = nullptr;
}


