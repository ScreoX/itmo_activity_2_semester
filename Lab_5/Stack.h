#ifndef LAB_5_OP_2SEM_STACK_H
#define LAB_5_OP_2SEM_STACK_H
#include "Exceptions.h"

template <int size, typename T>

class Stack {
private:

    int top;
    T* mas;

public:

    Stack();
    ~Stack();

    void push(T& val);
    T size_stack();
    T pop();
    T top_stack();
};


template<int size, typename T>
Stack<size, T>::Stack() {
    mas = new T[size];
    top = 0;
}

template<int size, typename T>
Stack<size, T>::~Stack() {
    delete[] mas;
}


template<int size, typename T>
void Stack<size, T>::push(T &val) {
    if (top == size) {
        throw Exceptions("Stack is full", 1);
    } else {
        mas[top++] = val;
    }
}

template<int size, typename T>
T Stack<size, T>::pop() {
    if (top <= 0) {
        throw Exceptions("Stack is empty", 2);
    } else {
        --top;
        return mas[top];
    }
}

template<int size, typename T>
T Stack<size, T>::size_stack() {
    return size;
}

template<int size, typename T>
T Stack<size, T>::top_stack() {
    if (top <= 0) {
        throw Exceptions("Stack is empty", 2);
    } else {
        return mas[top - 1];
    }
}



#endif
