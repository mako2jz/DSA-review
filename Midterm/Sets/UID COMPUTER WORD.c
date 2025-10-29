#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAX (sizeof(char) * 8)

// datatype
typedef char SET;

// user defined functions
void INIT(SET *A);
void INSERT(SET *A, int data);
void DELETE(SET *A, int data);
bool MEMBER(SET A, int data);
SET UNION(SET A, SET B);
SET INTERSECTION(SET A, SET B);
SET DIFFERENCE(SET A, SET B);
void display(SET A);

int main() {
    SET A, B;
    
    INIT(&A);
    INIT(&B);
    
    INSERT(&A, 1);
    INSERT(&A, 0);
    INSERT(&A, 5);
    INSERT(&A, 7);
    
    INSERT(&B, 0);
    INSERT(&B, 4);
    INSERT(&B, 5);
    
    printf("SET A: ");
    display(A);
    printf("SET B: ");
    display(B);

    printf("A u B: ");
    display(UNION(A, B));
    printf("A n B: ");
    display(INTERSECTION(A, B));
    printf("A \\ B: ");
    display(DIFFERENCE(A, B));
    printf("B \\ A: ");
    display(DIFFERENCE(B, A));
    
    printf("\n%d %s a member of SET A\n", 1, (MEMBER(A, 1)) ? "is" : "is not");
    printf("%d %s a member of SET A\n", 4, (MEMBER(A, 4)) ? "is" : "is not");
    printf("%d %s a member of SET B\n", 1, (MEMBER(B, 1)) ? "is" : "is not");
    printf("%d %s a member of SET B\n", 4, (MEMBER(B, 4)) ? "is" : "is not");
    
    printf("\nDeleting 1 from SET A: ");
    DELETE(&A, 1);
    display(A);

    return 0;
}
    
void INIT(SET *A){
    *A = 0;
}

void INSERT(SET *A, int data){
    *A |= 1 << data;
}

void DELETE(SET *A, int data){
    *A &= ~(1 << data);
}

bool MEMBER(SET A, int data){
    return (A >> data & 1) ? true : false;
}

SET UNION(SET A, SET B){
    return A | B;    
}

SET INTERSECTION(SET A, SET B){
    return A & B;
}

SET DIFFERENCE(SET A, SET B){
    return A & ~(B);
}

void display(SET A){
    int i;
    printf("{");
    for(i = 0; i < MAX; i++){
        if(A >> i & 1 != 0){
            printf("%d", i);
            if(A >> i + 1 != 0 && i + 1 < MAX - 1){
                printf(", ");
            }
        }
    }
    printf("}\n");
}