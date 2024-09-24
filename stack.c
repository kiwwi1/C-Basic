#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    int value;
    struct Node* next;
}Node;

Node* top;

Node* makeNode(int v){
    Node* p = (Node*)malloc(sizeof(Node));
    p->value = v; 
    p->next = NULL;
    return p;
}

void initStack(){
    top = NULL;
}

int stackEmpty(){
    return top == NULL;
}

void push(int v){
    Node* p = makeNode(v);
    p->next = top; 
    top = p;
}

int pop(){
    if(stackEmpty()) return -1;
    int v = top->value;
    Node* tmp = top;
    top = top->next; 
    free(tmp);
    return v;
}

void finalize(){
    Node* current = top;
    while(current != NULL){
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    top = NULL;
}

int main(void){
    int decimal;

    //Nhận một số nguyên từ bàn phím
    scanf("%d", &decimal);

    //Khởi tạo stack
    initStack();

    //Push remainder to stack
    while(decimal != 0){
        push(decimal % 2);
        decimal = decimal / 2;
    }

    //Show the binary number
    while(top != NULL){
        printf("%d", pop());
    }

    printf("\n");
    return 0;
}


