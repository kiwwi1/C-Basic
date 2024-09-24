#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* prev;
    struct Node* next;
} Node;

Node* head;
Node* tail;

// Function to create a new node
Node* makeNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Error: Unable to allocate memory for a new node.\n");
        exit(1);
    }
    newNode->value = v;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to initialize the queue
void initQueue() {
    head = NULL;
    tail = NULL;
}

// Function to check if the queue is empty
int queueEmpty() {
    return head == NULL && tail == NULL;
}

// Function to add a new node to the front of the queue
void pushQueue(int v) {
    Node* p = makeNode(v);
    if (queueEmpty()) {
        head = p;
        tail = p;
    } else {
        p->next = head;
        head->prev = p;
        head = p;
    }
}

// Function to remove and return the last element from the queue
int popQueue() {
    if (queueEmpty()) {
        fprintf(stderr, "Error: Queue is empty.\n");
        exit(1);
    }
    int v = tail->value;
    Node* tmp = tail;
    tail = tail->prev;
    if (tail != NULL) {
        tail->next = NULL;
    } else {
        head = NULL;
    }
    free(tmp);
    return v;
}

// Function to split a double into integer and fractional parts
void splitDouble(double soThuc, int* phanNguyen, double* phanThapPhan) {
    *phanNguyen = (int)soThuc;
    *phanThapPhan = soThuc - *phanNguyen;
}

int main(void) {
    int phanNguyen=5;
    double phanThapPhan;

    // Receive the fractional part from the user
    // printf("Enter a decimal fraction: ");
    scanf("%lf", &phanThapPhan);

    // Initialize the queue
    initQueue();

    // Push the integer part of the multiplication into the queue
    do {
        splitDouble(phanThapPhan * 2, &phanNguyen, &phanThapPhan);
        pushQueue(phanNguyen);
    } while (phanThapPhan != 0);

    // Display the binary representation
    // printf("Binary representation: ");
    printf("0.");
    while (!queueEmpty()) {
        printf("%d", popQueue());
    }
    printf("\n");

    return 0;
}