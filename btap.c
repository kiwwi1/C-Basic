#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for a BST node
struct Node {
    int key;
    struct Node *left, *right;
};

// Function to create a new BST node
struct Node *newNode(int key) {
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->key = key;
    temp->left = temp->right = NULL;
    return temp;
}

// Function to insert a key into the BST
struct Node *insert(struct Node *root, int key) {
    if (root == NULL)
        return newNode(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);

    return root;
}

// Function to perform pre-order traversal and print the result
void preorderTraversal(struct Node *root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// Function to check if a key exists in the BST
int keyExists(struct Node *root, int key) {
    if (root == NULL)
        return 0;

    if (key < root->key)
        return keyExists(root->left, key);
    else if (key > root->key)
        return keyExists(root->right, key);
    else
        return 1; // Key already exists
}

int main() {
    struct Node *root = NULL;

    char command[10];
    int key;

    while (1) {
        scanf("%s", command);

        if (command[0] == '#')
            break;

        if (strcmp(command, "insert") == 0) {
            scanf("%d", &key);
            if (!keyExists(root, key)) {
                root = insert(root, key);
            }
        }
    }

    preorderTraversal(root);

    return 0;
}
