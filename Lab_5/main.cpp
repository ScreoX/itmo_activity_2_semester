#include <iostream>
#include "Swap.h"
#include "Stack.h"

enum Tasks {
    SWAP = 1,
    STACK
};

int main() {

    std::cout << "Tasks:\n"
                 "1. Swap two elements using a template function\n"
                 "2. Create a stack using a template class and make exceptions for it\n"
                 "Choose task:";
    int command;
    std::cin >> command;

    switch (command) {
        case (SWAP):
            std::cout << "Two int elements\n";
            int x, y;
            std::cin >> x >> y;

            std::cout << "Two char elements\n";
            char a,b;
            std::cin >> a >> b;

            std::cout << "First Values: " << x << " " << y << '\n';
            std::cout << "Second Values: " << a << " " << b << '\n';

            Swap(x,y);
            Swap(a, b);
            std::cout << "Swapped\n";

            std::cout << "First Values: " << x << " " << y << '\n';
            std::cout << "Second Values: " << a << " " << b << '\n';

            break;

        case (STACK):
            try {
                const int size = 5;
                Stack<size, int> stack;
                std::cout << "\nStack of " << stack.size_stack() <<  " elements has been created\n";

                std::cout << "\nTrying to pop element from empty stack\n";
                stack.pop(); // Произойдет исключение, так как stack не содержит в себе элементов (Если закомментировать эту строку, то возникнет другое исключение

                for (int i = 0; i < size; i++) {
                    stack.push(i);
                }
                std::cout << "The stack was filled with elements 0 to " << size << "\n";

                int element = 9;
                std::cout << "\nTrying to push " << element << " to stack\n";
                stack.push(element); // Произойдет исключение, так как stack содержит в себе максимальное количество элементов

                break;
            }
            catch (Exceptions& e){
                std::cout << "\nError name: " << e.What() << "\nError code: " << e.Code();
            }

        default:
            break;
    }



    return 0;
}
