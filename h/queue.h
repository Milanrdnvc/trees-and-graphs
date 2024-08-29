#ifndef _queue_h_
#define _queue_h_

template <typename T>
class Queue {
    struct Node {
        T* item;
        Node* next;

        Node(T* item, Node* next): item(item), next(next) {}
    };

    Node* head = nullptr;
    Node* tail = nullptr;

public:
    Queue() = default;
    Queue(const Queue&) = delete;
    const Queue& operator=(const Queue&) = delete;
    ~Queue();

    void insertQ(T* node);
    T* deleteQ();
    T* frontQ() const;
    bool emptyQ() const;
    void printQTreeNode() const;
};

template<typename T>
void Queue<T>::insertQ(T *node) {
    Node* newNode = new Node(node, nullptr);
    Node* curr = head;

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
        return;
    }

    while (curr->next != nullptr) {
        curr = curr->next;
    }

    curr->next = newNode;
    tail = newNode;
}

template<typename T>
T* Queue<T>::deleteQ() {
    if (head == nullptr) return nullptr;

    if (head == tail) {
        Node* old = head;
        head = tail = nullptr;
        T* item = old->item;
        delete old;
        return item;
    }

    Node* old = head;
    head = head->next;
    T* item = old->item;
    delete old;
    return item;
}

template<typename T>
T* Queue<T>::frontQ() const {
    if (head == nullptr) return nullptr;

    return head->item;
}

template<typename T>
bool Queue<T>::emptyQ() const {
    return head == nullptr;
}

template<typename T>
void Queue<T>::printQTreeNode() const {
    Node* curr = head;

    while (curr) {
        cout << curr->item->f << endl;
        curr = curr->next;
    }
}

template<typename T>
Queue<T>::~Queue() {
    Node* curr = head;

    while (curr) {
        Node* old = curr;
        curr = curr->next;
        delete old;
    }
}

#endif
