//THAO TAC TREN CAY THUONG
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int id;
    struct Node* leftMostChild;
    struct Node* rightSibling;
} Node;

Node* root;

Node* makeNode(int id) {
    Node* p = (Node*)malloc(sizeof(Node));
    p->id = id;
    p->leftMostChild = NULL;
    p->rightSibling = NULL;
    return p;
}

Node* find(Node* r, int id) {
    if (r == NULL) return NULL;
    if (r->id == id) return r;
    Node* p = r->leftMostChild;
    while (p != NULL) {
        Node* q = find(p, id);
        if (q != NULL) return q;
        p = p->rightSibling;
    }
    return NULL;
}

Node* addLast(Node* p, int id) {
    if (p == NULL) return makeNode(id);
    p->rightSibling = addLast(p->rightSibling, id);
    return p;
}

void addChild(int parent_id, int child_id) {
    Node* r = find(root, parent_id);
    if (r == NULL) return;
    r->leftMostChild = addLast(r->leftMostChild, child_id);
}

void preOrder(Node* r) {
    if (r == NULL) return;
    printf("%d ", r->id); // visit the root r
    Node* p = r->leftMostChild;
    while (p != NULL) {
        preOrder(p);
        p = p->rightSibling;
    }
}

void inOrder(Node* r){
    if(r == NULL) return;
    Node* p = r->leftMostChild;// the first (left-most) child of r: r1
    inOrder(p);
    printf("%d ",r->id);
    if(p == NULL) return;
    p = p->rightSibling; // p = the second child of r: r2
    while(p != NULL){
        inOrder(p);
        p = p->rightSibling;
    }
}

void postOrder(Node* r){
    if(r == NULL) return;
    Node* p = r->leftMostChild;// start with the first (left-most) child of r
    while(p != NULL){
        postOrder(p);
        p = p->rightSibling;
    }
    printf("%d ",r->id);// lastly, visit the root r
}
int height(Node* r){
    int maxH = 0;
    if(r == NULL) return 0;
    for(Node* p = r->leftMostChild; p != NULL; p = p->rightSibling){
        int h = height(p);
        if(h > maxH) maxH = h;
    }
    return maxH + 1;
}

int countTree(Node* r){
    if(r == NULL) return 0;
    int count = 1;
    Node* q = r->leftMostChild;
    while(q != NULL){
        count += countTree(q);
        q = q->rightSibling;
    }
    return count;
}

int countChild(Node* r) {
    int count = 0;
    Node* p = r->leftMostChild;
    while (p != NULL) {
        count++;
        p = p->rightSibling;
    }  
    return count;
}

int countLeaves(Node* r){
    if(r == NULL) return 0;
    if(r->leftMostChild == NULL) return 1;
    int count = 0;
    Node* p = r->leftMostChild;
    while(p != NULL){
        count += countLeaves(p);
        p = p->rightSibling;
    }
    return count;
}

void freeTree(Node* r){
    if(r == NULL) return;
    Node* p = r->leftMostChild;
    while(p != NULL){
        Node* np = p->rightSibling;
        free(p);
        p = np;
    }
    free(r);
}
int main() {
    char action[20];
    int u, v;

    while (1) {
        scanf("%s",action);

        if (action[0] == '*')
            break;

        if (strcmp(action, "MakeRoot") == 0) {
            scanf(" %d", &u);
            root = makeNode(u);
        } else if (strcmp(action, "Insert") == 0) {
            scanf(" %d %d", &u, &v);
            addChild(v, u);
        } else if (strcmp(action, "PreOrder") == 0) {
            preOrder(root);
            printf("\n");
        } else if (strcmp(action, "InOrder") == 0) {
            inOrder(root);
            printf("\n");
        } else if (strcmp(action, "PostOrder") == 0) {
            postOrder(root);
            printf("\n");
        }
    }

    return 0;
}
