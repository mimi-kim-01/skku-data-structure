#include <stdio.h>

#define MAX_NUM 10

//roots
typedef struct Node{
    char data;
    struct Node* left;
    struct Node* right;
}Node;

typedef struct Tree{
    Node* root;
    int num;
}Tree;

//functions
void create(Tree* roots, char root);
void insert_child(Tree* roots, Node* node, char child);
void insert_sibling(Tree* roots, Node* node, char sibling);
void delete_node(Tree* roots, char node);
void get_parent(Tree* roots, char node);
void get_child(Tree* roots, char node);
void get_sibling(Tree* roots, char node);
void get_ancestors(Tree* roots, char node);
void get_descendants(Tree* roots, char node);
int level_of_node(Tree* roots, char node);
int level_of_tree(Tree* roots);
int degree_of_node(Tree* roots, char node);
int degree_of_tree(Tree* roots);
int count_node(Tree* roots);
void print_tree(Tree* roots);
void join(Node* root, Tree* tree1, Tree* tree2);
void clear(Tree* roots);
void upper(Tree* roots, char node);
void lower(Tree* roots, char node);
void view(); //comma, space bar xx
Node* search(Node* root, char data);

//main
int main(){
    Tree* roots[MAX_NUM];
    int cnt = 0;
    int pos = -1;
    //view();
    while (1){
        print_tree(roots[pos]->root, roots[pos]->root);
        char request[21] = {0};
        printf("\n>>> ");
        gets(request);
        if (request[0] == 'Q'){
            printf("THIS PROGRAM WILL END SOON!\n");
            break;
        }
        for (int i = 0; i < strlen(request); i++){
            switch (request[i]){
            case '+':
                if (request[i+2] == NULL) {
                    create(roots, request[i+1]);
                    i++;
                }
                if (request[i+2] == '('){
                    if (cnt == 0) printf("PLEASE CREATE THE TREE FIRST.\n");
                    Node* find = search(roots[pos]->root, request[i+1]);
                    if (find == NULL){
                        printf("%c IS NOT IN THE TREE!\n", request[i+1]);
                        break;
                    }
                    insert_child(roots[pos], find, request[i+3]);
                    i++;
                    while (request[i] != ')'){
                        Node* ffind = search(roots[pos]->root, request[i-1]);
                        insert_sibling(roots[pos], ffind, request[i]);
                        i++;
                    }
                }
            }
        }
    }

    return 0;
}

//functions specific
void create(Tree* roots, char root){
    Node* new = (Node*)malloc(sizeof(Node));
    roots->root = new;
    new->data = root;
    new->left = NULL;
    new->right = NULL;
    roots->num++;
}

void insert_child(Tree* roots, Node* node, char child){
    Node* new = (Node*)malloc(sizeof(Node));
    if (node->left == NULL){
        node->left = new;
    }
    new->data = child;
    new->left = NULL;
    new->right = NULL;
    roots->num++;
}

void insert_sibling(Tree* roots, Node* node, char sibling){
    Node* new = (Node*)malloc(sizeof(Node));
    if (node->right == NULL){
        node->right = new;
    }
    new->data = sibling;
    new->left = NULL;
    new->right = NULL;
    roots->num++;
}

Node* search(Node* root, char data) { //수정하기
    if (root == NULL)return NULL;
    if (root->data == data) return root;
    Node* new = search(root->left, data);
    if (new != NULL) return new;
    new = search(root->right, data);
    if (new != NULL) return new;
    return NULL;
}

void print_tree(Node* parent, Node* child){ //수정하기
    Node* cur = child->left;
    if (parent == child) printf("%c", parent->data);
    if (parent->left == NULL) return;
    if (cur != NULL){
        printf("[%c", cur->data);
        print_tree(child, cur);
        if (child->right != NULL){
            printf(",%c", child->right->data);
            print_tree(child, child->right);
        }
        printf("]\n");
    }

}

 