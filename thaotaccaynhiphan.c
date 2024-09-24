#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Node{
int id;
struct Node* leftChild;
struct Node* rightChild;
}Node;
Node* root=NULL;

Node* makeNode(int id){
    Node* p = (Node*)malloc(sizeof(Node));
    p->id = id;
    p->leftChild = NULL; 
    p->rightChild = NULL;
    return p;
}

Node* find(Node* r, int id){
    if(r == NULL) return NULL;
    if(r->id == id) return r;
    Node* p = find(r->leftChild,id);
    if(p != NULL) return p;
    return find(r->rightChild,id);
}
void addLeftChild(int u, int left){
     Node* pu = find(root,u);
     if(pu == NULL){
     //printf("Not found %d\n",u); 
     return;
}
     if(pu->leftChild != NULL){
     //printf("Node %d has already leftChild\n",u); 
     return;
}
     pu->leftChild = makeNode(left);
}
void addRightChild(int u, int right){
     Node* pu = find(root,u);
     if(pu == NULL){
     //printf("Not found %d\n",u); 
     return;
}
     if(pu->rightChild != NULL){
     //printf("Node %d has already rightChild\n",u); 
     return;
}
     pu->rightChild = makeNode(right);
}
void PreOrder(Node* root) {
    if (root) {
        printf("%d ", root->id);
        PreOrder(root->leftChild);
        PreOrder(root->rightChild);
    }
}

void InOrder(Node* root) {
    if (root) {
        InOrder(root->leftChild);
        printf("%d ", root->id);
        InOrder(root->rightChild);
    }
}

void PostOrder(Node* root) {
    if (root) {
        PostOrder(root->leftChild);
        PostOrder(root->rightChild);
        printf("%d ", root->id);
    }
}

void IsPerfect(int k) {
    Node *u=makeNode(k);
    if (!u) {

        return false;
    }
    if (!u->leftChild && !u->rightChild) {
        return true;
    }
    if (u->leftChild && u->rightChild) {
        return IsPerfect(u->leftChild) && IsPerfect(u->rightChild);
    }
    return false;
}

bool IsFull(int k) {
    Node *u=makeNode(k);
    if (!u) {
        return true;
    }
    if (!u->leftChild && !u->rightChild) {
        return true;
    }
    if (u->leftChild && u->rightChild) {
        return IsFull(u->leftChild) && IsFull(u->rightChild);
    }
    return false;
}

bool isCompleteBinaryTreeFromNode(int position) {
    // Trường hợp cơ bản: cây rỗng là cây nhị phân hoàn chỉnh
    if (root == NULL) {
        return true;
    }

    // Sử dụng hàng đợi để duyệt cây theo cấp
    std::queue<Node*> q;
    q.push(root);

    int currentPos = 0;
    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        // Kiểm tra xem node hiện tại có nằm ở vị trí cần kiểm tra hay không
        if (currentPos == position) {
            // Nếu là lá trái, không có nút nào phải theo
            if (current->left == NULL && current->right != NULL) {
                return false;
            }

            // Duyệt qua tất cả các nút còn lại ở cùng mức
            while (!q.empty()) {
                current = q.front();
                q.pop();

                if (current->left != NULL || current->right != NULL) {
                    return false;
                }
            }

            return true;
        }

        // Đưa các con của node hiện tại vào hàng đợi
        if (current->left != NULL) {
            q.push(current->left);
        }
        if (current->right != NULL) {
            q.push(current->right);
        }

        // Tăng vị trí hiện tại
        currentPos++;
    }

    // Nếu đến đây mà không tìm thấy vị trí cần kiểm tra
    return false;
}


int maxDepth(Node* root) {
    if (!root) {
        return 0;
    }
    int leftDepth = maxDepth(root->leftChild);
    int rightDepth = maxDepth(root->rightChild);
    return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
}

bool IsBalanced(int k) {
    Node *u=makeNode(k);
    if (!u) {
        return true;
    }
    int leftDepth = maxDepth(u->leftChild);
    int rightDepth = maxDepth(u->rightChild);
    return (abs(leftDepth - rightDepth) <= 1) && IsBalanced(u->leftChild) && IsBalanced(u->rightChild);
}

int main() {
    char lenh[20];
    int id1, id2;
    while (1) {
        scanf("%s", lenh);
        if (strcmp(lenh, "MakeRoot") == 0) {
            scanf(" %d", &id1);
            root = makeNode(id1);
        } else if (strcmp(lenh, "AddLeft") == 0) {
            scanf(" %d %d", &id1, &id2);
            addLeftChild(id2, id1);
        } else if (strcmp(lenh, "AddRight") == 0) {
            scanf(" %d %d", &id1, &id2);
            addRightChild(id2, id1);
        } else if (strcmp(lenh, "PreOrder") == 0) {
            PreOrder(root);
            printf("\n");
        } else if (strcmp(lenh, "InOrder") == 0) {
            InOrder(root);
            printf("\n");
        } else if (strcmp(lenh, "PostOrder") == 0) {
            PostOrder(root);
            printf("\n");
        } else if (strcmp(lenh, "#") == 0) {
            break;
        } else if (strcmp(lenh, "IsFull") == 0) {
            int k;
            scanf(" %d",&k);
            IsFull(k);
            printf("\n");
    }

    return 0;
}

