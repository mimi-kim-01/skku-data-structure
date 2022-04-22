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
Node* search(Node* node, int value);
Node* get_right_child(Node* root, int value);
Node* get_left_child(Node* root, int value);
void count_node(Node* root);
void delete_node(Node* root, int value);
void print_bst(Node* root);
void clear(Node* root);
void view();

//main
int main(){
    Node* root = (Node*)malloc(sizeof(Node));
    //view();
    while (1){
        char request[21] = {0};
        if (num == 0){
            printf("THE BST IS EMPTY!\n");
        }
        //else print_bst(root);
        printf("\n>>> ");
        gets(request);
        if (request[0] == 'Q'){
            printf("THIS PROGRAM WILL END SOON!\n");
            break;
        }
        for (int i = 0; i < strlen(request); i++){
            switch (request[i]){
            case '+':
                insert_node(root, request[i+1]);
                break;
            }
        }
    }

    free(root);
    return 0;
}

//functions specific
void insert_node(Node* root, int value){
    Node* new = (Node*)malloc(sizeof(Node));
    new->value = value;
    new->left = NULL;
    new->right = NULL;
    if (num == 0){
        new = root;
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

void inorder_traversal(Node* root){
    if (root->left != NULL) inorder_traversal(root->left);
    printf("%c ", root->value);
    if (root->right != NULL) inorder_traversal(root->right);
}

void right_root_left_traversal(Node* root){
    if (root->right != NULL) right_root_left_traversal(root->right);
    printf("%c ", root->value);
    if (root->left != NULL) right_root_left_traversal(root->left);
}

int get_min(Node* root){
    Node* crnt = root;
    int min = crnt->value;
    while (crnt->left != NULL){
        crnt = crnt->left;
        min = crnt->value;
    }
    return min;
}

int get_max(Node* root){
    Node* crnt = root;
    int max = crnt->value;
    while (crnt->right != NULL){
        crnt = crnt->right;
        max = crnt->value;
    }    
    return max;
}

int height(Node* bst);

Node* find_node(Node* node, int value){
    if (node == NULL) return NULL;
    printf("ROOT->");
    if (node->value == value) return node;
    if (node->value > value){
        printf("LEFT->");
        return find_node(node->left, value);
    }
    if (node->value < value){
        printf("RIGHT->");
        return find_node(node->right, value);
    }
    return NULL;
}

Node* search_node(Node* node, int value){
    if (node == NULL) return NULL;
    if (node->value == value) return node;
    Node* crnt = search_node(node->left, value);
    if (crnt != NULL) return crnt;
    crnt = search_node(node->right, value);
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
void view();