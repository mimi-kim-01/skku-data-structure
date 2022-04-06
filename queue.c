#include <stdio.h>
#include <string.h>
#define MAX_NUM 5

//queue
typedef struct queue{
    char data[MAX_NUM];
    int tail; 
    int head;
    int num;
}Queue;

//functions
void enqueue(Queue* queue, char data);
char dequeue(Queue* queue);
char peek(Queue* queue);
int is_full(Queue* queue);
int is_empty(Queue* queue);
void is_member(Queue* queue, char data);
void data_count(Queue* queue);
void head(Queue* queue);
void tail(Queue* queue);
void replace(Queue* queue, char data);
void clear(Queue* queue);
void upper(Queue* queue);
void lower(Queue* queue);
void print_queue(Queue* queue);
void view();

//main
int main(){
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->head = -1; //initialize head
    queue->tail = -1; //initialize tail
    view();
    while (1){
        print_queue(queue);
        int count = 0; //for 'default case' in switch statement
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
                enqueue(queue, request[i+1]);
                i++;
                break;
            case '-':
                printf("DEQUEUED ELEMENT: %c\n", dequeue(queue));
                break;
            case 'P':
                printf("CURRENT HEAD: %c\n", peek(queue));
                break;
            case 'F':
                if (is_full(queue) == 1) printf("True\n");
                else printf("False\n");
                break;
            case 'E':
                if (is_empty(queue) == 1) printf("True\n");
                else printf("False\n");
                break;
            case '?':
                is_member(queue, request[i+1]);
                i++;
                break;
            case '#':
                data_count(queue);
                break;
            case 'H':
                head(queue);
                break;
            case 'T':
                tail(queue);
                break;
            case '=':
                replace(queue, request[i+1]);
                i++;
                break;
            case 'C':
                clear(queue);
                break;
            case 'U':
                upper(queue);
                break;
            case 'D':
                lower(queue);
                break;
            case 'L':
                break;
            case 'V':
                view();
            default:
                for (count = 0; count < request[i] - '0'; count++){
                    printf("DEQUEUED ELEMENT: %c\n", dequeue(queue)); 
                }
                i++;
                break;
            }
            i++;
        }
    }
    free(queue);
    return 0;
}

//functions specific
void enqueue(Queue* queue, char data){
    if (is_full(queue) == 1) printf("THE QUEUE IS FULL!\n");
    else if (queue->tail == MAX_NUM - 1){
        int index = 0;
        for (int i = queue->head + 1; i <= queue->tail; i++){
            queue->data[index] = queue->data[i];
            index++;
        }
        queue->head--;
        queue->data[queue->tail] = data;
        queue->num++;
    }
    else{
        queue->tail++;
        queue->data[queue->tail] = data;
        queue->num++;
    }
}

char dequeue(Queue* queue){
    if (is_empty(queue) == 1) {
        printf("NOTHING TO DEQUEUE!\n");
        return '~';
    }
    else {
        char dequeued = queue->data[queue->head+1];
        queue->data[queue->head+1] = NULL;
        queue->head++;
        queue->num--;
        return dequeued;
    }
}

char peek(Queue* queue){
    if (is_empty(queue) == 1) {
        printf("THE QUEUE IS EMPTY!");
        return 0;
    }
    else return queue->data[queue->head+1];
}

int is_full(Queue* queue){
    if (queue->num == MAX_NUM) return 1;
    else return 0;
}

int is_empty(Queue* queue){
    if (queue->num == 0) return 1;
    else return 0;
}

void is_member(Queue* queue, char data){
    for (int i = queue->head + 1; i <= queue->tail; i++){
        if (queue->data[i] == data){
            printf("True\n");
            return;
        }
    }
    printf("False\n");
}

void data_count(Queue* queue){
    if (queue->num == 0) printf("THE STACK IS EMPTY!\n");
    else printf("DATA COUNT: %d\n", queue->num);
}

void head(Queue* queue){
    printf("%d\n", queue->head+2);
}

void tail(Queue* queue){
    printf("%d\n", queue->tail+1);
}

void replace(Queue* queue, char data){
    queue->data[queue->tail] = data;
}

void clear(Queue* queue){
    while (queue->num != 0){
        dequeue(queue);
    }
}

void upper(Queue* queue){
    if ((queue->data[queue->tail] >= 'a') && (queue->data[queue->tail] <= 'z')){
         queue->data[queue->tail] = queue->data[queue->tail] -'a' + 'A';
    }
}

void lower(Queue* queue){
    if ((queue->data[queue->tail] >= 'A') && (queue->data[queue->tail] <= 'Z')){
         queue->data[queue->tail] = queue->data[queue->tail] -'A' + 'a';
    }
}

void print_queue(Queue* queue){
    if (queue->num == 0) printf("THE QUEUE IS EMPTY!");
    else {
        for (int i = queue->head + 1; i <= queue->tail; i++) printf("%c ", queue->data[i]);
    }
}

void view(){
    printf("-----------------MENU-----------------\n");
    printf("ENQUEUE                     | +(data)\n");
    printf("DEQUEUE                     | -\n");
    printf("PEEK                        | P\n");
    printf("HEAD                        | H\n");
    printf("TAIL                        | T\n");
    printf("REPLACE DATA                | =(data)\n");
    printf("DATA COUNT                  | #\n");
    printf("IS MEMBER                   | ?(data)\n");
    printf("IS FULL                     | F\n");
    printf("CLEAR QUEUE                 | C\n");
    printf("TO UPPER CASE               | U\n");
    printf("TO LOWER CASE               | D\n");
    printf("VIEW MENU                   | V\n");
    printf("PRINT QUEUE                 | L\n");
    printf("QUIT                        | Q\n");
    printf("===SOME WARNINGS TO KEEP IN MIND===\n");
    printf("* SPACING between COMMANDS.\n");
    printf("* ONLY 1 element per 1 command.\n");
    printf("* 5- means DEQUEUE FOR 5 TIMES.\n");
}