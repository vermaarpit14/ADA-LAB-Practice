#include <stdio.h>
#include <stdlib.h>

struct Node{
    int key;
    struct Node* left;
    struct Node* right;
    int height;
};

int max(int a, int b){
    return (a > b) ? a : b;
}

int Height(struct Node* n){
    if(n == NULL) return 0;
    return n->height;
}

struct Node* createNode(int key){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

int BF(struct Node* n){
    if(n == NULL) return 0;
    return Height(n->left)-Height(n->right);
}

struct Node* LL(struct Node* z){
    struct Node* y = z->left;
    struct Node* T2 = y->right;
    y->right = z;
    z->left = T2;
    z->height = max(Height(z->left), Height(z->right)) + 1;
    y->height = max(Height(y->left), Height(y->right)) + 1;
    return y;
}

struct Node* RR(struct Node* z){
    struct Node* y = z->right;
    struct Node* T2 = y->left;
    y->left = z;
    z->right = T2;
    z->height = max(Height(z->left), Height(z->right)) + 1;
    y->height = max(Height(y->left), Height(y->right)) + 1;
    return y;
}

struct Node* LR(struct Node* z){
    z->left = RR(z->left);
    return LL(z);
}

struct Node* RL(struct Node* z){
    z->right = LL(z->right);
    return RR(z);
}

struct Node* Insert(struct Node* n, int key){
    if(n == NULL) return createNode(key);
    if(key < n->key) n->left = Insert(n->left, key);
    else if(key > n->key) n->right = Insert(n->right, key);
    else return n;
    n->height = max(Height(n->left), Height(n->right)) + 1;
    int bf = BF(n);
    if(bf > 1 && key < n->left->key) return LL(n);
    if(bf > 1 && key > n->left->key) return LR(n);
    if(bf < -1 && key > n->right->key) return RR(n);
    if(bf < -1 && key < n->right->key) return RL(n);
    return n;
}

struct Node* minNode(struct Node* n){
    struct Node* curr = n;
    while(curr->left) curr = curr->left;
    return curr;
}

struct Node* Delete(struct Node* n, int key){
    if(n == NULL) return n;
    if(key < n->key) n->left = Delete(n->left, key);
    else if(key > n->key) n->right = Delete(n->right, key);
    else {
        if(!n->left){
            struct Node* temp = n->right;
            free(n);
            return temp;
        } else if(!n->right){
            struct Node* temp = n->left;
            free(n);
            return temp;
        } else {
            struct Node* temp = minNode(n->right);
            n->key = temp->key;
            n->right = Delete(n->right, n->key);
        }
    }
    if(n == NULL) return n;
    n->height = max(Height(n->left), Height(n->right)) + 1;
    int bf = BF(n);
    if(bf > 1 && BF(n->left) >= 0) return LL(n);
    if(bf > 1 && BF(n->left) < 0) return LR(n);
    if(bf < -1 && BF(n->right) < 0) return RR(n);
    if(bf < -1 && BF(n->right) >= 0) return RL(n);
    return n;
}

void Inorder(struct Node* n){
    if(n){
        Inorder(n->left);
        printf("%d ", n->key);
        Inorder(n->right);
    }
}

int main() {
    struct Node* root = NULL;
    int choice, key;
    while (1) {
        printf("\n--- AVL Tree Operations ---\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Display Inorder\n");
        printf("4. Display Height\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                root = Insert(root, key);
                break;
            case 2:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                root = Delete(root, key);
                break;
            case 3:
                printf("Inorder traversal: ");
                Inorder(root);
                printf("\n");
                break;
            case 4:
                printf("Height of tree: %d\n", Height(root));
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
}
