#ifndef LAB_2_STACK_H
#define LAB_2_STACK_H


class Stack {
public:

    struct Node {
        int data;
        Node* next;

        Node(int data);

    };
    int size = 0;
    int max_size;
    Node* top;


    Stack();
    Stack(const Stack& other);
    explicit Stack(int size);

    void push(int data);
    void pop();
    int top_stack();
    int size_stack() const;
    bool isEmpty();

};




#endif
