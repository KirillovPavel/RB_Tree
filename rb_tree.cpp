#include "rb_tree.hpp"


Node::Node(int key, Color color):
    parent(nullptr),
    left(nullptr),
    right(nullptr),
    color(color),
    key(key)
{}

void Node::print(){
    if(left != nullptr)
        left->print();
    std::cout << key << std::endl;
    if(right != nullptr)
        right->print();
}

unsigned int Node::height(){
    if(left == nullptr){
        if(right == nullptr)
            return 0;
        else
            return right->height() + 1;
    } else{
        if(right == nullptr)
            return left->height() + 1;
        else
            return std::max(left->height(), right->height()) + 1;
    }
}

Node* Node::at(int key){
    if(key == this->key)
        return this;
    if(key > this->key){
        if(this->right != nullptr)
            return this->right->at(key);
        return nullptr;
    } else {
        if(this->left != nullptr)
            return this->left->at(key);
        return nullptr;
    }
}

void Node::insert(int key){
    if(key > this->key){
        if(right == nullptr){
            right = new Node(key, RED);
            right->parent = this;
            right->balance();
        } else {
            right->insert(key);
        }
    } else {
        if(left == nullptr){
            left = new Node(key, RED);
            left->parent = this;
            left->balance();
        } else {
            left->insert(key);
        }
    }
}

void Node::balance(){
    if(this->parent == nullptr){
        this->color = BLACK;
        return;
    }
    if(this->parent->parent == nullptr && this->parent->color == RED){
        std::cout << "Error: root can't be red" << std::endl;
        return;
    }
    if(this->parent->color == BLACK)
        return;

    Side child = this == this->parent->right ? RIGHT : LEFT;
    Side uncle = this->parent->parent->right == this->parent ? LEFT : RIGHT;
    if(uncle == LEFT){
        if(child == RIGHT){
            LR();
        } else {
            LL();
        }
    } else {
        if(child == RIGHT){
            RR();
        } else {
            RL();
        }
    }
}

Node::~Node(){
    delete left;
    delete right;
}

void Node::LR(){
    if(this->parent->parent->left == nullptr){
        LR_change();
        return;
    }
    Color uncle_color = this->parent->parent->left->color;
    if(uncle_color == BLACK){
        LR_change();
    } else {
        this->parent->color = BLACK;
        this->parent->parent->color = RED;
        this->parent->parent->left->color = BLACK;
        this->parent->parent->balance();
    }
}

void Node::LR_change(){
    this->parent->color = BLACK;
    this->parent->parent->color = RED;
    Node* brother = this->parent->left;
    Node* grand = this->parent->parent;
    if(brother != nullptr)
        brother->parent = this->parent->parent;
    this->parent->left = grand;
    this->parent->parent = grand->parent;
    if(grand->parent != nullptr){
        if(grand->parent->left == grand){
            grand->parent->left = this->parent;
        } else {
            grand->parent->right = this->parent;
        }
    }
    grand->right = brother;
    grand->parent = this->parent;
}

void Node::LL(){
    Node* parent = this->parent;
    Node* grand = this->parent->parent;
    if(this->right != nullptr)
        this->right->parent = parent;
    parent->left = this->right;
    this->parent = grand;
    grand->right = this;
    this->right = parent;
    parent->parent = this;
    parent->LR();
}

void Node::RR(){
    Node* parent = this->parent;
    Node* grand = this->parent->parent;
    if(this->left != nullptr)
        this->left->parent = parent;
    parent->right = this->left;
    this->parent = grand;
    grand->left = this;
    this->left = parent;
    parent->parent = this;
    parent->RL();
}

void Node::RL(){
    if(this->parent->parent->right == nullptr){
        RL_change();
        return;
    }

    Color uncle_color = this->parent->parent->right->color;
    if(uncle_color == BLACK){
        RL_change();
    } else {
        this->parent->color = BLACK;
        this->parent->parent->color = RED;
        this->parent->parent->right->color = BLACK;
        this->parent->parent->balance();
    }
}

void Node::RL_change(){
    this->parent->color = BLACK;
    this->parent->parent->color = RED;
    Node* grand = this->parent->parent;
    if(this->parent->right != nullptr)
        this->parent->right->parent = grand;
    grand->left = this->parent->right;
    this->parent->parent = grand->parent;
    if(grand->parent != nullptr){
        if(grand->parent->left == grand){
            grand->parent->left = this->parent;
        } else {
            grand->parent->right = this->parent;
        }
    }
    this->parent->right = grand;
    grand->parent = this->parent;
}
