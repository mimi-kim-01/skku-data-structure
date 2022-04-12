#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//tree
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
void insert_child(Tree* tree, Node* node, char child, int binary);
void insert_sibling(Tree* tree, Node* node, char sibling, int binary);
void delete_node(Tree* tree, char node);
void get_parent(Tree* tree, char node);
void get_child(Tree* tree, char node);
void get_sibling(Tree* tree, char node);
void get_ancestors(Tree* tree, char node);
void get_descendants(Tree* tree, char node);
int level_of_node(Tree* tree, char node);
int level_of_tree(Tree* tree);
int degree_of_node(Tree* tree, char node);
int degree_of_tree(Tree* tree);
int count_node(Tree* tree);
void print_tree(Tree* tree);
void clear(Tree* tree);
void upper(Tree* tree, char node);
void lower(Tree* tree, char node);
void view();

//main
int main(){
    Tree* tree = (Tree*)malloc(sizeof(Node));
    tree->num = 0;
    tree->root = NULL;

    return 0;
}

//functions specific
