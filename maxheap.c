#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_NUM 50

//max heap
typedef struct element {
    int key;
}Element;

typedef struct heap {
    Element heap[MAX_NUM];
    int num;
}Heap;

//binary search tree
typedef struct node {
    int value;
    struct node* left;
    struct node* right;
}Node;

int num = 0;

//functions
void insert_max_heap(Heap* heap, Element value);
void insert_node(Node* root, int value);
void print_bst(Node* one, Node* two);

//main
int main() {
    Heap heap;
    Node* root = (Node*)malloc(sizeof(Node));
    heap.num = 0;
    while (1) {
        printf("INPUT (-1 to stop): ");
        Element request;
        scanf("%d", &(request.key));
        if (request.key == -1) {
            printf("\n<<< END INSERT && CHANGE TO BST >>>\n");
            break;
        }
        insert_max_heap(&heap, request);
    }
    printf("\nMAX HEAP: ");
    insert_node(root, heap.heap[heap.num/2].key);
    for (int i = 1; i <= heap.num; i++) {
        printf("%d ", heap.heap[i].key);
        if (i != heap.num/2) {
            insert_node(root, heap.heap[i].key);
            }
    }
    printf("\n\nBINARY SEARCH TREE: ");
    print_bst(root, root);
    printf("\n");
    free(root);
    return 0;
}

//functions specific
void insert_max_heap(Heap* heap, Element value) {
    int i = 0; 
    int crnt; 
    heap->num++; 
    i = heap->num; 
    heap->heap[i].key = value.key; 
    while (i > 1) {
        if (heap->heap[i/2].key < heap->heap[i].key) {
            crnt = heap->heap[i].key;
            heap->heap[i].key = heap->heap[i/2].key;
            heap->heap[i/2].key = crnt;
            i = i/2;
        }
        else break;
    }
}

void insert_node(Node* root, int value) {
    Node* new = (Node*)malloc(sizeof(Node));
    new->value = value;
    new->left = NULL;
    new->right = NULL;
    if (num == 0) {
        new = root;
        root->value = value;
        num++;
        return;
    }
    if (root->value < value) {
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
        return;
    }
}

void print_bst(Node* one, Node* two) {
    if (one == two) printf("%d", one->value);
    Node* crnt = two->left;
    if (two->left != NULL) {
        printf("(%d", crnt->value);
        print_bst(one, crnt);
        if (two->right != NULL) {
            printf(",%d", two->right->value);
            print_bst(one, two->right);
            printf(")");
        }
        else printf(",)");
    }
    else if (two->right != NULL) {
        printf("(,%d", two->right->value);
        print_bst(one, two->right);
        printf(")");
    }
}