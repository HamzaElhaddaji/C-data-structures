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

int list_search(const LinkedList *list, int value){

    Node *current = list->head;

    while (current != NULL)
    {
        if (current->data == value)
        {
            return 1; // Value found
        }
        current = current->next;
    }

    return 0; // Value not found

}
void list_print(const LinkedList *list){

    Node *current = list->head;

    while (current != NULL)
    {
        printf("%d -> ", current->data);
        current = current->next;
    }

    printf("NULL\n");
}