#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_NUM 30

//functions
void menu();
void insert(char arr[], char data);
void delete(char arr[]);
void traverse_front(char arr[]);
void traverse_rear(char arr[]);
void prev(char arr[]);
void next(char arr[]);
void get_data(char arr[]);
void replace(char arr[], char data);
void empty(char arr[]);
void move(char arr[], int position);
void print_array(char arr[]);
void upper(char arr[]);
void lower(char arr[]);

//settings
int current = -1;
int size = 0;

//main
int main(){
    char arr[MAX_NUM] = {0}; //create array
    menu();
    while (1){
        char request[21] = {0}; //create request
        size = strlen(arr);
        if (size != 0) print_array(arr);
        else if (size == 0) printf("THE ARRAY IS EMPTY!");
        //get request && number of requests
        printf("\n>>> "); 
        gets(request);
        int number = strlen(request);
        //ends if request is 'Q'
        if (request[0] == 'Q'){ 
            printf("THIS PROGRAM ENDS SOON\n");
            break;
            }
    //using switch statement
        for (int i = 0; i < number; i++){
            switch(request[i]){
            case '+':
                insert(arr, request[i+1]);
                i++;
                break;
            case '-':
                delete(arr);
                break;
            case '<':
                traverse_front(arr);
                break;
            case '>':
                traverse_rear(arr);
                break;
            case 'P':
                prev(arr);
                break;
            case 'N':
                next(arr);
                break;
            case '@':
                get_data(arr);
                break;
            case '=':
                replace(arr, request[i+1]);
                i++;
                break;
            case 'E':
                empty(arr);
                break;
            case 'M':
                if (request[i+1] == '\0') move(arr, 0);
                else if (request[i+1] == 'n') move(arr, size-1);
                else if (request[i+1] == 'P') move(arr, current-1);
                else if (request[i+1] == 'N') move(arr, current+1);
                else move(arr, (int)request[i+1]-48);
                i++;
                break;
            case 'L':
                break;
            case 'U':
                upper(arr);
                break;
            case 'D':
                lower(arr);
                break;
            case 'V':
                menu();
                break;
                }
            }
        }
    return 0;
}

//functions specific
void menu(){
    printf("----------------MENU----------------\n");
    printf("INSERT DATA                 | +(data)\n");
    printf("DELETE                      | -\n");
    printf("TRAVERSE_FRONT              | <\n");
    printf("TRAVERSE_REAR               | >\n");
    printf("PREVIOUS                    | P\n");
    printf("NEXT                        | N\n");
    printf("GET DATA                    | @\n");
    printf("REPLACE DATA                | =(data)\n");
    printf("EMPTY THE ARRAY             | E\n");
    printf("MOVE TO POSITION            | M(position)\n");
    printf("MOVE TO FRONT               | M\n");
    printf("MOVE TO REAR                | Mn\n");
    printf("MOVE TO PREVIOUS            | MP\n");
    printf("MOVE TO NEXT                | MN\n");
    printf("PRINT THE ARRAY             | L\n");
    printf("TO UPPER CASE               | U\n");
    printf("TO LOWER CASE               | D\n");
    printf("VIEW MENU                   | V\n");
    printf("QUIT                        | Q\n");
    printf("===SOME WARNINGS TO KEEP IN MIND===\n");
    printf("* Q should be used ALONE.\n");
    printf("* SPACING between COMMANDS.\n");
    printf("* ONLY 1 data per 1 command.\n");
}

void insert(char arr[], char data){
    size = strlen(arr);
    if (size == MAX_NUM) printf("THE ARRAY IS FULL!");
    else
        current++;
        for (int i = size; i >= current; i--) arr[i] = arr[i-1];
        arr[current] = data;
}

void delete(char arr[]){
    size = strlen(arr);
    for (int i = current; i < size-1; i++) arr[i] = arr[i+1];
    arr[size-1] = '\0';
    if (current == size-1) current--;
}

void traverse_front(char arr[]){
    current = 0;
}

void traverse_rear(char arr[]){
    size = strlen(arr);
    current = size-1;
}

void prev(char arr[]){
    current--;
}

void next(char arr[]){
    current++;
}

void get_data(char arr[]){
    printf("arr[%d]: %c\n", current, arr[current]);
}

void replace(char arr[], char data){
    arr[current] = data;
}

void empty(char arr[]){
    for (int i = 0; i < size; i++) arr[i] = NULL;
    current = -1;
}

void move(char arr[], int position){
    char temp;
    if (current > position){
        for (int i = current; i > position; i--) {
            temp = arr[i-1];
            arr[i-1] = arr[i];
            arr[i] = temp;
            } 
        }
    else {
        for (int i = current; i < position; i++) {
            temp = arr[i+1];
            arr[i+1] = arr[i];
            arr[i] = temp;
            } 
        }
    current = position;
}

void print_array(char arr[]){
    size = strlen(arr);
    for (int i = 0; i < size; i++){
        if (i == current) printf("[%c] ", arr[i]);
        else if (i != current) printf("%c ", arr[i]);
        }
}

void upper(char arr[]){
    if ((arr[current] >= 'a') && (arr[current] <= 'z')){
        arr[current] = arr[current] -'a' + 'A';
        }
}

void lower(char arr[]){
    if ((arr[current] >= 'A') && (arr[current] <= 'a')){
        arr[current] = arr[current] -'A' + 'a';
        }
}