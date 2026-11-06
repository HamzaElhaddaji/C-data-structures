#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"
#include "stack.h"

int main(void)
{
    LinkedList list;
    Stack stack;
    int value;

    list_init(&list);
    list_push_back(&list, 10);
    list_push_back(&list, 20);
    list_print(&list);

    stack_init(&stack);
    for (const Node *node = list.head; node != NULL; node = node->next)
        stack_push(&stack, node->data);

    int status = list.size == 2 && stack_size(&stack) == 2
        ? EXIT_SUCCESS : EXIT_FAILURE;

    while (stack_pop(&stack, &value))
        printf("Popped %d\n", value);

    stack_free(&stack);
    list_free(&list);
    return status;
}
