#include <stdio.h>
#include <stdlib.h>

//avl tree
typedef struct Node{
    int value;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
    int degree;
    int level;
}Node;

typedef struct Tree{
    Node* root;
    int num;
}Tree;

//functions

//main
int main(){

    return 0;
}

//functions specific
Node* LLrotate(Node* c){
    Node* b = c->right;
    Node* a = b->left;
    b->left = c;
    c->right = a;
    return b;
}

Node* RRrotate(Node* c){
    Node* b = c->left;
    Node* a = b->right;
    b->right = c;
    c->left = a;
    return b;
}

Node* LRrotate(Node* c){
    c = RRrotate(c->left);
    return LLrotate(c);
}

Node* RLrotate(Node* c){
    c = LLrotate
}