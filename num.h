#include<stdio.h>
#include<stdlib.h>
#include"list.h"

typedef struct node
{
    int data;
    struct node* next;
    struct node* prev;
}node;


typedef struct Big_N{
    int size;
    
    int sign; // 0 -> +ve   and   1 -> -ve

    node* head;
    node* tail;
}Big_N;

// to indicate error and exit from loop
extern int cont;

void init_num(Big_N *num);
void negation(Big_N *num);
void rem_lead_zeros(Big_N* num);
void destroy(Big_N* num);
void display(Big_N num);
void isnertInFront(Big_N* num, int val);
void insertInEnd(Big_N* num, int val );
int compare(Big_N a, Big_N b);
int length(Big_N num);


Big_N add(Big_N *a, Big_N *b);
Big_N sub(Big_N* a, Big_N* b);

Big_N  mult(Big_N* a, Big_N* b);
Big_N division(Big_N* l, Big_N* m);