#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node* next;
};

struct Node* createNode(int x){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = x;
    newNode->next = NULL;
    return newNode;
}

void printLL(struct Node* head){
    struct Node* curr = head;
    while(curr){
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

struct Node* merge(struct Node* a, struct Node* b){
    struct Node* dummy = createNode(-1);
    struct Node* curr = dummy;
    while(a && b){
        if(a->data < b->data){
            curr->next = createNode(a->data);
            a = a->next;
        } else {
            curr->next = createNode(b->data);
            b = b->next;
        }
        curr = curr->next;
    }
    while(a){
        curr->next = createNode(a->data);
        curr = curr->next;
        a = a->next;
    }
    while(b){
        curr->next = createNode(b->data);
        curr = curr->next;
        b = b->next;
    }
    return dummy->next;
}

struct Node* mergeSort(struct Node* head){
    if(!head || !head->next) return head;
    struct Node* fast = head, *slow = head;
    while(fast && fast->next && fast->next->next){
        slow = slow->next;
        fast = fast->next->next;
    }
    struct Node* head2 = slow->next;
    slow->next = NULL;
    struct Node* left = mergeSort(head);
    struct Node* right = mergeSort(head2);
    return merge(left, right);
}

int main(){
    struct Node* head = createNode(-1);
    int n;
    printf("Enter the size of LL : ");
    scanf("%d", &n);
    printf("Enter the elements in LL : ");
    struct Node* curr = head;
    while(n--){
        int x;
        scanf("%d", &x);
        curr->next = createNode(x);
        curr = curr->next;
    }
    printf("Before Sorting : ");
    printLL(head->next);
    head = mergeSort(head->next);
    printf("After Sorting : ");
    printLL(head);
    return 0;
}