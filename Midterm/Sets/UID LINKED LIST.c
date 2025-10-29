#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

// datatype
typedef struct node{
    int data;
    struct node *next;
}*SET;

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
    
    SET C;
    
    printf("A u B: ");
    C = UNION(A, B);
    display(C);
    
    printf("A n B: ");
    C = INTERSECTION(A, B);
    display(C);
    
    printf("A \\ B: ");
    C = DIFFERENCE(A, B);
    display(C);
    
    printf("B \\ A: ");
    C = DIFFERENCE(B, A);
    display(C);
    
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
    *A = NULL;
}

void INSERT(SET *A, int data){
    SET temp = (SET)malloc(sizeof(struct node));
    if(temp != NULL){
        SET *ptr;
        temp->data = data;
        for(ptr = A; *ptr != NULL && data > (*ptr)->data; ptr = &(*ptr)->next){}
        temp->next = *ptr;
        *ptr = temp;
    }
}

void DELETE(SET *A, int data){
    SET *ptr;
    for(ptr = A; *ptr != NULL && (*ptr)->data != data; ptr = &(*ptr)->next){}
    if(*ptr != NULL){
        SET temp = *ptr;
        *ptr = temp->next;
        free(temp);
    }
}

bool MEMBER(SET A, int data){
    SET ptr;
    bool result = false;
    for(ptr = A; ptr != NULL && ptr->data != data; ptr = ptr->next){}
    if(ptr != NULL){
        result = true;
    }
    return result;
}

/*
STEPS FOR SET UNION:
1. make SET C, apointer, bpointer, and *cpointer (PPN) // *cpointer (PPN) because we will be inserting / creating a new list.
2. loop (while a and b are not null) structure is:
    a. *cptr makes new node
    b. if a data < b data: copy to cptr and move aptr
    c. if b data < a data: copy to cptr and move bptr
    d. else, copy a data into cptr and move both aptr and bptr
    e. move cptr
3. after loop, check if either aptr or bptr are null and reuse aptr => aptr = (aptr == NULL) ? B : A;
4. copy rest of aptr into cptr
5. return C
*/
SET UNION(SET A, SET B){
    SET C, aptr, bptr, *cptr;
    aptr = A;
    bptr = B;
    cptr = &C;
    while(aptr != NULL && bptr != NULL){
        *cptr = (SET)malloc(sizeof(struct node));
        if(aptr->data < bptr->data){
            (*cptr)->data = aptr->data;
            aptr = aptr->next;
        } else if(bptr->data < aptr->data){
            (*cptr)->data = bptr->data;
            bptr = bptr->next;
        } else {
            (*cptr)->data = aptr->data;
            aptr = aptr->next;
            bptr = bptr->next;
        }
        cptr = &(*cptr)->next;
    }
    aptr = (aptr == NULL) ? bptr : aptr;
    while(aptr != NULL){
        *cptr = (SET)malloc(sizeof(struct node));
        (*cptr)->data = aptr->data;
        aptr = aptr->next;
        cptr = &(*cptr)->next;
    }
    return C;
}

/*
STEPS FOR SET INTERSECTION:
1. make SET C, apointer, bpointer, *cpointer (PPN), int count1 and count2 // *cpointer (PPN) because we will be inserting / creating a new list.
2. make 2 loops to determine which set is longer
3. assign aptr to longer set => aptr = (count1 > count2) ? A : B;
4. loop while(aptr is not NULL)
    a. forloop(bptr = (count1 > count2) ? B : A; bptr not NULL and b data != a data; move bptr)
    b. if(bptr is NULL): *cptr makes a new node, copy aptr data into *cptr, move cptr
    c. move aptr
5. return C
*/
SET INTERSECTION(SET A, SET B){
    SET C, aptr, bptr, *cptr;
    cptr = &C;
    int count1, count2;
    for(aptr = A, count1 = 0; aptr != NULL; aptr = aptr->next, count1++);
    for(bptr = B, count2 = 0; bptr != NULL; bptr = bptr->next, count2++);
    aptr = (count1 > count2) ? A : B;
    while(aptr != NULL){
        for(bptr = (count1 > count2) ? B : A; bptr != NULL && aptr->data != bptr->data; bptr = bptr->next){}
        if(bptr != NULL){
            *cptr = (SET)malloc(sizeof(struct node));
            (*cptr)->data = aptr->data;
            bptr = bptr->next;
            cptr = &(*cptr)->next;
        }
        aptr = aptr->next;
    }
    return C;
}

/*
1. make SET C, apointer, bpointer, *cpointer (PPN), int count1 and count2 // *cpointer (PPN) because we will be inserting / creating a new list.
2. loop while(aptr is not NULL)
    a. loop for(bptr = B; bptr is not NULL and b data != a data; move bptr)
    b. if bptr is NULL: *cptr makes new node, copies a data into c and move cptr
    c. move aptr
3. return C
*/
SET DIFFERENCE(SET A, SET B){
    SET C, aptr, bptr, *cptr;
    cptr = &C;
    aptr = A;
    while(aptr != NULL){
        for(bptr = B; bptr != NULL && bptr->data != aptr->data; bptr = bptr->next){}
        if(bptr == NULL){
            *cptr = (SET)malloc(sizeof(struct node));
            (*cptr)->data = aptr->data;
            cptr = &(*cptr)->next;
        }
        aptr = aptr->next;
    }
    return C;
}

void display(SET A){
    printf("{");
    SET ptr;
    for(ptr = A; ptr != NULL; ptr = ptr->next){
        printf("%d", ptr->data);
        if(ptr->next != NULL){
            printf(", ");
        }
    }
    printf("}\n");
}