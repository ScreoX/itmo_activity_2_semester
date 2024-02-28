#include <iostream>
#include "CircularBuffer.h"

int main() {

    CircularBuffer<int> my_vector(4);

    my_vector.push_back(1);
    my_vector.push_back(9);
    my_vector.push_back(3);

    std::cout << "Add numbers to circular buffer:\n";
    for (int j : my_vector) {
        std::cout << j << " ";
    }
    std::cout << "---- Temp size: " << my_vector.size();

    my_vector.pop_back();
    my_vector.push_back(4);

    std::cout << "\nDeleted back element and add new element (4):\n";
    for (int j : my_vector) {
        std::cout << j << " ";
    }
    std::cout << "---- Temp size: " << my_vector.size();

    my_vector.pop_front();
    my_vector.push_front(8);

    std::cout << "\nDeleted front element and add new element (8):\n";
    for (int j : my_vector) {
        std::cout << j << " ";
    }
    std::cout << "---- Temp size: " << my_vector.size();

    std::cout << "\nCapacity:\n" << my_vector.capacity() << '\n';

    my_vector.change_capacity(10);
    std::cout << "Changed capacity. New capacity:\n" << my_vector.capacity();
    std::cout << '\n';

    std::cout << "Add Iterator\n";
    auto i = CircularBuffer<int>::MyIterator(my_vector.begin());

    std::cout << "Push 2 by iterator\n";
    my_vector.push_by_iterator(i, 2);
    for (int j : my_vector) {
        std::cout << j << " ";
    }
    std::cout << "---- Temp size: " << my_vector.size();

    std::cout << "\nDelete 9 by iterator\n";
    my_vector.pop_by_iterator(my_vector.begin() + 1);
    for (int j : my_vector) {
        std::cout << j << " ";
    }
    std::cout << "---- Temp size: " << my_vector.size();
    std::cout << '\n';

    std::cout << "Circular buffer front element: " << my_vector.get_front() << "\n";
    std::cout << "Circular buffer back element: " << my_vector.get_back();

    return 0;
}
