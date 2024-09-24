#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 100

// Định nghĩa cấu trúc Node
typedef struct Node {
    int value;
    struct Node* next;
} Node;
Node *head=NULL;
// Hàm tạo một Node mới
Node* makeNode(int v) {
    Node *p=(Node*) malloc(sizeof(Node));
    p->value=v;
    p->next=NULL;
    return p;
}

// Hàm chèn một Node vào cuối danh sách
Node* insertLast(int v) {
    Node *p =head;
    if(head==NULL){
        return makeNode(v);
    }
    while(p->next != NULL){
        p=p->next;
    }
    Node *q=makeNode(v);
    p->next=q;
    return head;
}

// Hàm hiển thị danh sách
void printList() {
    Node* p = head;
    while (p != NULL) {
        printf("%d ", p->value);
        p = p->next;
    }
    printf("\n");
}

// Hàm xóa một node có giá trị v
Node* removeNode(int v){
    Node* p = head;

    // Trường hợp danh sách rỗng
    if(head == NULL) return NULL;

    // Trường hợp phần tử đầu danh sách có giá trị v
    if(head->value == v){
        Node* tmp = head; 
        head = head->next;      
        free(tmp);  
        return head;
    }

    // Trường hợp thông thường 
    while(p->next!=NULL){
        if(p->next->value==v) break;
        p=p->next;
    }
    if(p->next!=NULL){
        Node *q=p->next;
        p->next=q->next;
        free(q);
    }
    return head;
}

// Hàm xóa tất cả các node có giá trị v 
Node* removeAll(int v){
    // remove all nodes having value v from the linked list headed by head
    if(head == NULL) 
        return NULL;
     // Trường hợp phần tử đầu danh sách có giá trị v
    if(head->value == v){
        Node* tmp = head; 
        head = head->next; 
        free(tmp);
        head = removeAll(v); // continue to remove other elements having value v
        return head;
    }

    head->next = removeAll(v);
    return head;
}

// Hàm đếm số node trên danh sách
int count(){
    int count=0;
    Node *p=head;
    while(p->next!=NULL){
        count++;
        p=p->next;
    }
    return count;
}

// Hàm đảo ngược thứ tự các node trong danh sách
void reverse(){
    Node* p = head;
    Node* pp = NULL;
    Node* np = NULL;
    while(p != NULL){
        np = p->next;
        p->next = pp;
        pp = p;
        p = np;
    }
    head=pp;
}

int main() {
    char buff[MAX_LEN];
    int v; 
    
    // Đọc dãy số vào bộ đệm
    fgets(buff, MAX_LEN, stdin);

    // Sử dụng strtok() để tách xâu bằng dấu khoảng cách
    char *token = strtok(buff, " ");

    // Tạo list
    while (token != NULL) {
        head = insertLast(atoi(token)); // Lấy số hiện tại
        token = strtok(NULL, " "); // Lấy số tiếp theo
    }

    // Hiển thị danh sách
    printf("Dãy số vừa nhập là:\n");
    printList();

    // Nhập giá trị muốn xoá
    //printf("Nhập giá trị muốn xóa khởi danh sách: ");
    //scanf("%d", &v);

    // Xóa phần tử có giá trị v
    removeNode(1);

    // Xoá hết các phần tử có giá trị v
    //head = removeAll(head, v);

    //printf("Dãy số sau khi xóa là:\n");
    //printList(head);

   reverse();

    printf("Dãy số sau khi đảo ngược là:\n");
    printList();

    // Giải phóng bộ nhớ sau khi sử dụng
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}


