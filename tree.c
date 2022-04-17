#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//tree
typedef struct Node{
    char data;
    struct Node* left;
    struct Node* right;
    int degree;
    int level;
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
Node* search(Tree* tree, Node* node, char data);
void print_tree(Tree* tree, Node* one, Node* two, int binary);
void view();

//main
int main(){
    Tree* tree = (Tree*)malloc(sizeof(Node));
    tree->num = 0;
    tree->root = NULL;
    int binary;
    printf("CHOOSE YOUR TREE TYPE(1: BINARY, 0: TREE)\n>>> ");
    scanf(" %d", &binary);
    while (1){
        print_tree(tree, tree->root, tree->root, binary);
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
                if (strlen(request) == 2){
                    create(tree, request[i+1]);
                    i++;
                }
                else {
                    Node* node = search(tree, tree->root, request[i+1]);
                    if (node == NULL) {
                        printf("%c IS NOT IN TREE", request[i+1]);
                    }
                    else{
                        i += 3;
                        while (request[i] != ')'){
                            insert_child(tree, node, request[i], binary);
                            i++;
                        }
                    }
                }
            }
        }
    }


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
    Node* new = (Node*)malloc(sizeof(Node));
    if (binary){
        if (node->left != NULL && node->right != NULL){
            printf("CANNOT INSERT %c\n", child);
        }
        if (node->left == NULL){
            node->left = new;
        }
        else if (node->right == NULL){
            node->right = new;
        }
    }
    else{
        if (node->left == NULL) node->left = new;
        else{
            Node* crnt = node->left;
            while (crnt->right != NULL){
                crnt = crnt->right;
            }
            crnt->right = new;
        }
    }
    new->data = child;
    new->left = NULL;
    new->right = NULL;
    new->level = node->level + 1;
    new->degree = 0;
    tree->num++;
}

Node* search(Tree* tree, Node* node, char data){
    if (node == NULL) return NULL;
    if (node->data == data) return node;
    Node* crnt = search(tree, node->left, data);
    if (crnt != NULL) return crnt;
    crnt = search(tree, node->right, data);
    if (crnt != NULL) return crnt;
    return NULL;
}

void print_tree(Tree* tree, Node* one, Node* two, int binary){
    if (tree->num == 0) {
        printf("EMPTY!\n");
        return;
    }
    if (!binary){
        Node* crnt = two->left;
        if (one == two){
            printf("%c", one->data);
        }
        if (one->left == NULL) return;
        printf("(");
        while(crnt != NULL){
            printf("%c", crnt->data);
            if (crnt->left != NULL) print_tree(tree, one, crnt, binary);
            if (crnt->right != NULL) printf(",");
            crnt = crnt->right;
        }
        printf(")");
    }
    else{
        Node* crnt = one; // tmp 노드에 현재 주목하고 있는 노드 대입
        if (crnt == tree->root){
            printf("%c", crnt->data);
        }
        else {
            printf("(%c", crnt->data);
        }
        if (crnt->left != NULL) print_tree(tree, crnt->left, two, binary);
        if (crnt->right != NULL) {
            crnt = crnt->right;
            printf(",%c", crnt->data);
            if (crnt->left != NULL) print_tree(tree, crnt->left, two, binary);
            printf(")");
        }
    }
    printf("\n");
}

void view(){
    printf("---------------------MENU---------------------\n");
    printf("CREATE                      | +(r)\n");
    printf("INSERT CHILD                | +p(c1, c2, ...))\n");
    printf("INSERT SIBLING              | =+n(s1, s2, ...))\n");
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