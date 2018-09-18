#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;

    struct Node* next;
    struct Node* prev;
} Node;

typedef struct LinkedList {
    int data;
    struct LinkedList* next;
} LinkedList;

struct Node* head = NULL;

struct Node* current = NULL;

int isEmpty() {

}

LinkedList* create(int n) {
    LinkedList *head, *node, *end;
    head = malloc(sizeof(LinkedList));
    end = head;
    for (int i = 0; i < n; i++) {
        node = malloc(sizeof(LinkedList));
        scanf("%d", &node->data);
        end->next = node;
        end = node;
    }
}

void printLinkedList(LinkedList list) {
    LinkedList *curNode = &list;
    while(curNode != NULL) {
        printf("%d ->", curNode.data);
        curNode = curNode.next;
    }
    printf("\n");
}

int main() {
    LinkedList *head = create(5);
    printLinkedList(*head);
}

