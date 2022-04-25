#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//binary search tree
typedef struct node{
    int value;
    struct node* left;
    struct node* right;
}Node;

int num = 0;

//functions
void insert_node(Node* root, int value);
void inorder_traversal(Node* root);
void right_root_left_traversal(Node* root);
int get_min(Node* root);
int get_max(Node* root);
int height(Node* bst);
int degree_of_node(Node* root, int value);
Node* find_node(Node* node, int value);
Node* search_node(Node* node, int value);
void get_right_child(Node* root, int value);
void get_left_child(Node* root, int value);
void count_node(Node* root);
Node* delete_node(Node* root, int value);
void print_bst(Node* one, Node* two);
int get_value(char request[21]);
void clear(Node* root);
void view();

//main
int main(){
    Node* root = (Node*)malloc(sizeof(Node));
    view();
    while (1){
        char request[21] = {0};
        if (num == 0){
            printf("THE BST IS EMPTY!\n");
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
                break;
            case '-':
                if (search_node(root, get_value(request)) != NULL) num--;
                root = delete_node(root, get_value(request));
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
                printf("MIN: %d\n", get_min(root));
                break;
            case 'X':
                printf("MAX: %d\n", get_max(root));
                break;
            case 'F':
                if (search_node(root, get_value(request)) != NULL) printf("ROOT");
                find_node(root, get_value(request));
                printf("\n");
                break;
            case 'H':
                printf("HEIGHT: %d\n", height(root) - 1);
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

int height(Node* root){
    if (root == NULL) return 0;
    int l = height(root->left);
    int r = height(root->right);
    if (l > r) return l + 1;
	else return r + 1;
}

int degree_of_node(Node* root, int value){
    Node* crnt = search_node(root, value);
    if (crnt == NULL) return -1;
    if (crnt->left == NULL && crnt->right == NULL) return 0;
    else if (crnt->left == NULL || crnt->right == NULL) return 1;
    else return 2;
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

Node* search_node(Node* node, int value){
    if (node == NULL) return NULL;
    if (node->value == value) return node;
    Node* crnt = search_node(node->left, value);
    if (crnt != NULL) return crnt;
    crnt = search_node(node->right, value);
    if (crnt != NULL) return crnt;
    return NULL;
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

void count_node(Node* root){
    printf("NODE COUNT: %d\n", num);
}

Node* delete_node(Node* root, int value){
    Node* del = NULL;
    if (root == NULL){
        printf("THE BST IS EMPTY!\n");
        return NULL;
    }
    if (root->value > value){
        root->left = delete_node(root->left, value);
    }
    else if (root->value < value){
        root->right = delete_node(root->right, value);
    }
    else{
        if (degree_of_node(root, root->value) == 2){
            del = search_node(root, get_max(root->left));
            root->value = del->value;
            root->left = delete_node(root->left, del->value);
        }
        else{
            if (root->left == NULL) del = root->right;
            else del = root->left;
            free(root);
            return del;
        }
    }
    return root;
}

void print_bst(Node* one, Node* two){
    if (one == two) printf("%d", one->value);
    Node* crnt = two->left;
    if (two->left != NULL) {
        printf("(%d", crnt->value);
        print_bst(one, crnt);
        if (two->right != NULL){
            printf(",%d", two->right->value);
            print_bst(one, two->right);
            printf(")");
        }
        else printf(",)");
    }
    else if (two->right != NULL){
        printf("(,%d", two->right->value);
        print_bst(one, two->right);
        printf(")");
    }
}

void clear(Node* root){
    root->value = '\0';
    root->left = NULL;
    root->right = NULL;
    num = 0;
}

int get_value(char request[21]){
    int value = 0;
    char number[20] = {0};
    strncpy(number,request+1,20);
    value = atoi(number);
    return value;
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
    printf("HEIGHT                      | H\n"); 
    printf("GET RIGHT CHILD             | G(n)\n");
    printf("GET LEFT CHILD              | L(n)\n");
    printf("COUNT NODE                  | #\n");
    printf("PRINT BST                   | P\n");
    printf("CLEAR BST                   | C\n");
    printf("QUIT                        | Q\n");
    printf("VIEW MENU                   | V\n");
    printf("===SOME WARNINGS TO KEEP IN MIND===\n");    
    printf("* 1. Do not use brackets.\n");
    printf("* 2. No spacing between commands.\n\n");
}