#include <stdio.h>
#define MAX_NUM 10

//stack
typedef struct stack{
    char* data[MAX_NUM];
    int top; 
}Stack;

//functions
void push(Stack* stack, char element);
char pop(Stack* stack);
char peek(Stack* stack);
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
    stack->top = -1; //initialize top
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
                push(stack, request[i+1]);
                i++;
                break;
            case '-':
                pop(stack);
                break;
            case 'P':
                printf("CURRENT TOP: %c", peek(stack));
                break;
            case 'T':
                top(stack);
                break;
            case '=':
                replace(stack, request[i+1]);
                i++;
                break;
            case '#':
                element_count(stack);
                break;
            case '?':
                is_member(stack, request[i+1]);
                i++;
                break;
            case 'F':
                is_full(stack);
                break;
            case 'C':
                clear(stack);
                break;
            case 'U':
                upper(stack);
                break;
            case 'D':
                lower(stack);
                break;
            case 'V':
                view();
                break;
            case 'L':
                break;
            default:
                for (int i = 0; i < request[i] - '0'; i++){
                    if (request[i+1] == '-') pop(stack);
                }
                i++;
                break;
            }
            i++;
    free(stack);
    return 0;
}

//functions specific
void push(Stack* stack, char element){
    if (stack->top == MAX_NUM-1){
        printf("THE STACK IS FULL!");
    }
    else {
        stack->top++;
        stack->data[stack->top] = element
    }
}

char pop(Stack* stack){
    if (stack->top == -1){
        printf("THE STACK IS EMPTY!");
    }
    else {
        stack->top--;
        return stack->data[stack->top+1];
    }
}

char peek(Stack* stack){
    if (stack->top == -1){
        printf("THE STACK IS EMPTY!");
    }
    else {
        return stack->data[stack->top];
    }
}

void is_full(Stack* stack){
    if (stack->top == MAX_NUM - 1) printf("True");
    else printf("False");
}

void element_count(Stack* stack){
    if (stack->top == -1) printf("THE STACK IS EMPTY!");
    else prinf("ELEMENT COUNT: %d", stack->top + 1);
}

void top(Stack* stack){
    if (stack->top == -1) printf("THE STACK IS EMPTY!");
    else prinf("(%d, %c)", stack->top + 1, stack->data[stack->top]);
}

void is_member(Stack* stack, char element){
    if (stack->top == -1) printf("THE STACK IS EMPTY!");
    else {
        Stack* stacktwo = (Stack*)malloc(sizeof(Stack));
        stacktwo->top = -1;
        for (int i = 0; i < stack->top; i++){
            if (peek(stack) == element){
                printf("True");
                break;
            }
            else push(stacktwo, pop(stack));
        }
        while (stacktwo->top != -1){
            push(stack, pop(stacktwo));
        }
        printf("False");
    }
}

void replace(Stack* stack, char element){
    stack->data[stack->top] = element;
}

void clear(Stack* stack){
    if (stack->top == -1) printf("THE STACK IS EMPTY!");
    while (stack->top != -1){
        pop(stack);
    }
}

void print_stack(Stack* stack){
    if (stack->top == -1) printf("THE STACK IS EMPTY!");
    int num = stackt->top;
    else {
        Stack* stacktwo = (Stack*)malloc(sizeof(Stack));
        stacktwo->top = -1;
        for (int i = 0; i < stack->top; i++){
            push(stacktwo, pop(stack));
        }
        while (stacktwo->top != -1){
            popped = pop(stacktwo);
            if (stack->top == num - 1){
                printf("[%c] ", popped);
            }
            else printf("%c ", popped);
            push(stack, popped);
        }
    }
}

void upper(Stack* stack){
    if ((stack->data[stack->top] >= 'a') && (stack->data[stack->top] <= 'z')){
         stack->data[stack->top] = stack->data[stack->top] -'a' + 'A';
    }
}

void lower(Stack* stack){
        if ((stack->data[stack->top] >= 'A') && (stack->data[stack->top] <= 'Z')){
         stack->data[stack->top] = stack->data[stack->top] -'A' + 'a';
    }
}

void view(){
    printf("-----------------MENU-----------------");
    printf("PUSH                        | +(element)\n");
    printf("POP                         | -\n");
    printf("PEEK                        | P\n");
    printf("TOP                         | T\n");
    printf("REPLACE ELEMENT             | =(element)\n");
    printf("ELEMENT COUNT               | #\n");
    printf("IS MEMBER                   | ?(element)\n");
    printf("IS FULL                     | F\n");
    printf("CLEAR STACK                 | C\n");
    printf("TO UPPER CASE               | U\n");
    printf("TO LOWER CASE               | D\n");
    printf("VIEW MENU                   | V\n");
    printf("PRINT STACK                 | L\n");
    printf("QUIT                        | Q\n");
    printf("===SOME WARNINGS TO KEEP IN MIND===\n");
    printf("* SPACING between COMMANDS.\n");
    printf("* ONLY 1 element per 1 command.\n");
    printf("* 5- means POP for 5 times.\n");
}