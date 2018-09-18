#include <stdio.h>
#include <stdlib.h>


struct Node {
    int data;
    struct Node *next;
};

void printList(struct Node *head) {
    struct Node *cur = head;
    while(cur != NULL) {
        printf(" %d ", cur->data);
        cur = cur->next;
    }
}

void insertAtBegining(struct Node **headRef, int newData) {
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));
    node->data = newData;
    node->next = (*headRef);
    *(headRef) = node;
}

void insertAfter(struct Node *prevNode,  int newData) {
    if (prevNode == NULL) {
        printf("previous node can not be NULL");
        return;
    }
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = newData;
    newNode->next = prevNode->next;
    prevNode->next = newNode;
    return ;
}


void pushNode(struct Node **headRef, int newData) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = newData;
    newNode->next = (*headRef);
    (*headRef) = newNode;
}

struct Node* deleteNodeAtPosition(struct Node **headRef, int x) {
    if (&headRef == NULL) {
        return NULL;
    }

    struct Node* temp = *headRef;

    if (x == 0) {
        *headRef = temp->next;
        return temp;
    }

    struct Node* prev;
    for (int i = 0; i < x && temp != NULL; i++) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        return NULL;
    }

    prev->next = temp->next;
    return temp;
}


struct Node* deleteNodePosition(struct Node* head, int position) {
    if (head == NULL) {
        return NULL;
    }

    struct Node* temp = head;
    if (position == 0) {
        temp = head;
        head = head->next;
        return temp;
    }

    struct Node* prev;
    for (int i = 0; i < position && temp != NULL; i++) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        return NULL;
    }

    prev->next = temp->next;
    return temp;
}


struct Node* deleteNode(struct Node *head, int x) {
    if (head == NULL) {
        printf("head can not be NULL");
        return NULL;
    }

    struct Node *prev = head;
    for (int i = 0; ((i < x - 1) && (prev->next != NULL)); i++) {
        prev = prev->next;
    }

    if (prev->next != NULL) {
        struct Node* temp = prev->next;
        prev->next = prev->next->next;
        return temp;
    } else {
        return NULL;
    }
}


void deleteLink(struct Node **headRef) {
    struct Node *current = *headRef;
    struct Node *next;

    while(current != NULL) {
        next = current;
        free(current);
        current = next;
    }

    *headRef = NULL;
}

void insertAtEnd(struct Node **headRef, int newData) {
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));
    node->data = newData;
    node->next = NULL;
    struct Node *tail = (*headRef);
    if (tail == NULL) {
        (*headRef) = node;
        return ;
    }
    while(tail->next != NULL) {
        tail = tail->next;
    }
    tail->next = node;
}


int getCount(struct Node* head) {
    int i = 0;
    while(head != NULL) {
        head = head->next;
        i++;
    }
    return i;
}

int getCountRecursive(struct Node* head) {
    if (head == NULL) {
        return 0;
    }
    return getCountRecursive(head->next) + 1;
}

int main() {
    struct Node* head = NULL;
    struct Node* second = NULL;
    struct Node* third = NULL;

    head = (struct Node*)malloc(sizeof(struct Node));
    second = (struct Node*)malloc(sizeof(struct Node));
    third = (struct Node*)malloc(sizeof(struct Node));

    head->data = 1;
    head->next = second;

    second->data = 2;
    second->next = third;

    third->data = 3;
    third->next = NULL;

    printList(head);
    printf("\n");
    insertAtBegining(&head, 4);
    printList(head);
    printf("\n");
    insertAtEnd(&head, 6);
    printList(head);
    printf("\n");
    insertAfter(head->next->next, 8);
    printList(head);
    printf("\n");
    int i = getCountRecursive(head);
    printf("%d\n", i);
    return 0;
}

