#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//binary search tree
typedef struct Node{
    int value;
    struct Node* left;
    struct Node* right;
}Node;

int num = 0;

//functions
void insert_node(Node* root, int value);
void inorder_traversal(Node* root);
void right_root_left_traversal(Node* root);
int get_min(Node* root);
int get_max(Node* root);
int height(Node* bst);
Node* find_node(Node* node, int value);
Node* get_right_child(Node* root, int value);
Node* get_left_child(Node* root, int value);
void count_node(Node* root);
void delete_node(Node* root, int value);
void print_bst(Node* root);
void clear(Node* root);

//main
int main(){
    Node* root = (Node*)malloc(sizeof(Node));


    free(root);
    return 0;
}

//functions specific
void insert_node(Node* root, int value){
    if (num == 0) {
        printf("THE BST IS EMPTY!\n");
        return;
    }
    Node* new = (Node*)malloc(sizeof(Node));
    new->value = value;
    new->left = NULL;
    new->right = NULL;
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

void inorder_traversal(Node* root);
void right_root_left_traversal(Node* root);
int get_min(Node* root);
int get_max(Node* root);
int height(Node* bst);

Node* find_node(Node* node, int value){
    if (node == NULL) return NULL;
    if (node->value == value) return node;
    Node* crnt = find(node->left, value);
    if (crnt != NULL) return crnt;
    crnt = find(node->right, value);
    if (crnt != NULL) return crnt;
    return NULL;
}

Node* get_right_child(Node* root, int value){
    if (root == NULL) return NULL;
    if (root->right == NULL) return NULL;
    return root->right;
}

Node* get_left_child(Node* root, int value){
    if (root == NULL) return NULL;
    if (root->left == NULL) return NULL;
    return root->left;
}

void count_node(Node* root){
    printf("NODE COUNT: %d\n", num);
}

void delete_node(Node* root, int value);
void print_bst(Node* root);
void clear(Node* root);