#include <stdio.h>
#include <stdlib.h>

struct Stack {
    int top;
    int capacity;
    int *data;
};


struct Stack* create(int capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = -1;
    stack->capacity = capacity;
    stack->data = (int*)malloc(capacity * sizeof(int));
    return stack;
}


int isFull(struct Stack* stack) {
    return stack->top == (stack->capacity - 1);
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

void push(struct Stack* stack, int item) {
    if (isFull(stack)) {
        printf("stack has no capacity!");
        return;
    }

    stack->data[++stack->top] = item;
}

int pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        return -1;
    }
    return stack->data[stack->top--];
}

void printfEmpty(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("is empty\n");
    } else {
        printf("not empty\n");
    }
}

int peek(struct Stack* stack) {
    if (isEmpty(stack)) {
        return -1;
    }
    return stack->data[stack->top];
}

int main() {
    struct Stack* stack = create(10);
    push(stack, 10);
    push(stack, 20);
    push(stack, 30);
    int item = pop(stack);
    printf("pop %d\n", item);
    
    item = peek(stack);
    printf("peek %d\n", item);
}
