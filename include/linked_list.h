#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    int size;
} LinkedList;

void list_init(LinkedList *list);

void list_push_front(LinkedList *list, int value);

void list_push_back(LinkedList *list, int value);

int list_search(const LinkedList *list, int value);

void list_print(const LinkedList *list);

void list_remove(LinkedList *list, int value);

void list_free(LinkedList *list);

#endif