#ifndef LAB_5_OP_2SEM_SWAP_H
#define LAB_5_OP_2SEM_SWAP_H

template <typename T>
void Swap(T& x, T& y) {
    T temp = x;
    x = y;
    y = temp;
}



#endif
