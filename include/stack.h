#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

typedef struct StackNode {
    int data;
    struct StackNode *next;
} StackNode;

typedef struct {
    StackNode *top;
    int size;
} Stack;

/* Initialization */
void stack_init(Stack *stack);

/* Basic operations */
void stack_push(Stack *stack, int value);
bool stack_pop(Stack *stack, int *value);
bool stack_peek(const Stack *stack, int *value);

/* Utility operations */
bool stack_is_empty(const Stack *stack);
int stack_size(const Stack *stack);
void stack_free(Stack *stack);

#endif


