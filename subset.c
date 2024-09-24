#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char id;
    struct Node* leftChild;
    struct Node* rightChild;
} Node;

Node* MakeRoot(char id) {
    Node* root = (Node*)malloc(sizeof(Node));
    root->id = id;
    root->leftChild = NULL;
    root->rightChild = NULL;
    return root;
}

void AddLeftChild(Node* parent, char id) {
    if (parent->leftChild == NULL) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->id = id;
        newNode->leftChild = NULL;
        newNode->rightChild = NULL;
        parent->leftChild = newNode;
    }
}

void AddRightChild(Node* parent, char id) {
    if (parent->rightChild == NULL) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->id = id;
        newNode->leftChild = NULL;
        newNode->rightChild = NULL;
        parent->rightChild = newNode;
    }
}

void PreOrder(Node* node) {
    if (node != NULL) {
        printf("%c ", node->id);
        PreOrder(node->leftChild);
        PreOrder(node->rightChild);
    }
}

void InOrder(Node* node) {
    if (node != NULL) {
        InOrder(node->leftChild);
        printf("%c ", node->id);
        InOrder(node->rightChild);
    }
}

void PostOrder(Node* node) {
    if (node != NULL) {
        PostOrder(node->leftChild);
        PostOrder(node->rightChild);
        printf("%c ", node->id);
    }
}

int main() {
    Node* root = NULL;
    char command[20];

    while (1) {
        scanf("%s", command);

        if (command[0] == '#') {
            break;
        }

        if (strcmp(command, "MakeRoot") == 0) {
            char id;
            scanf(" %c", &id);
            root = MakeRoot(id);
        } else if (strcmp(command, "AddLeftChild") == 0) {
            char u, v;
            scanf(" %c %c", &u, &v);

            Node* node = root;
            while (node != NULL && node->id != u) {
                if (u < node->id) {
                    node = node->leftChild;
                } else {
                    node = node->rightChild;
                }
            }

            if (node != NULL) {
                AddLeftChild(node, v);
            }
        } else if (strcmp(command, "AddRightChild") == 0) {
            char u, v;
            scanf(" %c %c", &u, &v);

            Node* node = root;
            while (node != NULL && node->id != u) {
                if (u < node->id) {
                    node = node->leftChild;
                } else {
                    node = node->rightChild;
                }
            }

            if (node != NULL) {
                AddRightChild(node, v);
            }
        } else if (strcmp(command, "PreOrder") == 0) {
            printf("PreOrder: ");
            PreOrder(root);
            printf("\n");
        } else if (strcmp(command, "InOrder") == 0) {
            printf("InOrder: ");
            InOrder(root);
            printf("\n");
        } else if (strcmp(command, "PostOrder") == 0) {
            printf("PostOrder: ");
            PostOrder(root);
            printf("\n");
        }
    }

    return 0;
}
