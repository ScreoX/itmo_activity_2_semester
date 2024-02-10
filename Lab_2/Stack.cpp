#include "Stack.h"

Stack::Stack(const Stack& other) {
    top = other.top;
    max_size = other.max_size;
    size = other.size;
}

Stack::Stack(int size) {
    size = 0;
    max_size = size;
    top = nullptr;
}

Stack::Stack() {
    size = 0;
    top = nullptr;
}


void Stack::push(int data) {

    Node* newNode = new Node(data);
    newNode->next = top;
    top = newNode;
    ++size;
}

void Stack::pop() {
    if (isEmpty()) {
        return;
    }
    --size;
    Node* temp = top;
    top = top->next;
    delete temp;
}

int Stack::top_stack() {
    if (isEmpty()) {
        return -1;
    }
    return top->data;
}

int Stack::size_stack() const {
    return size;
}

bool Stack::isEmpty() { return top == nullptr; }


Stack::Node::Node(int x) {
    next = nullptr;
    data = x;
}
