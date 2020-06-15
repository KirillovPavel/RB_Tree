#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <iostream>


enum Color{
    RED,
    BLACK
};

enum Side{
    RIGHT,
    LEFT
};

struct Node{
    struct Node* parent;
    struct Node* left;
    struct Node* right;

    Color color;
    int key;

    Node(int key, Color color = BLACK);
    void print();
    unsigned int height();
    Node* at(int key);
    void insert(int key);
    void balance();
    ~Node();
private:   /* LR means Left uncle and Right current node*/

    void LR();
    void LR_change();
    void LL();
    void RR();
    void RL();
    void RL_change();
};


#endif // RB_TREE_HPP
