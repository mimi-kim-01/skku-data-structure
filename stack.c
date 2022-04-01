#include <stdio.h>
#define MAX_NUM 10

//stack
typedef struct stack
{
    char* data[MAX_NUM];
    int* top;
}Stack;

//functions
void create(Stack* stack);
void push(Stack* stack, char element);
void pop(Stack* stack);
void peek(Stack* stack);
void is_full(Stack* stack);
void element_count(Stack* stack);
void top(Stack* stack);
void is_member(Stack* stack, char element);
void replace(Stack* stack, char element);
void clear(Stack* stack);
void print_stack(Stack* stack);
void upper(Stack* stack);
void lower(Stack* stack);
void view();

//main
int main(){
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    view();
    while (1){
        print_stack(stack);
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


    return 0;
}

//functions specific
void create(Stack* stack);
void push(Stack* stack, char element);
void pop(Stack* stack);
void peek(Stack* stack);
void is_full(Stack* stack);
void element_count(Stack* stack);
void top(Stack* stack);
void is_member(Stack* stack, char element);
void replace(Stack* stack, char element);
void clear(Stack* stack);
void print_stack(Stack* stack);
void upper(Stack* stack);
void lower(Stack* stack);
void view();