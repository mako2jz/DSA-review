#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAX 10

// datatype
typedef struct node{
    int data;
    struct node *next;
}*LIST;

typedef LIST Dictionary[MAX];

// user defined functions
void initDict(Dictionary D);
int hash(int data);
void insert(Dictionary D, int data);
void delete(Dictionary D, int data);
bool member(Dictionary D, int data);
void display(Dictionary D);

int main(){
    Dictionary D;

    initDict(D);
    
    printf("Set A = {0, 13, 20, 28, 30, 33, 45, 48, 108}\n\n");
    insert(D, 0);
    insert(D, 13);
    insert(D, 20);
    insert(D, 28);
    insert(D, 30);
    insert(D, 33);
    insert(D, 45);
    insert(D, 48);
    insert(D, 108);
    display(D);

    printf("\n%d %s a member of Set A\n", 20, member(D, 20) ? "is" : "is not");
    
    printf("\nDeleting 108 and 20:\n");
    delete(D, 108);
    delete(D, 20);
    display(D);

    printf("\n%d %s a member of Set A", 20, member(D, 20) ? "is" : "is not");
    printf("\n%d %s a member of Set A", 13, member(D, 13) ? "is" : "is not");
}

void initDict(Dictionary D){
    int i;
    for(i = 0; i < MAX; i++){
        D[i] = NULL;
    }
}

int hash(int data){
    return data % MAX;
}

void insert(Dictionary D, int data){
    int start = hash(data);
    LIST *ptr;
    for(ptr = &D[start]; *ptr != NULL && data != (*ptr)->data; ptr = &(*ptr)->next){}
    if(*ptr == NULL){
        *ptr = (LIST)malloc(sizeof(struct node));
        (*ptr)->data = data;
        (*ptr)->next = NULL;
    }
}

void delete(Dictionary D, int data){
    int start = hash(data);
    LIST *ptr;
    for(ptr = &D[start]; *ptr != NULL && data != (*ptr)->data; ptr = &(*ptr)->next){}
    if(*ptr != NULL){
        LIST temp;
        temp = *ptr;
        *ptr = temp->next;
        free(temp);
    }
}

bool member(Dictionary D, int data){
    int start = hash(data);
    LIST ptr;
    for(ptr = D[start]; ptr != NULL && data != ptr->data; ptr = ptr->next){}
    return (ptr != NULL) ? true : false;
}

void display(Dictionary D){
    int i;
    for(i = 0; i < MAX; i++){
        LIST ptr;
        printf((D[i] != NULL) ? "%d: " : "", i);
        for(ptr = D[i]; ptr != NULL; ptr = ptr->next){
            printf("%d", ptr->data);
            if(ptr->next != NULL){
                printf("->");
            }
        }
        printf((D[i+1] != NULL) ? "\n" : "");
    }
}
