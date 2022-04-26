#include <stdio.h>
#include <stdlib.h>

//avl tree
typedef struct Node{
    char data;
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