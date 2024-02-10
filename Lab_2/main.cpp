#include <iostream>
#include "Stack.h"

int main() {
    int size;
    Stack x(size);
    x.push(1);
    x.push(3);
    x.push(8);


    std::cout << "\nTemp top stack: " << x.top_stack() << "\n"
                                                   "Temp size stack: " << x.size_stack() << '\n';

    std::cout << "\nDelete top stack";
    x.pop();

    std::cout << "\nTemp top stack: " << x.top_stack() << "\n"
                                                        "Temp size stack: " << x.size_stack() << '\n';

    std::cout << "\nDelete top stack\n";
    x.pop();

    std::cout << "Temp top stack: " << x.top_stack() << "\n"
                                                        "Temp size stack: " << x.size_stack() << '\n';

    std::cout << "\nDelete top stack\n";
    x.pop();

    std::cout << "Temp top stack: " << x.top_stack() << "\n"
                                                        "Temp size stack: " << x.size_stack() << '\n';

    bool check = x.isEmpty();
    if (check) {
        std::cout << "Stack is empty\n";
    } else {
        std::cout << "Stack isn't empty\n";
    }


    return 0;
}
