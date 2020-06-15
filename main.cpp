#include <iostream>
#include <random>
#include "rb_tree.hpp"


int main()
{
    Node root(100);
    int k = 1000;
    srand(2);
    for(int i = 0; i < k; i++)
        root.insert(rand() % 200);
    root.at(199)->print();
    std::cout << "H = " << root.height() << std::endl;
    return 0;
}
