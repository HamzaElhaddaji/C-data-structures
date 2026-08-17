#include "linked_list.h"
#include <stdlib.h>

void list_init(LinkedList *list)
{
    list->head = NULL;
    list->size = 0;
}

void list_push_front(LinkedList *list, int value)
{
    Node *new_node = malloc(sizeof(Node));

    new_node->data = value;
    new_node->next = list->head;

    list->head = new_node;
    list->size++;
}

void list_push_back(LinkedList *list, int value)
{
    Node *new_node = malloc(sizeof(Node));

    new_node->data = value;
    new_node->next = NULL;

    if (list->head == NULL)
    {
        list->head = new_node;
    }
    else
    {
        Node *current = list->head;

        while (current->next != NULL)
        {
            current = current->next;
        }

        current->next = new_node;
    }

    list->size++;
}