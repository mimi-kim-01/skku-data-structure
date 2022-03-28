#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)
#pragma warning(disable:4047)

//linkedlist
typedef struct Node{
    char data;
    struct Node* next;
}Node;

typedef struct List{
    Node* head;
    Node* position;
    int current; 
    int len;
}List;

//functions
void print_list(List* list);
void get_data(List* list);
void traverse_front(List* list, int count);
void traverse_rear(List* list, int count);
void move_position(List* list, int index);
void delete(List* list);
void addTail(List* list, char data);
void add(List* list, char count, char data);
void replace(List* list, char new);
void data_count(List* list);
void is_member(List* list, char data);
void is_empty(List* list);
void clear(List *list);
void upper(List* list);
void lower(List* list);
void view();

//main
int main(){
    Node* head = malloc(sizeof(Node)); //create node
    List* list = malloc(sizeof(Node)); 
    list->head = head;
    list->position = list->head;
    list->current = 0;
    list->len = 0;
    head->data = NULL;
    head->next = NULL;
    //warnings
    printf("Our group decided to differentiate the input forms of ADD function\n");
    printf("PLEASE READ OUR MENU CAREFULLY!\n");
    view();
    while (1){
        print_list(list);
        char request[21] = {0};
        printf("\n>>> ");
        gets(request);
        if (request[0] == 'Q'){
            printf("THIS PROGRAM WILL END SOON!\n");
            break;
        }
        for (int i = 0; i < strlen(request); i++){
            switch (request[i]){
            case 'G':
                get_data(list);
                break;
            case '+':
                if (request[i+1] == '\0') break;
                if (list->len == 0) addTail(list, request[i+1]);
                else {
                    add(list, '\0', request[i+1]);
                }
                i++;
                break;
            case 'N':
                add(list, request[i], request[i+2]);
                i += 3;
                break;
            case 'T':
                addTail(list, request[i+2]);
                i += 3;
                break;
            case '<': ;
                int cnt = 0;
                for(int i = 1; request[i] != NULL; i++){
                    if (request[i] == 'N') cnt++;
                    else continue;
                }
                i += 2*cnt;
                traverse_front(list, cnt);
                break;
            case '>': ;
                int ccnt = 0;
                for(int i = 1; request[i] != NULL; i++){
                    if (request[i] == 'P') ccnt++;
                    else continue;
                }
                i += 2*ccnt;
                traverse_rear(list, ccnt);
                break;
            case '-':
                delete(list);
                break;
            case '=':
                replace(list, request[i+1]);
                i++;
                break;
            case '#':
                data_count(list);
                break;
            case '?':
                is_member(list, request[i+1]);
                i++;
                break;
            case 'E':
                is_empty(list);
                break;
            case 'C':
                clear(list);
                printf("THE LIST IS CLEARED!\n");
                break;
            case 'U':
                upper(list);
                break;
            case 'D':
                lower(list);
                break;
            case 'V':
                view();
                break;
            case 'L':
                break;
            default: //move to position
                move_position(list, request[i] - '0');
                break;
            }
            i++;
        }
    }
    return 0;
}

//functions specific
void print_list(List* list){
    Node* current = list->head->next;
    int index = 0;
    if (current == NULL) printf("THE LIST IS EMPTY!");
    else {
        while (current != NULL){
            if (index == list->current-1) printf("[%c] ", current->data);
		    else printf("%c ", current->data);
            current = current->next;
            index++;
        }
    }
}

void get_data(List* list){
    printf("CURRENT DATA: %c\n", list->position->data);
}

void traverse_front(List* list, int count){
    list->position = list->head;
    list->current = 1;
    if (count != 0){
        list->position = list->position->next;
        for (int i = 0; i < count; i++){
            list->position = list->position->next;
            list->current++;
        }
    }
}

void traverse_rear(List* list, int count){
    move_position(list, list->len - count);
}

void move_position(List* list, int index){
    Node* move = malloc(sizeof(Node));
    move = list->head->next;
    for (int i = 0; i < index - 1; i++){
        move = move->next;
    }
    list->current = index;
    list->position = move;
}

void delete(List* list){
    Node* prev = list->head;
    Node* del = list->position;
    if (list->len == 0) {
        printf("THE LIST IS EMPTY!"); 
        return;
    }
    for (int i = 0; i < list->len; i++){
        if (prev->next == del) break;
        prev = prev->next;
    }
    if (del->next == NULL){ 
        prev->next == NULL;
        if (list->len == 1){
            list->current = 0;
            list->position = list->head;
        }
        else{
            list->current = 1;
            list->position = list->head->next;
        }
        free(del); 
    }
    else{
        prev->next = del->next;
        list->position = del->next;
        free(del);
    }
    list->len--;
}

void addTail(List* list, char data){
    Node* new = malloc(sizeof(Node));
    if (list->position->next != NULL){
        Node* current = list->head;
        while (current->next != NULL){
            current = current->next;
        }
        list->position = current;
    }
    new->next = NULL;
    new->data = data;
    list->position->next = new;
    list->position = new;
    list->len++;
    if (list->len == 1) list->current++;
    else list->current++;
}

void add(List* list, char count, char data){
    Node* new = malloc(sizeof(Node));
    if (count == '\0'){
        Node* prev = malloc(sizeof(Node));
        prev = list->head;
        for (int i = 0; i <list->current-1; i++) prev = prev->next;
        new->data = data;
        new->next = list->position;
        prev->next = new;
        list->len++; //maintain current
        list->position = new;
    }
    else if (count == 'N'){
        if (list->position->next == NULL){
            new->data = data;
            new->next = NULL;
            list->position->next = new;
        }
        else {
            new->data = data;
            new->next = list->position->next;
            list->position->next = new;
        }
        list->position = new;
        list->current++;
        list->len++;
    }
}

void replace(List* list, char new){
    list->position->data = new;
}

void data_count(List* list){
    printf("DATA COUNT: %d\n", list->len);
}


void is_member(List* list, char data){
    Node* temp = list->head;
    int index;
    for (index = 0; index < list->len + 1; index++){
        if (temp->data == data){
            printf("%d: ", index);
            break;
        }
        if (temp->next == NULL) {
            printf("FAILED");
            break;
        }
        temp = temp->next;
    }
}

void is_empty(List* list){
    if (list->len == 0) printf("True\n");
    else printf("False\n");
}

void clear(List *list){
    Node* clear = list->head->next;
    while (clear != NULL){
        clear = clear->next;
    }
    free(clear);
    list->head->next = NULL;
    list->current = 0;
    list->len = 0;
    list->position = list->head;
}

void upper(List* list){
    if (( list->position->data >= 'a') && (list->position->data <= 'z')){
         list->position->data = list->position->data -'a' + 'A';
    }
}

void lower(List* list){
    if ((list->position->data >= 'A') && (list->position->data <= 'a')){
        list->position->data = list->position->data -'A' + 'a';
        }
}

void view(){
    printf("-----------------MENU-----------------");
    printf("GET DATA                    | G\n");
    printf("TRAVERSE FRONT              | <\n");
    printf("TRAVERSE REAR               | >\n");
    printf("MOVE TO POSITION(n)         | n\n");
    printf("DELETE                      | -\n");
    printf("ADD TO TAIL                 | T+(data)\n");
    printf("ADD PREVIOUS                | +(data)\n");
    printf("ADD NEXT                    | N+(data)\n");
    printf("REPLACE DATA                | =(data)\n");
    printf("DATA COUNT                  | #\n");
    printf("IS MEMBER                   | ?(data)\n");
    printf("IS EMPTY                    | E\n");
    printf("CLEAR LIST                  | C\n");
    printf("TO UPPER CASE               | U\n");
    printf("TO LOWER CASE               | D\n");
    printf("VIEW MENU                   | V\n");
    printf("PRINT LIST                  | L\n");
    printf("QUIT                        | Q\n");
    printf("===SOME WARNINGS TO KEEP IN MIND===\n");
    printf("* n is a NUMBER, not an alphabet.\n");
    printf("* SPACING between COMMANDS.\n");
    printf("* ONLY 1 data per 1 command.\n");
    printf("* TRAVERSE cannot be used with other options.\n");
    printf("* < N means traverse front and move next.\n");
    printf("* > P means traverse rear and move previous.\n");
}