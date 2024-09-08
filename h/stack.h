#ifndef _stack_h_
#define _stack_h_

template <typename T>
class Stack {
    struct Node {
        T* item;
        Node* next;
        Node* prev;

        Node(T* item, Node* next, Node* prev): item(item), next(next), prev(prev) {}
    };

    Node* head = nullptr;
    Node* tail = nullptr;

public:
    Stack() = default;
    Stack(const Stack&) = delete;
    const Stack& operator=(const Stack&) = delete;
    ~Stack();

    void push(T* node);
    T* pop();
    T* peek() const;
    bool emptyS() const;
};

template<typename T>
void Stack<T>::push(T *node) {
    Node* newNode = new Node(node, nullptr, nullptr);
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
    newNode->prev = curr;
    tail = newNode;
}

template<typename T>
T* Stack<T>::pop() {
    if (head == nullptr) return nullptr;

    if (head == tail) {
        Node* old = head;
        head = tail = nullptr;
        T* item = old->item;
        delete old;
        return item;
    }

    Node* old = tail;
    tail = tail->prev;
    T* item = old->item;
    delete old;
    return item;
}

template<typename T>
T* Stack<T>::peek() const {
    return tail ? tail->item : nullptr;
}

template<typename T>
bool Stack<T>::emptyS() const {
    return head == nullptr;
}

template<typename T>
Stack<T>::~Stack() {
    Node* curr = head;

    while (curr) {
        Node* old = curr;
        curr = curr->next;
        delete old;
    }
}

#endif
