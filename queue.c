#include <stdio.h>
#include <string.h>
#define MAX_NUM 5

//queue
typedef struct stack{
    char data[MAX_NUM];
    int tail; 
    int head;
}Queue;

//functions
void enqueue(Queue* queue, char data);
char dequeue(Queue* queue);
char peek(Queue* queue);
void is_full(Queue* queue);
void is_empty(Queue* queue);
void is_member(Queue* queue);
void data_count(Queue* queue);
void head(Queue* queue);
void tail(Queue* queue);
void replace(Queue* queue);
void clear(Queue* queue);
void upper(Queue* queue, int index);
void lower(Queue* queue, int index);
void print_queue(Queue* queue);
void view();

//main
int main(){
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->head = -1; //initialize head
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
            }
        }
    }
    free(queue);
    return 0;
}

//functions specific
void enqueue(Queue* queue, char data);
char dequeue(Queue* queue);
char peek(Queue* queue);
void is_full(Queue* queue);
void is_empty(Queue* queue);
void is_member(Queue* queue);
void data_count(Queue* queue);
void head(Queue* queue);
void tail(Queue* queue);
void replace(Queue* queue);
void clear(Queue* queue);
void upper(Queue* queue, int index);
void lower(Queue* queue, int index);
void print_queue(Queue* queue);
void view();