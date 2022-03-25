#include <stdio.h>

//struct
typedef struct Node{
    char data;
    Node* next;
}Node;

typedef struct List{
    Node* head;
    Node* current;
    int cursor;
    int len;
}List;

//functions
void print_list(List* list);
void get_data(List* list);
void traverse_front(List* list, int count);
void traverse_rear(List* list, int count);
void delete(List* list);
void addTail(List* list, char data);
void add(List* list, char count, char data);
void replace(List* list, char new);
void data_count(List* list);
void is_member(List* list, char data);
void is_empty(List* list);
void upper(List* list);
void lower(List* list);
void view();

//main
int main(){
    Node* head = malloc(sizeof(Node)); //create 
    List* list = malloc(sizeof(List)); 
    list->head = head;
    list->current = list->head;
    list->cursor = 0;
    list->len = 0;
    head->data = NULL;
    head->next = NULL;


    return 0;
}

//functions specific
void print_list(List* list);
void get_data(List* list);
void traverse_front(List* list, int count);
void traverse_rear(List* list, int count);
void delete(List* list);
void addTail(List* list, char data);
void add(List* list, char count, char data){
    
}

void replace(List* list, char new){
    list->current->data = new;
}

void data_count(List* list){
    printf("%d\n", list->len);
}


void is_member(List* list, char data){
    int index;
    for (index = 0; index < list->len; index++){
        if(list->current->data == data){
            printf("%d: ", index);
        }
    }
    list->cursor = index;
}

void is_empty(List* list){
    if (list->len == 0) printf("True");
    else printf("False");
}

void upper(List* list){
    if ((list->current->data >= 'a') && (list->current->data <= 'z')){
        list->current->data = list->current->data -'a' + 'A';
    }
}

void lower(List* list){
    if ((list->current->data >= 'A') && (list->current->data <= 'a')){
        list->current->data = list->current->data -'A' + 'a';
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
    printf("===SOME WARNINGS TO KEEP IN MIND===\n");
    printf("* n is a NUMBER, not an alphabet.\n");
    printf("* SPACING between COMMANDS.\n");
    printf("* ONLY 1 data per 1 command.\n");
}