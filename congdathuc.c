#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Định nghĩa cấu trúc Node
typedef struct Node {
    int coefficient;
    int exponent;
    struct Node* next;
} Node;

// Hàm tạo một Node mới
Node* makeNode(int coeff, int expo) {
    Node* p = (Node*)malloc(sizeof(Node));
    p->coefficient = coeff;
    p->exponent = expo;
    p->next = NULL;
    return p;
}

// Hàm thêm một Node vào cuối danh sách
Node* addLast(Node* head, int coeff, int expo) {
    Node* p = head;
    if (head == NULL) {
        return makeNode(coeff, expo);
    }
    while (p->next != NULL) {
        p = p->next;
    }
    Node* q = makeNode(coeff, expo);
    p->next = q;
    return head;
}

// Hàm tính tổng hai đa thức
Node* addPolynomials(Node* p, Node* q) {
    Node* result = NULL;
    while (p != NULL || q != NULL) {
        int coeff = 0, expo = 0;
        if (p != NULL && q != NULL) {
            if (p->exponent == q->exponent) {
                coeff = p->coefficient + q->coefficient;
                expo = p->exponent;
                p = p->next;
                q = q->next;
            } else if (p->exponent > q->exponent) {
                coeff = p->coefficient;
                expo = p->exponent;
                p = p->next;
            } else {
                coeff = q->coefficient;
                expo = q->exponent;
                q = q->next;
            }
        } else if (p != NULL) {
            coeff = p->coefficient;
            expo = p->exponent;
            p = p->next;
        } else {
            coeff = q->coefficient;
            expo = q->exponent;
            q = q->next;
        }
        result = addLast(result, coeff, expo);
    }
    return result;
}

// Hàm tính hiệu hai đa thức
Node* subtractPolynomials(Node* p, Node* q) {
    Node* result = NULL;
    while (p != NULL || q != NULL) {
        int coeff = 0, expo = 0;
        if (p != NULL && q != NULL) {
            if (p->exponent == q->exponent) {
                coeff = p->coefficient - q->coefficient;
                expo = p->exponent;
                p = p->next;
                q = q->next;
            } else if (p->exponent > q->exponent) {
                coeff = p->coefficient;
                expo = p->exponent;
                p = p->next;
            } else {
                coeff = -q->coefficient;
                expo = q->exponent;
                q = q->next;
            }
        } else if (p != NULL) {
            coeff = p->coefficient;
            expo = p->exponent;
            p = p->next;
        } else {
            coeff = -q->coefficient;
            expo = q->exponent;
            q = q->next;
        }
        result = addLast(result, coeff, expo);
    }
    return result;
}

// Hàm hiển thị danh sách
void printList(Node* head) {
    Node* p = head;
    while (p != NULL) {
        printf("%d ", p->coefficient);
        p = p->next;
    }
    printf("\n");
}

int main() {
    int n, m;
    int coeff;
    Node* polyP = NULL;
    Node* polyQ = NULL;

    // Nhập đa thức P
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &coeff);
        polyP = addLast(polyP, coeff, i);
    }

    // Nhập đa thức Q
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &coeff);
        polyQ = addLast(polyQ, coeff, i);
    }

    // Lựa chọn phép toán: plus hoặc minus
    char operation[10];
    scanf("%s", operation);

    Node* result = NULL;

    // Thực hiện phép toán
    if (strcmp(operation, "plus") == 0) {
        result = addPolynomials(polyP, polyQ);
    } else if (strcmp(operation, "minus") == 0) {
        result = subtractPolynomials(polyP, polyQ);
    }

    // Hiển thị kết quả
    int nodeCount = 0;
    Node* p = result;
    while (p != NULL) {
        if(p->coefficient!=0) nodeCount++;
        p = p->next;
    }
    Node *q= result;
    int sum=0;
    while(q->next!=NULL)
    {
        sum+=q->coefficient;
q=q->next;
    }
    if(sum==0) printf("1 0");
    else{
        printf("%d ", nodeCount);
    printList(result);
}
}
