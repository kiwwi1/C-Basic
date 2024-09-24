
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node{
int key;
struct Node* left;
struct Node* right;
}Node;

// Create a Node
Node *newNode(int item) {
 Node *temp = (Node*)malloc(sizeof(Node));
  temp->key = item;
  temp->left = temp->right = NULL;
  return temp;
}
Node* search(Node* r, int v) {
if(r == NULL){
     printf("%d not found", v);
     return NULL;
}
else if (r->key == v) {
        printf("found %d", v);
        return r;
    } else if (v < r->key) {
        return search(r->left, v);
    } else {
        return search(r->right, v);
    }
}

// Inorder Traversal
void inorder(Node *root) {
  if (root != NULL) {
    // Traverse left
    inorder(root->left);

    // Traverse root
    printf("%d ", root->key);

    // Traverse right
    inorder(root->right);
  }
}
void preorder(Node *root) {
  if (root != NULL) {
     // Traverse root
    printf("%d ", root->key);
    // Traverse left
    preorder(root->left);
    // Traverse right
    preorder(root->right);
  }
}
Node* insert(Node* r, int v) {
if(r == NULL)
r = newNode(v);
else if(r->key > v)
r->left = insert(r->left,v);
else if(r->key <= v)
r->right = insert(r->right,v);
return r;
}

Node* findMin(Node* root) {
    if (root == NULL) {
        printf("Tree is empty");
        return NULL;
    }

    Node* current = root;
    while (current->left != NULL) {
        current = current->left;
    }

    printf("Min is %d", current->key);
    return current;
}
Node* findMax(Node* root) {
    if (root == NULL) {
        printf("Tree is empty");
        return NULL;
    }

    Node* current = root;
    while (current->right != NULL) {
        current = current->right;
    }

    printf("Max is %d\n", current->key);
    return current;
}
// Find the inorder successor
 Node *minValueNode(Node *u) {
   Node* current = u;

  // Find the leftmost leaf
  while (current && current->left != NULL)
    current = current->left;

  return current;
}

// Deleting a Node
 Node *deleteNode( Node *root, int key) {
  // Return if the tree is empty
  if (root == NULL) return root;

  // Find the Node to be deleted
  if (key < root->key)
    root->left = deleteNode(root->left, key);
  else if (key > root->key)
    root->right = deleteNode(root->right, key);

  else {
    // If the Node is with only one child or no child
    if (root->left == NULL) {
      Node *temp = root->right;
      free(root);
      return temp;
    } else if (root->right == NULL) {
       Node *temp = root->left;
      free(root);
      return temp;
    }

    // If the Node has two children
    Node *temp = minValueNode(root->right);

    // Place the inorder successor in position of the Node to be deleted
    root->key = temp->key;

    // Delete the inorder successor
    root->right = deleteNode(root->right, temp->key);
  }
  return root;
}
int treeHeight(Node* root) {
    if (root == NULL) {
        return 0;
    } else {
        int leftHeight = treeHeight(root->left);
        int rightHeight = treeHeight(root->right);
        return (leftHeight > rightHeight) ? (leftHeight + 1) : (rightHeight + 1);
    }
}
void displayTreeHeight(Node* root) {
    int height = treeHeight(root);
    if (height == 0) {
        printf("Tree is empty\n");
    } else {
        printf("%d\n", height);
    }
}
int depthOfNode(Node* root, int u, int depth) {
    if (root == NULL) {
        return -1; // Node không tồn tại
    } else if (root->key == u) {
        return depth;
    } else {
        int leftDepth = depthOfNode(root->left, u, depth + 1);
        int rightDepth = depthOfNode(root->right, u, depth + 1);
        if (leftDepth != -1) {
            return leftDepth;
        } else {
            return rightDepth;
        }
    }
}
void freeTree(Node *root) {
    if (root != NULL) {
        // Giải phóng cây con bên trái và bên phải trước
        freeTree(root->left);
        freeTree(root->right);

        // Giải phóng nút hiện tại
        free(root);
    }
}

// Driver code
int main() {
Node *root = NULL;
  char lenh[20];
  int k;
  while(1){
    scanf("%s",lenh);
    if(strcmp(lenh,"#")==0){
        break;
    }
    else if(strcmp(lenh,"Insert")==0){
        scanf(" %d",&k);
        root = insert(root,k);
    }
    else if(strcmp(lenh,"Delete")==0){
        scanf(" %d",&k);
        root = deleteNode(root,k);
    }
    else if(strcmp(lenh,"Search")==0){
        scanf(" %d",&k);
        search(root,k);
        printf("\n");
    }
    else if(strcmp(lenh,"FindMin")==0){
        findMin(root);
        printf("\n");
    }
    else if(strcmp(lenh,"FindMax")==0){
        findMax(root);
    }
    else if(strcmp(lenh,"PrintTree")==0){
        inorder(root);
        printf("\n");
    }
    else if(strcmp(lenh,"TreeHeight")==0){
        displayTreeHeight(root);
    }
    else if(strcmp(lenh,"Depth")==0){
        scanf(" %d",&k);
         int depth = depthOfNode(root, k, 0);
    if (depth != -1) {
        printf("%d\n",depth);
    } else {
        printf("%d not found\n", k);
    }
    }
  }
 freeTree(root);
}
