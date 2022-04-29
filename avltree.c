#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//avl tree
typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
    int height;
}Node;

int num = 0;

//functions 
//다시 정리하기
Node* LLrotate(Node* pp);
Node* RRrotate(Node* pp);
Node* rebalance(Node* node);
int balance_factor(Node* node);
int height(Node* root);
Node* insert_node(Node* root, int value);
int get_max(int a, int b);
int get_value(char request[21]);
void print_avl(Node* one, Node* two);
Node* search_node(Node* node, int value);
Node* newnode(int value){

//main
int main() {
    Node* root = (Node*)malloc(sizeof(Node));
    //view();
    while (1) {
        char request[21] = { 0 };
        if (num == 0) {
            printf("THE AVL TREE IS EMPTY!\n");
        }
        else print_avl(root, root);
        printf("\n>>> ");
        gets(request);
        if (request[0] == 'Q') {
            printf("THIS PROGRAM WILL END SOON!\n");
            break;
        }
        for (int i = 0; i < strlen(request); i++) {
            switch (request[i]) {
            case '+':
                root = insert_node(root, get_value(request));
                break;
            }
        }
    }
    free(root);
    return 0;
}

//functions specific
Node* LLrotate(Node* pp) {
    Node* cc = pp->right;
    Node* temp = cc->left;
    cc->left = pp;
    pp->right = temp;
    cc->height = 1 + get_max(height(cc->left), height(cc->right));
    pp->height = 1 + get_max(height(pp->left), height(pp->right));
    return cc;
}

Node* RRrotate(Node* pp) {
    Node* cc = pp->left;
    Node* temp = cc->right;
    cc->right = pp;
    pp->left = temp;
    cc->height = 1 + get_max(height(cc->left), height(cc->right));
    pp->height = 1 + get_max(height(pp->left), height(pp->right));
    return cc;
}

Node* rebalance(Node* node) {
    if (balance_factor(node) > 1) {
        if (node->value > node->left->value) {
            node->left = LLrotate(node->left);
            return RRrotate(node);
        }
        else return RRrotate(node);
    }
    else if (balance_factor(node) < -1) {
        if (node->value < node->right->value) {
            node->right = RRrotate(node->right);
            return LLrotate(node);
        }
        else return LLrotate(node);
    }
    return node;
}

int balance_factor(Node* node) {
    if (node == NULL) return 0;
    int factor = height(node->left) - height(node->right);
    return factor;
}

int height(Node* root) {
    if (root == NULL) return 0;
    int l = height(root->left);
    int r = height(root->right);
    if (l > r) return l + 1;
    else return r + 1;
}

Node* newnode(int value){
    Node* new = (Node*)malloc(sizeof(Node));
    new->value = value;
    new->left = NULL;
    new->right = NULL;
    new->height = 1;
    num++;
    return new;
}

Node* insert_node(Node* root, int value) {
    if (root == NULL){
        return newnode(value);
    }
    if (value < root->value){
        root->left = insert_node(root->left, value);
    }
    else if (value > root->value){
        root->right = insert_node(root->right, value);
    }
    else return root;
    root->height = get_max(height(root->left), height(root->right)) + 1;
    int bal = balance_factor(root);
    if (bal == 2){
        if (value < root->left->value) return RRrotate(root);
        else{
            root->left = LLrotate(root->left);
            return RRrotate(root);
        }
    }
    else if (bal == -2){
        if (value > root->right->value) return LLrotate(root);
        else{
            root->right = RRrotate(root->right);
            return LLrotate(root);
        }
    }
    return root;
}

Node* search_node(Node* node, int value) {
    if (node == NULL) return NULL;
    if (node->value == value) return node;
    Node* crnt = search_node(node->left, value);
    if (crnt != NULL) return crnt;
    crnt = search_node(node->right, value);
    if (crnt != NULL) return crnt;
    return NULL;
}

int get_value(char request[21]) {
    int value = 0;
    char number[20] = { 0 };
    strncpy(number, request + 1, 20);
    value = atoi(number);
    return value;
}


void print_avl(Node* one, Node* two) {
    if (one == two) printf("%d", one->value);
    Node* crnt = two->left;
    if (two->left != NULL) {
        printf("(%d", crnt->value);
        print_avl(one, crnt);
        if (two->right != NULL) {
            printf(",%d", two->right->value);
            print_avl(one, two->right);
            printf(")");
        }
        else printf(",)");
    }
    else if (two->right != NULL) {
        printf("(,%d", two->right->value);
        print_avl(one, two->right);
        printf(")");
    }
}

int get_max(int a, int b) {
    if (a >= b) return a;
    else return b;
}
