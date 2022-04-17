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

//functions //이진트리용 기능들도 쓰기? 아니 그리고 challenge과제 할거면 이진트리 자체 기능을 먼저 만들고, ??? 뭔소리임
void create(Tree* tree, char root);
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
void join(Node* root, Tree* tree1, Tree* tree2);
void clear(Tree* tree);
void upper(Tree* tree, char node);
void lower(Tree* tree, char node);
void view();

//main
int main(){
    Tree* tree = (Tree*)malloc(sizeof(Node));
    tree->num = 0;
    tree->root = NULL;
    int binary;
    printf("CHOOSE YOUR TREE TYPE(1: BINARY, 0: TREE)\n>>> ");
    scanf("%d", &binary);


    return 0;
}

//functions specific
void create(Tree* tree, char root){
    Node* new = (Node*)malloc(sizeof(Node));
    tree->root = new;
    new->data = root;
    new->left = NULL;
    new->right = NULL;
    tree->num++;
}

void insert_child(Tree* tree, Node* node, char child, int binary){
    
}
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
void join(Node* root, Tree* tree1, Tree* tree2);
void clear(Tree* tree);
void upper(Tree* tree, char node);
void lower(Tree* tree, char node);

void view(){
    printf("---------------------MENU---------------------\n");
    printf("CREATE                      | +(r)\n");
    printf("INSERT CHILD                | +p(c1, c2, ...))\n");
    printf("INSERT SIBLING              | +n(s1, s2, ...))\n");
    printf("DELETE NODE                 | -(n)\n");
    printf("GET PARENT                  | P(c)\n");
    printf("GET CHILD                   | C(p)\n");
    printf("GET SIBLING                 | S(n)\n");
    printf("GET ANCESTORS               | A(n)\n");
    printf("GET DESCENDANTS             | D(n)\n");
    printf("LEVEL OF NODE               | L(n)\n"); 
    printf("LEVEL OF TREE               | L\n");
    printf("DEGREE OF NODE              | G(n)\n");
    printf("DEGREE OF TREE              | G\n");
    printf("COUNT NODE                  | #\n");
    printf("PRINT TREE                  | L\n");
    printf("JOIN TREES                  | L(r, t1, t2)\n");
    printf("CLEAR TREE                  | C\n");
    printf("TO UPPER CASE               | U(n)");
    printf("TO LOWER CASE               | W(n)\n");
    printf("QUIT                        | Q\n");
    printf("===SOME WARNINGS TO KEEP IN MIND===\n");
    printf("* p: PARENT, c: CHILD, s: SIBLING\n");
    printf("* t: TREE, r: ROOT, n: NODE\n");
}