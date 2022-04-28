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

int num = 0;

//functions

//main
int main(){
    Node* root = (Node*)malloc(sizeof(Node));
    view();
    while (1){
        char request[21] = {0};
        if (num == 0){
            printf("THE AVL TREE IS EMPTY!\n");
        }
        else print_bst(root, root);
        printf("\n>>> ");
        gets(request);
        if (request[0] == 'Q'){
            printf("THIS PROGRAM WILL END SOON!\n");
            break;
        }
        for (int i = 0; i < strlen(request); i++){
            switch (request[i]){
            case '+':
                insert_node(root, get_value(request));
                rebalance(root);
                break;
            }
        }
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
    c = LLrotate(c);
    return c;
}

Node* RLrotate(Node* c){
    c = LLrotate(c->right);
    c = RRrotate(c);
    return c;
}

Node* rebalance(Node* node){
    if (balance_factor(node) >= 2){
        if (balance_factor(node->left) >= 1) node = LLrotate(node);
        else node = LRrotate(node);
    }
    else if (balance_factor(node) <= -2){
        if (balance_factor(node->right) <= -1) node = RRrotate(node);
        else node = RLrotate(node);
    }
    return node;
}

int balance_factor(Node* node){
    int factor = height(node->left) - height(node->right);
    return factor;
}

int height(Node* root){
    if (root == NULL) return 0;
    int l = height(root->left);
    int r = height(root->right);
    if (l > r) return l + 1;
	else return r + 1;
}

void insert_node(Node* root, int value){
    Node* new = (Node*)malloc(sizeof(Node));
    new->value = value;
    new->left = NULL;
    new->right = NULL;
    if (num == 0){
        new = root;
        root->value = value;
        num++;
        return;
    }
    if (root->value < value){
        if (root->right == NULL){
            root->right = new;
            num++;
        }
        else insert_node(root->right, value);
    }
    else if (root->value > value){
        if (root->left == NULL){
            root->left = new;
            num++;
        }
        else insert_node(root->left, value);
    }
    else{
        printf("[%d] ALREADY EXISTS!\n", value);
        return;
    }
}

int get_value(char request[21]){
    int value = 0;
    char number[20] = {0};
    strncpy(number,request+1,20);
    value = atoi(number);
    return value;
}