#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node{
    int value;
    struct Node* next;
}Node;

Node* top=NULL;

Node* makeNode(int v){
    Node* p = (Node*)malloc(sizeof(Node));
    p->value = v; 
    p->next = NULL;
    return p;
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

// Function to check if each '2' has a corresponding '1' before it in pairs
bool check(int *ngoac,int n){
    for(int i=0;i<n;i++){
        if(ngoac[i]==1){
            push(ngoac[i]);
        }
        else if(ngoac[i]==2){
            if(stackEmpty) return false;
            int topE=pop();
            if(topE!=1){
                return false;
            }
        }
    }
    return stackEmpty();
}
// Function to print all combinations of '(' and ')' for a given expression
void generateCombinations(int *expression, int index, int openCount, int closeCount, int n) {
    if (index == n) {
        // Check if the parentheses are balanced and meet the additional condition
        if (check(expression,n)) {
            for (int i = 0; i < n; i++) {
                printf("%d", expression[i]);
            }
            printf(" ");
        }
        return;
    }

    if (expression[index] == 0) {
        // Choose '(' for '0'
        expression[index] = 1;
        generateCombinations(expression, index + 1, openCount + 1, closeCount, n);
        expression[index] = 0;  // Reset for backtracking

        // Choose ')' for '0'
        expression[index] = 2;
        generateCombinations(expression, index + 1, openCount, closeCount + 1, n);
        expression[index] = 0;  // Reset for backtracking
    } else if (expression[index] == 1) {
        generateCombinations(expression, index + 1, openCount + 1, closeCount, n);
    } else if (expression[index] == 2) {
        generateCombinations(expression, index + 1, openCount, closeCount + 1, n);
    } else {
        generateCombinations(expression, index + 1, openCount, closeCount, n);
    }
}

int main() {
    int n;

    scanf("%d", &n);

    int expression[n];
   
    for (int i = 0; i < n; i++) {
        scanf("%d", &expression[i]);
    }

    generateCombinations(expression, 0, 0, 0, n);

    return 0;
}
