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
Node* LLrotate(Node* pp);
Node* RRrotate(Node* pp);
Node* rebalance(Node* node);
int balance_factor(Node* node);
void inorder_traversal(Node* root);
void right_root_left_traversal(Node* root);
int height(Node* root);
Node* insert_node(Node* root, int value);
Node* delete_node(Node* root, int value);
int get_max(int a, int b);
int get_min_value(Node* root);
int get_max_value(Node* root);
void get_right_child(Node* root, int value);
void get_left_child(Node* root, int value);
int get_value(char request[21]);
Node* find_node(Node* node, int value);
void print_avl(Node* one, Node* two);
Node* search_node(Node* node, int value);
Node* newnode(int value);
void count_node(Node* root);
void clear(Node* root);
void view();

//main
int main() {
    Node* root = (Node*)malloc(sizeof(Node));
    view();
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
                if (search_node(root, get_value(request)) != NULL){
                    printf("[%d] ALREADY EXISTS!\n", get_value(request));
                    break;
                }
                root = insert_node(root, get_value(request));
                break;
            case '-':                
                if (search_node(root, get_value(request)) != NULL) num--;
                root = delete_node(root, get_value(request));
                break;
            case 'B':
                if (search_node(root, get_value(request)) == NULL){
                    printf("[%d] DOES NOT EXIST!\n", get_value(request));
                    break;
                }
                else {
                    printf("BALANCE FACTOR OF [%d]: ", get_value(request));
                    printf("%d\n",balance_factor(search_node(root, get_value(request))));
                }
                break;
            case 'I':
                inorder_traversal(root);
                printf("\n");
                break;
            case 'R':
                right_root_left_traversal(root);
                printf("\n");
                break;       
            case 'N':
                printf("MIN: %d\n", get_min_value(root));
                break;
            case 'X':
                printf("MAX: %d\n", get_max_value(root));
                break;
            case 'F':
                if (search_node(root, get_value(request)) != NULL) printf("ROOT");
                find_node(root, get_value(request));
                printf("\n");
                break;  
            case 'T':
                printf("HEIGHT: %d\n", height(root) - 1);
                break;
                case 'H':
                if (search_node(root, get_value(request)) == NULL){
                    printf("[%d] DOES NOT EXIST!\n", get_value(request));
                    break;
                }
                printf("HEIGHT OF [%d]: %d\n", get_value(request), height(search_node(root, get_value(request))) - 1);
                break;
            case 'G':
                get_right_child(root, get_value(request));
                break;
            case 'L':
                get_left_child(root, get_value(request));
                break;                
            case '#':
                count_node(root);
                break;
            case 'P':
                break;
            case 'C':
                clear(root);
                break;
            case 'V':
                view();
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

void inorder_traversal(Node* root){
    if (root->left != NULL) inorder_traversal(root->left);
    printf("%d ", root->value);
    if (root->right != NULL) inorder_traversal(root->right);
}

void right_root_left_traversal(Node* root){
    if (root->right != NULL) right_root_left_traversal(root->right);
    printf("%d ", root->value);
    if (root->left != NULL) right_root_left_traversal(root->left);
}

Node* insert_node(Node* root, int value) {
    Node* new = (Node*)malloc(sizeof(Node));
    new->value = value;
    new->left = NULL;
    new->right = NULL;
    if (num == 0){
        new = root;
        root->value = value;
        num++;
        return root;
    }
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

Node* delete_node(Node* root, int value){
    if (root == NULL) return NULL;
    if (value < root->value){
        root->left = delete_node(root->left, value);
    }
    else if (value > root->value){
        root->right = delete_node(root->right, value);
    }
    else{
        if (root->left == NULL || root->right == NULL){
            Node* crnt = (Node*)malloc(sizeof(Node));
            if (root->left != NULL) crnt = root->left;
            else crnt = root->right;
            if (crnt != NULL) *root = *crnt;
            else {
                crnt = root;
                root = NULL;
            }
            free(crnt);
        }
        else{
            Node* crnt = search_node(root, get_max_value(root->left));
            root->value = crnt->value;
            root->left = delete_node(root->left, crnt->value);
        }
    }
    if (root == NULL) return root;
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

int get_min_value(Node* root){
    Node* crnt = root;
    int min = crnt->value;
    while (crnt->left != NULL){
        crnt = crnt->left;
        min = crnt->value;
    }
    return min;
}

int get_max_value(Node* root){
    Node* crnt = root;
    int max = crnt->value;
    while (crnt->right != NULL){
        crnt = crnt->right;
        max = crnt->value;
    }    
    return max;
}

void get_right_child(Node* root, int value){
    if (root == NULL) {
        printf("THE BST DOES NOT EXIST!\n");
        return;
        }
    if (root->right == NULL) {
        printf("[%d] DOES NOT HAVE RIGHT CHILD!\n", value);
        return;
        }
    printf("RIGHT CHILD OF [%d]: %d\n", value, root->right->value);
}

void get_left_child(Node* root, int value){
    if (root == NULL) {
        printf("THE BST DOES NOT EXIST!\n");
        return;
        }
    if (root->left == NULL) {
        printf("[%d] DOES NOT HAVE LEFT CHILD!\n", value);
        return;
        }
    printf("LEFT CHILD OF [%d]: %d\n", value, root->left->value);
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

Node* find_node(Node* node, int value){
    if (node == NULL) return NULL;
    if (search_node(node, value) == NULL) {
        printf("NOT FOUND!");
        return NULL;
    }
    if (node->value == value) {
        return node;
        }
    if (node->value > value){
        printf("->LEFT");
        return find_node(node->left, value);
    }
    if (node->value < value){
        printf("->RIGHT");
        return find_node(node->right, value);
    }
    return NULL;
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

void count_node(Node* root){
    printf("NODE COUNT: %d\n", num);
}

void clear(Node* root){
    root->value = '\0';
    root->left = NULL;
    root->right = NULL;
    num = 0;
}

void view(){
    printf("---------------------MENU---------------------\n");
    printf("CREATE                      | +(n)\n");
    printf("INSERT NODE                 | +(n)\n");
    printf("DELETE NODE                 | -(n)\n");
    printf("INORDER TRAVERSE            | I\n");
    printf("RIGHT ROOT LEFT TRAVERSE    | R\n");
    printf("GET MIN                     | N\n");
    printf("GET MAX                     | X\n");
    printf("FIND NODE                   | F(n)\n");
    printf("HEIGHT OF TREE              | T\n"); 
    printf("HEIGHT OF NODE              | H(n)\n"); 
    printf("GET RIGHT CHILD             | G(n)\n");
    printf("GET LEFT CHILD              | L(n)\n");
    printf("BALANCING FACTOR            | B(n)\n");
    printf("COUNT NODE                  | #\n");
    printf("PRINT AVL TREE              | P\n");
    printf("CLEAR AVL TREE              | C\n");
    printf("QUIT                        | Q\n");
    printf("VIEW MENU                   | V\n");
    printf("===SOME WARNINGS TO KEEP IN MIND===\n");    
    printf("* 1. Do not use brackets.\n");
    printf("* 2. No spacing between commands.\n\n");
}