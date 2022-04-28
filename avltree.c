#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//avl tree
typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
    int degree;
    int level;
}Node;

int num = 0;

//functions
Node* LLrotate(Node* c);
Node* RRrotate(Node* c);
Node* rebalance(Node* node);
int balance_factor(Node* node);
int height(Node* root);
Node* insert_node(Node* root, int value);
int get_max(int a, int b);
int get_value(char request[21]);
void print_avl(Node* one, Node* two);

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
Node* LLrotate(Node* c) {
    Node* b = c->right;
    Node* a = b->left;
    b->left = c;
    c->right = a;
    c->level = 1 + get_max(height(c->left), height(c->left));
    b->level = 1 + get_max(height(b->left), height(b->right));
    return b;
}

Node* RRrotate(Node* c) {
    Node* b = c->left;
    Node* a = b->right;
    b->right = c;
    c->left = a;
    c->level = 1 + get_max(height(c->left), height(c->left));
    b->level = 1 + get_max(height(b->left), height(b->right));
    return b;
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

Node* insert_node(Node* root, int value) {
    Node* new = (Node*)malloc(sizeof(Node));
    new->value = value;
    new->left = NULL;
    new->right = NULL;
    if (num == 0) {
        new = root;
        root->value = value;
        num++;
        return root;
    }
    else if (root->value < value) {
        if (root->right == NULL) {
            root->right = new;
            num++;
        }
        else insert_node(root->right, value);
    }
    else if (root->value > value) {
        if (root->left == NULL) {
            root->left = new;
            num++;
        }
        else insert_node(root->left, value);
    }
    else {
        printf("[%d] ALREADY EXISTS!\n", value);
    }
    root->level = 1 + get_max(height(root->left), height(root->right));
    root = rebalance(root);
    return root;
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
