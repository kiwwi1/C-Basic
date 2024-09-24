#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 50

typedef struct Node {
    char name[MAX_LEN];
    float grade;
    struct Node* previous;
    struct Node* next;
} Node;

void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%s ", current->name);
        current = current->next;
    }
    printf("\n");
}

Node* createNode(char name[MAX_LEN], float grade) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    newNode->grade = grade;
    newNode->previous = NULL;
    newNode->next = NULL;
    return newNode;
}

Node* insertNode(Node* head, Node* newNode) {
    if (head == NULL) {
        return newNode;
    }

    Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = newNode;
    newNode->previous = current;
    return head;
}

Node* selectionSort(Node* head) {
    Node *i, *j, *min;

    for (i = head; i != NULL; i = i->next) {
        min = i;
        for (j = i->next; j != NULL; j = j->next) {
            if (strcmp(j->name, min->name) < 0) {
                min = j;
            }
        }

        // Swap data of min and i
        char tempName[MAX_LEN];
        strcpy(tempName, i->name);
        float tempGrade = i->grade;

        strcpy(i->name, min->name);
        i->grade = min->grade;

        strcpy(min->name, tempName);
        min->grade = tempGrade;
    }

    return head;
}

Node* insertionSort(Node* head) {
    Node *i, *key, *j;

    for (i = head->next; i != NULL; i = i->next) {
        key = i;
        j = i->previous;

        while (j != NULL && strcmp(j->name, key->name) > 0) {
            // Shift the elements greater than key to the right
            strcpy(j->next->name, j->name);
            j->next->grade = j->grade;
            j = j->previous;
        }

        // Insert the key in its correct position
        strcpy(j->next->name, key->name);
        j->next->grade = key->grade;
    }

    return head;
}

Node* bubbleSort(Node* head) {
    int swapped;
    Node *ptr1, *lptr = NULL;

    // Checking for empty list
    if (head == NULL) {
        return head;
    }

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (strcmp(ptr1->name, ptr1->next->name) > 0) {
                // Swap the data
                char tempName[MAX_LEN];
                strcpy(tempName, ptr1->name);
                float tempGrade = ptr1->grade;

                strcpy(ptr1->name, ptr1->next->name);
                ptr1->grade = ptr1->next->grade;

                strcpy(ptr1->next->name, tempName);
                ptr1->next->grade = tempGrade;

                swapped = 1;
            }

            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);

    return head;
}

int main() {
    Node* head = NULL;
    char name[MAX_LEN];
    float grade;

    // Nhập dữ liệu sinh viên
    while (1) {
        scanf("%s", name);
        if (strcmp(name, "#") == 0) {
            break;
        }
        scanf("%f", &grade);

        // Kiểm tra điểm hợp lệ (trong khoảng 0 đến 10)
        if (grade >= 0 && grade <= 10) {
            Node* newNode = createNode(name, grade);
            head = insertNode(head, newNode);
        }
    }

    // Chọn giải thuật sắp xếp
    char sortingAlgorithm[15];
    scanf("%s", sortingAlgorithm);

    // Sắp xếp và in ra từng bước lặp
    if (strcmp(sortingAlgorithm, "SelectionSort") == 0) {
        head = selectionSort(head);
    } else if (strcmp(sortingAlgorithm, "InsertionSort") == 0) {
        head = insertionSort(head);
    } else if (strcmp(sortingAlgorithm, "BubbleSort") == 0) {
        head = bubbleSort(head);
    } else {
        printf("Wrong Command\n");
        return 0;
    }

    // In ra từng bước lặp của giải thuật
    printList(head);

    // Giải phóng bộ nhớ
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
