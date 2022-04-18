#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//tree
typedef struct Node{
    char data;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
    int degree;
    int level;
}Node;

typedef struct Tree{
    Node* root;
    int num;
}Tree;

//functions 
void create(Tree* tree, char root);
void insert_child(Tree* tree, Node* node, char child, int binary);
void insert_sibling(Tree* tree, Node* node, char sibling, int binary);
void get_child(Tree* tree, char parent, int binary);
void get_parent(Tree* tree, char child);
void get_sibling(Tree* tree, char sibling, int binary);
void get_ancestors(Tree* tree, char node);
void get_descendants(Tree* tree, char node, int binary);
void level_of_node(Tree* tree, char node);
void level_of_tree(Tree* tree, Node* one, Node* two, int binary);
void degree_of_node(Tree* tree, char node);
void degree_of_tree(Tree* tree, Node* one, Node* two, int binary);
void delete_node(Tree* tree, char node, int binary);
Node* search(Tree* tree, Node* node, char data);
void print_tree(Tree* tree, Node* one, Node* two, int binary);
void clear(Tree* tree, Node* node);
void level_up(Node* node);
void join_trees(Tree* tree, char root);
void view();

//main
int main(){
    Tree* tree = (Tree*)malloc(sizeof(Node));
    int binary;
    tree->num = 0;
    tree->root = NULL;
    printf("CHOOSE YOUR TREE TYPE(0: GENERAL, 1: BINARY)\n>>> ");
    scanf("%d", &binary);
    printf("\n");
    view();
    while (1){
        char request[21] = {0};
        if (tree->num == 0){
            printf("THE TREE IS EMPTY!\n");
        }
        else print_tree(tree, tree->root, tree->root, binary);
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
                        printf("[%c] IS NOT IN THE TREE!\n", request[i+1]);
                    }
                    else{
                        i += 3;
                        while (request[i] != ')'){
                            insert_child(tree, node, request[i], binary);
                            i++;
                        }
                    }
                }
                break;
            case '=':
                if (request[i+1] == '+'){
                    Node* node = search(tree, tree->root, request[i+2]);
                    insert_sibling(tree, node, request[i+4], binary);
                    i++;
                }
                break;
            case 'C':
                get_child(tree, request[i+1], binary);
                break;
            case 'P':
                get_parent(tree, request[i+1]);
                break;
            case 'S':
                get_sibling(tree, request[i+1], binary);
                break;
            case 'A':
                get_ancestors(tree, request[i+1]);
                break;
            case 'D':
                get_descendants(tree, request[i+1], binary);
                break;
            case 'L':
                if (strlen(request) == 2){
                    level_of_node(tree, request[i+1]);
                }
                else level_of_tree(tree, tree->root, tree->root, binary);
                break;
            case 'G':
                if (strlen(request) == 2){
                    degree_of_node(tree, request[i+1]);
                }
                else degree_of_tree(tree, tree->root, tree->root, binary);
                break;     
            case '#':
                printf("COUNT NODE: %d\n", tree->num);
                break;
            case 'T':
                break;
            case 'J':
                join_trees(tree, request[i+1]);
                break;
            case '-':
                delete_node(tree, request[i+1], binary);
                break;
            case 'K':
                clear(tree, tree->root);
                break;
            default:
                break;
            }
        }
    }
    free(tree);
    return 0;
}

//functions specific
void create(Tree* tree, char root){
    if (tree->num != 0){
        printf("THE TREE ALREADY HAS A ROOT NODE\n");
        return;
    }
    Node* new = (Node*)malloc(sizeof(Node));
    tree->root = new;
    new->data = root;
    new->left = NULL;
    new->right = NULL;
    new->parent = NULL;
    new->level = 0;
    new->degree = 0;
    tree->num++;
}

void insert_child(Tree* tree, Node* node, char child, int binary){
    Node* new = (Node*)malloc(sizeof(Node));
    if (binary){
        if (node->left != NULL && node->right != NULL){
            printf("CANNOT INSERT [%c]\n", child);
            return;
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
    new->parent = node;
    new->left = NULL;
    new->right = NULL;
    new->level = node->level + 1;
    new->degree = 0;
    node->degree++;
    tree->num++;
}

void insert_sibling(Tree* tree, Node* node, char sibling, int binary){
    if (tree->num == 0) {
        printf("THE TREE IS EMPTY!\n");
        return;
    }  
    Node* crnt = node;
    if (crnt == NULL){
        printf("[%c] IS NOT IN THE TREE!\n", crnt->data);
        return;
    }
    else if (crnt == tree->root){
        printf("[%c] IS THE ROOT NODE!\n", crnt->data);
        return;
    }
    crnt = crnt->parent;
    Node* sib = malloc(sizeof(Node));
    sib->parent = crnt;
    sib->level = crnt->level;
    if (!binary){
        crnt = crnt->left;
        while (crnt->right != NULL){
            crnt = crnt->right;
        }          
        crnt->right = sib;
        sib->level = crnt->level;
    }
    else{
        if (crnt->left == NULL){
            crnt->left = sib;
        } 
        else if (crnt->right == NULL){
            crnt->right = sib;
        }
        else {
            printf("CANNOT INSERT [%c]\n", sibling);
            return;
        }
    }
    sib->data = sibling;
    sib->left = NULL;
    sib->right = NULL;
    tree->num++;             
}

void get_child(Tree* tree, char parent, int binary){
    if (tree->num == 0) {
        printf("THE TREE IS EMPTY!\n");
        return;
    }  
    Node* crnt = search(tree, tree->root, parent);
    if (crnt == NULL){
        printf("[%c] IS NOT IN THE TREE!\n", parent);
        return;
    }
    if (crnt->data == parent){
        if (crnt->left == NULL) {
            printf("[%c] DOES NOT HAVE CHILD!\n", parent);
            return;
        }
        if (!binary){
            crnt = crnt->left;
            printf("{%c", crnt->data);
            while (1){
                if (crnt->right == NULL){
                    break;
                }
                crnt = crnt->right;
                printf(",%c", crnt->data);
            }
        }
        else{
            Node* temp = crnt->left;
            printf("{%c", temp->data);
            if (crnt->right != NULL){
                crnt = crnt->right;
                printf(",%c", crnt->data);
            }
        }
        printf("}\n");
    }
}

void get_parent(Tree* tree, char child){
    if (tree->num == 0) {
        printf("THE TREE IS EMPTY!\n");
        return;
    }   
    Node* crnt = search(tree, tree->root, child);
    if (crnt == NULL){
        printf("[%c] IS NOT IN THE TREE!\n", child);
        return;
    }
    if (crnt->data == child){
        if (crnt->parent == NULL) {
            printf("[%c] IS THE ROOT NODE!\n", child);
            return;
        }
        printf("[%c] IS THE PARENT NODE OF [%c]\n", crnt->parent->data, child);
    }
}

void get_sibling(Tree* tree, char sibling, int binary){
    if (tree->num == 0) {
        printf("THE TREE IS EMPTY!\n");
        return;
    } 
    int idx = 0;
    Node* crnt = search(tree, tree->root, sibling);
    if (crnt == NULL){
        printf("[%c] IS NOT IN THE TREE!\n", sibling);
        return;
    }
    else if (crnt == tree->root){
        printf("[%c] IS THE ROOT NODE!\n", crnt->data);
        return;
    }
    Node* find = crnt;
    if (!binary){
        crnt = crnt->parent->left;
        printf("{");
        if (crnt != find){
            printf("%c", crnt->data);
            idx = 1;
        }
        while(1){
            if (crnt->right == NULL) break;
            crnt = crnt->right;
            if (crnt != find && idx == 0){
                printf("%c", crnt->data);
                idx = 1;
            }
            else if (crnt != find && idx == 1){
                printf(",%c", crnt->data);
            }
        }  
        printf("}\n");
    }
    else{
        crnt = crnt->parent;
        if (crnt->left != find && crnt->left != NULL){
            printf("THE SIBLING OF [%c] IS [%c]\n", sibling, crnt->left->data);
        }
        else if (crnt->right != find && crnt->right != NULL){
            printf("THE SIBLING OF [%c] IS [%c]\n", sibling, crnt->right->data);
        }
        else printf("[%c] DOES NOT HAVE SIBLING!\n", sibling);
    }
}

void get_ancestors(Tree* tree, char node){
    if (tree->num == 0) {
        printf("THE TREE IS EMPTY!\n");
        return;
    }   
    Node* crnt = search(tree, tree->root, node);
    int idx = 0;
    if (crnt == NULL){
        printf("[%c] IS NOT IN THE TREE!\n", node);
        return;
    }
    if (crnt->data == node){
        if (crnt->parent == NULL) {
            printf("[%c] IS THE ROOT NODE!\n", node);
            return;
        }
        while (1){
            crnt = crnt->parent;
            if (idx == 0) {
                printf("{%c", crnt->data);
                idx = 1;
                }
            else printf(",%c", crnt->data);
            if (crnt == tree->root) break;
        }
        printf("}\n");
    }    
}

void get_descendants(Tree* tree, char node, int binary){
    if (tree->num == 0) {
        printf("THE TREE IS EMPTY!\n");
        return;
    }  
    Node* crnt = search(tree, tree->root, node);
    Node* find = crnt;
    if (crnt == NULL){
        printf("[%c] IS NOT IN THE TREE!\n", node);
        return;
    }
    if (crnt->data == node){
        if (crnt->left == NULL) {
            printf("[%c] DOES NOT HAVE CHILD!\n", node);
            return;
        }
        if (!binary){
            crnt = crnt->left;
            printf("{%c", crnt->data);
            while (crnt->left != NULL){
                crnt = crnt->left;
                printf(",%c", crnt->data);
            }
            Node* temp = crnt;
            while (temp->right != NULL){
                if (temp == find) break;
                while (crnt->right != NULL){
                    printf(",%c", crnt->right->data);
                    crnt = crnt->right;
                }
                temp = temp->parent;
                crnt = temp;
            }
            printf("}\n");
            }    
        else {
            crnt = crnt->left;
            printf("{%c", crnt->data);            
            while (crnt->left != NULL){
                crnt = crnt->left;
                printf(",%c", crnt->data);
                printf(",%c", crnt->parent->right->data);
            }
            printf("}\n");
        }
    }
}

void level_of_node(Tree* tree, char node){
    if (tree->num == 0) {
        printf("THE TREE IS EMPTY!\n");
        return;
    }  
    Node* crnt = search(tree, tree->root, node);
    if (crnt == NULL){
        printf("[%c] IS NOT IN THE TREE!\n", node);
        return;
    }
    printf("LEVEL OF NODE [%c] IS %d\n", node, crnt->level);
}

void level_of_tree(Tree* tree,Node* one, Node* two, int binary){
    int level = tree->root->level;
    if (tree->num == 0) {
        printf("THE TREE IS EMPTY!\n");
        return;
    }
    if (!binary){
        Node* crnt = two->left;
        while (crnt != NULL){
            if (crnt->level > level){
                level = crnt->level;
            }
            crnt = crnt->left;
        }
    }
    else{
        Node* crnt = one; 
        while (crnt != NULL){
            if (crnt->level > level){
                level = crnt->level;
            }
            crnt = crnt->left;
        }
        crnt = one; 
        while (crnt != NULL){
            if (crnt->level > level){
                level = crnt->level;
            }
            crnt = crnt->right;
        }
    }
    printf("LEVEL OF THE TREE IS %d\n", level);
}

void degree_of_node(Tree* tree, char node){
    if (tree->num == 0) {
        printf("THE TREE IS EMPTY!\n");
        return;
    }  
    Node* crnt = search(tree, tree->root, node);
    if (crnt == NULL){
        printf("[%c] IS NOT IN THE TREE!\n", node);
        return;
    }
    printf("DEGREE OF NODE [%c] IS %d\n", node, crnt->degree);    
}

void degree_of_tree(Tree* tree, Node* one, Node* two, int binary){
    int deg = tree->root->degree;
    if (tree->num == 0) {
        printf("THE TREE IS EMPTY!\n");
        return;
    }
    if (!binary){
        Node* crnt = two->left;
        while (crnt != NULL){
            if (crnt->level > deg){
                deg = crnt->degree;
            }
            crnt = crnt->right;
        }
    }
    else{
        Node* crnt = one; 
        while (crnt->left != NULL){
            if (crnt->degree > deg){
                deg = crnt->degree;
            }
            crnt = crnt->left;
        }
        while (crnt->right != NULL){
            if (crnt->degree > deg){
                deg = crnt->degree;
            }
            crnt = crnt->right;
        }
    }
    printf("DEGREE OF THE TREE IS %d\n", deg);    
}

void delete_node(Tree* tree, char node, int binary){
    if (tree->num == 0) {
        printf("THE TREE IS EMPTY!\n");
        return;
    }
    Node* find = search(tree, tree->root, node);    
    if (find == NULL){
        printf("[%c] IS NOT IN THE TREE!\n", node);
        return;
    }
    if (find == tree->root){
        printf("[%c] IS THE ROOT NODE!\n", node);
        return;
    }
    if (binary){
        if (find->left != NULL || find->right != NULL){
            printf("CANNOT DELETE [%c]\n", find->data);
            return;
            }
        Node* crnt = find->parent;
        if (find->left == NULL) {
            if (crnt->left == find){
                if (crnt->right == NULL){
                    crnt->left = NULL;
                    }
                else {
                    crnt->left = crnt->right;
                    crnt->right = NULL;
                    }
                }
            else{
                crnt->right = NULL;
            }
        }
    }
    else{
        find = search(tree, tree->root, node);
        Node* crnt = find->parent;
        Node* prev;
        Node* sib;
        if (find->degree != 0){
            printf("CANNOT DELETE [%c]\n", find->data);
            return;            
        }
        if (find->left == NULL){
            if (crnt->left == find){
                if (crnt->right == NULL){
                    crnt->left = NULL;
                    crnt->left = find->right;
                }
                else crnt->left = find->right;
            }        
            else{
                prev = crnt->left;
                sib = prev;
                while (1){
                    sib = sib->right;
                    if (sib->data == find->data) break;
                    prev = prev->right; 
                    }
                if (find->right == NULL){
                    prev->right = NULL;
                    }
                else {
                    prev->right = find->right;
                    }
                }
            }
        }
    find->parent->degree--;
    free(find);
    tree->num--;
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
    if (!binary){
        Node* crnt = two->left;
        if (one == two){
            printf("lv%d: %c\n", one->level, one->data);
        }
        if (one->left == NULL) return;
        while(crnt != NULL){
            printf("lv%d: %c\n", crnt->level, crnt->data);
            if (crnt->left != NULL) print_tree(tree, one, crnt, binary);
            crnt = crnt->right;
        }
    }
    else{
        Node* crnt = one;
        printf("lv%d: %c\n", one->level, one->data);
        if (one->left != NULL){
            print_tree(tree, one->left, two, binary);
        if (one->right != NULL){
            while (1){
                crnt = crnt->right;
                printf("lv%d: %c\n", crnt->level, crnt->data);
                if (crnt->left != NULL){
                    print_tree(tree, crnt->left, two, binary);
                    }
                if (crnt->right == NULL) break;
                }
            }
        }
    }
}

void clear(Tree* tree, Node* node){
    if (tree->num == 0) {
        printf("THE TREE IS EMPTY!\n");
        return;
    }
    if (node->left != NULL){
        clear(tree, node->left);
    }
    else if (node->right != NULL){
        clear(tree, node->right);
    }
    if (tree->root == node){
        tree->num = 0;
        tree->root = NULL;
    }
    free(node);
}

void level_up(Node* node){
    if (node == NULL) return;
    else{
        node->level++;
        level_up(node->left);
        level_up(node->right);
    }
}

void join_trees(Tree* tree, char root){
    if (tree->num == 0) {
        printf("THE TREE IS EMPTY!\n");
        return;
    }
    Node* nroot = malloc(sizeof(Node));
    Node* crnt = tree->root;
    tree->num++;
    tree->root = nroot;
    nroot->data = root;
    nroot->left = crnt;
    nroot->right = NULL;
    level_up(crnt);
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
    printf("PRINT TREE                  | T\n");
    printf("JOIN TREES                  | J(r)\n");
    printf("CLEAR TREE                  | K\n");
    printf("QUIT                        | Q\n");
    printf("===SOME WARNINGS TO KEEP IN MIND===\n");
    printf("* p: PARENT, c: CHILD, s: SIBLING\n");
    printf("* t: TREE, r: ROOT, n: NODE\n");
    printf("* 1. No spacing between commands.\n");
    printf("* 2. Do not use commas.\n");
    printf("* 3. Use brackets ONLY in INSERT fuctions.\n");
}