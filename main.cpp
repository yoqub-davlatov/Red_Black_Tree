#include <iostream>
#include "red_black_tree.h"

int main()
{
    int a[] = {1, 4, 8, 4, 2, 0, 6, 7, 3};
    RedBlackTree<int> rbt;
    for (int i : a)
    {
        rbt.insert(i);
    }
    rbt.print();
    std::cout << "Success!" << std::endl;
}