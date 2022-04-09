#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)
#pragma warning(disable:4047)

//deque
typedef struct Node{
    char data;
    struct Node* prev;
    struct Node* next;
}Node;

typedef struct Deque{
    Node* front;
    Node* rear;
    int len;
}Deque;

//functions
void init(Deque* deque);
int is_empty(Deque* deque);
void add_front(Deque* deque, char element);
void add_rear(Deque* deque, char element);
char delete_front(Deque* deque);
char delete_rear(Deque* deque);
void get_front(Deque* deque);
void get_rear(Deque* deque);
void print_deque(Deque* deque);
void view();

//main
int main(){
    Node* front = malloc(sizeof(Node)); //create node
    Deque* deque = malloc(sizeof(Node)); 
    deque->front = front;
    deque->rear = front;
    deque->len = 0;
    front->data = NULL;
    front->next = NULL;
    front->prev = NULL;
    view();
    while (1){
        print_deque(deque);
        char request[21] = {0};
        printf("\n>>> ");
        gets(request);
        if (request[0] == 'Q'){
            printf("THIS PROGRAM WILL END SOON!\n");
            break;
        }
        for (int i = 0; i < strlen(request); i++){
            switch (request[i]){
            case 'H':
                if (request[i+1] == '+') {
                    add_front(deque, request[i+2]);
                    i++;
                }
                else if (request[i+1] == '-') printf("DEQUEUED ELEMENT: %c\n", delete_front(deque));
                else if (request[i+1] == 'G') get_front(deque);
                i++;
                break;
            case 'R':
                if (request[i+1] == '+') {
                    add_rear(deque, request[i+2]);
                    i++;
                }
                else if (request[i+1] == '-') printf("DEQUEUED ELEMENT: %c\n", delete_rear(deque));
                else if (request[i+1] == 'G') get_rear(deque);
                i++;
                break;
            case 'F': //dynamic, so never full
                printf("THIS DEQUE IS DYNAMIC, SO IT CANNOT BE FULL.\n");
                break;
            case 'E':
                if (is_empty(deque) == 1) printf("True\n");
                else printf("False\n");
                break;
            case 'I':
                init(deque);
                break;
            case 'V':
                view();
                break;
            case 'L':
                break;
            }
            i++;
        }
    }
    free(deque);
    return 0;
}

//functions specific
void init(Deque* deque){
    Node* clear = deque->front->next;
    while (clear != NULL){
        clear = clear->next;
    }
    free(clear);
    deque->front->next = NULL;
    deque->front->data = NULL;
    deque->front->prev = NULL;
    deque->len = 0;
    printf("THE DEQUE IS CLEARED!\n");
}

int is_empty(Deque* deque){
    if (deque-> len == 0) return 1;
    else return 0;
}

void add_front(Deque* deque, char element){
    if (deque->len == 0){
        deque->front->data = element;
    } 
    else {
        Node* new = (Node*)malloc(sizeof(Node));
        new->data = element;
        new->next = deque->front;
        deque->front->prev = new;
        deque->front = new;
        deque->front->prev = NULL;
    }
    deque->len++;
}

void add_rear(Deque* deque, char element){
    if (deque->len == 0){
        deque->front->data = element;
    } 
    else {
        Node* new = (Node*)malloc(sizeof(Node));
        new->data = element;
        new->prev = deque->rear;
        deque->rear->next = new;
        deque->rear = new;
        deque->rear->next = NULL;
    }
    deque->len++;
}

char delete_front(Deque* deque){
    if (deque->len == 0){
        printf("NOTHING TO DELETE!\n");
        return '~';
    }
    else if (deque->len == 1){
        char d1 = deque->front->data;
        init(deque);
        return d1;
    }
    Node* del = deque->front;
    char d2 = deque->front->data;
    deque->front = deque->front->next;
    deque->front->prev = NULL;
    free(del);
    deque->len--;
    return d2;
}

char delete_rear(Deque* deque){
    if (deque->len == 0){
        printf("NOTHING TO DELETE!\n");
        return '~';
    }
    else if (deque->len == 1){
        char d1 = deque->rear->data;
        init(deque);
        return d1;
    }
    Node* del = deque->rear;
    char d2 = deque->rear->data;
    deque->rear = deque->rear->prev;
    deque->rear->next = NULL;
    free(del);
    deque->len--;
    return d2;
}

void get_front(Deque* deque){
    if (deque->len == 0){
        printf("THE DEQUE IS EMPTY!\n");
        return;
    }
    printf("CURRENT FRONT: %c\n", deque->front->data);
}

void get_rear(Deque* deque){
    if (deque->len == 0){
        printf("THE DEQUE IS EMPTY!\n");
        return;
    }
    printf("CURRENT REAR: %c\n", deque->rear->data);
}

void print_deque(Deque* deque){
    if (deque->len == 0){
        printf("THE DEQUE IS EMPTY!\n");
        return;
    }
    Node* pos = deque->front;
    for (int i = 0; i < deque->len; i++){
        printf("%c ", pos->data);
        pos = pos->next;
    }
}

void view(){
    printf("-----------------MENU-----------------\n");
    printf("INITIALIZE DEQUE            | I\n");
    printf("IS EMPTY                    | E\n");
    printf("IS FULL                     | F\n");
    printf("ADD FRONT                   | H+(element)\n");
    printf("DELETE FRONT                | H-\n");
    printf("GET FRONT                   | HG\n");
    printf("ADD REAR                    | R+(element)\n");
    printf("DELETE REAR                 | R-\n");
    printf("GET REAR                    | RG\n");
    printf("VIEW MENU                   | V\n");
    printf("PRINT DEQUE                 | L\n");
    printf("QUIT                        | Q\n");
    printf("===SOME WARNINGS TO KEEP IN MIND===\n");
    printf("* SPACING between COMMANDS.\n");
    printf("* ONLY 1 element per 1 command.\n");
}