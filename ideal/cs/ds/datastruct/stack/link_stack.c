#include <stdio.h>
#include <stdlib.h>


struct StackNode {
    int data;
    struct StackNode* next;
};

struct StackNode* createNode(int data) {
    struct StackNode* node = (struct StackNode*)malloc(sizeof(struct StackNode));
    node->data = data;
    node->next = NULL;
    return node;
}

int isEmpty(struct StackNode* stack) {
    return !stack;
}

void push(struct StackNode** root, int data) {
    struct StackNode* node = (struct StackNode*)malloc(sizeof(struct StackNode));
    node->next = *root;
    node->data = data;
    *root = node;
}

int pop(struct StackNode** top) {
    if(isEmpty(*top)) {
        return -1;
    }
    struct StackNode* temp = *top;
    (*top) = (*top)->next;
    int popped = temp->data;
    free(temp);
    return popped;
}

int peek(struct StackNode* top) {
    return top->data;
}

int main() {
    struct StackNode* stack = createNode(100);
    push(&stack, 300);
    int item = pop(&stack);
    printf("%d\n", item);
    item = peek(stack);
    printf("%d\n", item);
}
