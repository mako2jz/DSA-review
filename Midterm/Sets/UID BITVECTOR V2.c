#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAX 10

// datatype
typedef int SET[MAX];

// user defined functions
void INIT(SET A);
void INSERT(SET A, int data);
void DELETE(SET A, int data);
bool MEMBER(SET A, int data);
void UNION(SET A, SET B, SET C);
void INTERSECTION(SET A, SET B, SET C);
void DIFFERENCE(SET A, SET B, SET C);
void display(SET A);

int main() {
    SET A, B;
    
    INIT(A);
    INIT(B);
    
    INSERT(A, 1);
    INSERT(A, 0);
    INSERT(A, 5);
    INSERT(A, 7);
    
    INSERT(B, 0);
    INSERT(B, 4);
    INSERT(B, 5);
    
    printf("SET A: ");
    display(A);
    printf("SET B: ");
    display(B);

    SET C;
    printf("A u B: ");
    UNION(A, B, C);
    display(C);
    printf("A n B: ");
    INTERSECTION(A, B, C);
    display(C);
    printf("A \\ B: ");
    DIFFERENCE(A, B, C);
    display(C);
    printf("B \\ A: ");
    DIFFERENCE(B, A, C);
    display(C);

    printf("\n%d %s a member of SET A\n", 1, (MEMBER(A, 1)) ? "is" : "is not");
    printf("%d %s a member of SET A\n", 4, (MEMBER(A, 4)) ? "is" : "is not");
    printf("%d %s a member of SET B\n", 1, (MEMBER(B, 1)) ? "is" : "is not");
    printf("%d %s a member of SET B\n", 4, (MEMBER(B, 4)) ? "is" : "is not");
    
    printf("\nDeleting 1 from SET A: ");
    DELETE(A, 1);
    display(A);

    return 0;
}

void INIT(SET A){
    int x;
    for(x = 0; x < MAX; x++){
        A[x] = 0;
    }
}

void INSERT(SET A, int data){
    A[data] |= 1;
}

void DELETE(SET A, int data){
    A[data] &= 0;
}

bool MEMBER(SET A, int data){
    return (A[data] & 1) ? 1 : 0;
}

void UNION(SET A, SET B, SET C){
    int x;
    for(x = 0; x < MAX; x++){
        C[x] = A[x] | B[x];
    }
}

void INTERSECTION(SET A, SET B, SET C){
    int x;
    for(x = 0; x < MAX; x++){
        C[x] = A[x] & B[x];
    }
}

void DIFFERENCE(SET A, SET B, SET C){
    int x;
    for(x = 0; x < MAX; x++){
        C[x] = A[x] & ~(B[x]);
    }
}

void display(SET A){
    int x;
    printf("{");
    for(x = 0; x < MAX; x++){
        if(A[x] != 0){
            printf("%d, ", x);
        }
    }
    printf("}\n");
}