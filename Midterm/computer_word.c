#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#define MAX (sizeof(char) * 8)

typedef unsigned char SET;

void initSet(SET *A);
void insert(SET *A, int data);
void display(SET A, SET B, char operation);
void displaySet(SET A);
bool member(SET A, int elem);
void delete(SET *A, int index);
SET UNION(SET A, SET B);
SET INTERSECTION(SET A, SET B);
SET DIFFERENCE(SET A, SET B);

int main(){
	SET A;
	SET B;
	initSet(&A);
	initSet(&B);
	insert(&A, 0);
	insert(&A, 4);
	insert(&A, 6);
	insert(&A, 7);
	insert(&B, 1);
	insert(&B, 4);
	insert(&B, 5);
	insert(&B, 6);
	display(A, B, 'S');
	display(A, B, 'U');
	display(A, B, 'I');
	display(A, B, '1');
	display(A, B, '2');
	display(A, B, '3');
	display(A, B, '4');
}

void initSet(SET *A){
	*A = '\0';
}

void insert(SET *A, int data){
	if(data < MAX){
		*A |= 1 << data;
	}
}

void display(SET A, SET B, char operation){
    switch(operation){
        case 'S': printf("A = "); displaySet(A); printf("B = "); displaySet(B); break;
        case 'U': printf("A | B = "); displaySet(UNION(A, B)); break;
        case 'I': printf("A & B = "); displaySet(INTERSECTION(A, B)); break;
        case '1': printf("A \\ B = "); displaySet(DIFFERENCE(A, B)); break;
        case '2': printf("B \\ A = "); displaySet(DIFFERENCE(B, A)); break;
        case '3': printf((member(A, 4)) ? "%d is a member of A\n" : "%d is not a member of A\n", 4); break;
        case '4': printf((member(B, 2)) ? "%d is a member of B\n" : "%d is not a member of B\n", 2); break;
    }
}

void displaySet(SET A){
	int mask;
	printf("{");
	for(mask = 0; mask < MAX; mask++){
	    if(A >> mask & 1 != 0){
	        printf("%d", mask);
	        if(A >> mask + 1 != 0){
	            printf(", ");
	        }
	    }
	}
	printf("}");
	printf("\n");
}

bool member(SET A, int elem){
	return (A >> elem & 1) ? true : false;
}

void delete(SET *A, int data){
	*A &= ~(1 << data);
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