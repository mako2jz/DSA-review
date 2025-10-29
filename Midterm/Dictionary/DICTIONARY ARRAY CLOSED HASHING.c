#include<stdio.h>
#include<stdbool.h>
#define MAX 10

// cell states
typedef enum {
    EMPTY = -1,
    DELETED = -2
} Status;

// datatype
typedef char Dictionary[MAX];

// user defined functions
void initDict(Dictionary D);
int hash(char data);
void insert(Dictionary D, char data);
void delete(Dictionary D, char data);
bool member(Dictionary D, char data);
void display(Dictionary D);

int main(){
    Dictionary D;

    initDict(D);
    
    printf("Set A: {a, b, c, d, e, f}:\n");
    insert(D, 'a');
    insert(D, 'b');
    insert(D, 'c');
    insert(D, 'd');
    insert(D, 'e');
    display(D);

    printf("\n%c %s a member of Set A", 'a', member(D, 'a') ? "is" : "is not");

    printf("\n\nDeleting a and e:\n");
    delete(D, 'a');
    delete(D, 'e');
    display(D);

    printf("\n%c %s a member of Set A", 'a', member(D, 'a') ? "is" : "is not");
    printf("\n%c %s a member of Set A", 'b', member(D, 'b') ? "is" : "is not");
    printf("\n%c %s a member of Set A\n\n", 'e', member(D, 'e') ? "is" : "is not");

    insert(D, 'f');
    insert(D, 'g');
    insert(D, 'j');
    insert(D, 'h');
    insert(D, 'i');
    insert(D, 'k');
    display(D);

    return 0;
}

void initDict(Dictionary D){
    int i;
    for(i = 0; i < MAX; i++){
        D[i] = EMPTY;
    }
}

int hash(char data) {
    switch (data) {
        case 'a': return 3;
        case 'b': return 9;
        case 'c': return 4;
        case 'd': return 3;
        case 'e': return 9;
        case 'f': return 0;
        case 'g': return 1;
        case 'j': return 3;
        case 'h': return 7;
        case 'i': return 8;
        case 'k': return 3;
        default:  return -1;
    }
}

void insert(Dictionary D, char data){
    int start = hash(data);
    int stop = (start + MAX - 1) % MAX;
    int firstAvailable = -1;
    int i;
    for(i = start; i != stop && D[i] != EMPTY && D[i] != data; i = (i + 1) % MAX){
        if(firstAvailable == -1 && D[i] == DELETED){
            firstAvailable = i;
        }
    }
    if(D[i] == EMPTY || (i == stop && firstAvailable != -1)){
        D[(i == stop && firstAvailable != -1) ? firstAvailable : i] = data;
    }
}

void delete(Dictionary D, char data){
    int start = hash(data);
    int stop = (start - MAX + 1) % MAX;
    int i;
    for(i = start; i != stop && D[start] != EMPTY && data != D[i]; i = (i + 1) % MAX){}
    if(D[i] == data){
        D[i] = DELETED;
    }
}

bool member(Dictionary D, char data){
    int start = hash(data);
    int stop = (start + MAX - 1) % MAX;
    int i;
    for(i = start; i != stop && D[start] != EMPTY && D[i] != data; i = (i + 1) % MAX){}
    return (D[i] == data) ? true : false;
}

void display(Dictionary D){
    int i;
    for(i = 0; i < MAX; i++){
        printf("%d: ", i);
        printf((D[i] >= 0) ? "%c\n" : (D[i] == -1) ? "EMPTY\n" : "DELETED\n", D[i]);
    }
}