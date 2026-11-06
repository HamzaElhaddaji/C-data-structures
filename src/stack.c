#include "stack.h"

#include <limits.h>
#include <stdlib.h>

void stack_init(Stack *stack)
{
    stack->top = NULL;
    stack->size = 0;
}

void stack_push(Stack *stack, int value)
{
    if (stack->size == INT_MAX)
        return;

    StackNode *node = malloc(sizeof *node);
    if (node == NULL)
        return;

    node->data = value;
    node->next = stack->top;
    stack->top = node;
    stack->size++;
}

bool stack_pop(Stack *stack, int *value)
{
    if (!stack_peek(stack, value))
        return false;

    StackNode *node = stack->top;
    stack->top = node->next;
    stack->size--;
    free(node);
    return true;
}

bool stack_peek(const Stack *stack, int *value)
{
    if (stack_is_empty(stack) || value == NULL)
        return false;

    *value = stack->top->data;
    return true;
}

bool stack_is_empty(const Stack *stack)
{
    return stack->top == NULL;
}

int stack_size(const Stack *stack)
{
    return stack->size;
}

void stack_free(Stack *stack)
{
    if (stack == NULL)
        return;

    while (stack->top != NULL)
    {
        StackNode *node = stack->top;
        stack->top = node->next;
        free(node);
    }
    stack->size = 0;
}
