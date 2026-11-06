#include <assert.h>
#include <limits.h>
#include <stdint.h>

#include "avl_tree.h"
#include "deque.h"
#include "disjoint_set.h"
#include "graph.h"
#include "hash_map.h"
#include "linked_list.h"
#include "min_heap.h"
#include "queue.h"
#include "stack.h"
#include "trie.h"
#include "vector.h"

static void test_list_and_stack(void)
{
    LinkedList list;
    Stack stack;
    int value = 99;
    list_init(&list);
    stack_init(&stack);
    assert(!stack_pop(&stack, &value) && value == 99);

    list_push_back(&list, 3);
    list_push_front(&list, 2);
    list_push_back(&list, 3);
    list_remove(&list, 3);
    assert(list.size == 2 && list.head->next->data == 3);
    list_remove(&list, 2);
    assert(list.size == 1 && !list_search(&list, 2));
    list_free(&list);
    assert(list.size == 0 && list.head == NULL);

    stack_push(&stack, INT_MIN);
    stack_push(&stack, INT_MAX);
    assert(!stack_pop(&stack, NULL) && stack_size(&stack) == 2);
    assert(stack_peek(&stack, &value) && value == INT_MAX);
    assert(stack_pop(&stack, &value) && value == INT_MAX);
    assert(stack_pop(&stack, &value) && value == INT_MIN);
    assert(stack_is_empty(&stack));
    stack_free(&stack);
}

static void test_vector(void)
{
    Vector vector;
    int value;
    vector_init(&vector);
    assert(!vector_insert(&vector, 1, 0));
    for (int i = 0; i < 128; i++)
        assert(vector_push(&vector, i));
    assert(vector_insert(&vector, 64, -1));
    assert(vector_get(&vector, 65, &value) && value == 64);
    assert(!vector_remove(&vector, 64, NULL) && vector.size == 129);
    assert(vector_remove(&vector, 64, &value) && value == -1);
    assert(vector_get(&vector, 64, &value) && value == 64);
    assert(vector_set(&vector, 127, INT_MIN));
    assert(vector_remove(&vector, 127, &value) && value == INT_MIN);
    assert(!vector_get(&vector, 127, &value) && value == INT_MIN);
    vector_free(&vector);
    assert(vector.size == 0 && vector_push(&vector, 0));
    vector_free(&vector);
}

static void test_deque_and_queue(void)
{
    Deque deque;
    Queue queue;
    int value = 99;
    deque_init(&deque);
    assert(!deque_pop_back(&deque, &value) && value == 99);
    assert(deque_push_front(&deque, 2));
    assert(deque_push_front(&deque, 1));
    assert(deque_push_back(&deque, 4));
    assert(deque_insert(&deque, 2, 3));
    for (size_t i = 0; i < 4; i++)
        assert(deque_get(&deque, i, &value) && value == (int)i + 1);
    assert(!deque_insert(&deque, 5, 0));
    assert(deque_remove(&deque, 1, &value) && value == 2);
    assert(deque_peek_front(&deque, &value) && value == 1);
    assert(deque_peek_back(&deque, &value) && value == 4);
    assert(deque_pop_back(&deque, &value) && value == 4);
    assert(deque_pop_front(&deque, &value) && value == 1);
    assert(deque_pop_back(&deque, &value) && value == 3);
    assert(deque.size == 0 && deque.front == NULL && deque.back == NULL);
    deque_free(&deque);

    queue_init(&queue);
    assert(queue_enqueue(&queue, INT_MAX));
    assert(queue_enqueue(&queue, INT_MIN));
    assert(queue_peek(&queue, &value) && value == INT_MAX);
    assert(queue_size(&queue) == 2);
    assert(queue_dequeue(&queue, &value) && value == INT_MAX);
    assert(queue_dequeue(&queue, &value) && value == INT_MIN);
    assert(!queue_dequeue(&queue, &value));
    queue_free(&queue);
}

static void test_heap(void)
{
    MinHeap heap;
    const int unsorted[] = {9, 2, 2, 0, 4, 1, INT_MIN, INT_MAX, -4, 7, 3};
    const int sorted[] = {INT_MIN, -4, 0, 1, 2, 2, 3, 4, 7, 9, INT_MAX};
    int value;
    min_heap_init(&heap);
    for (size_t i = 0; i < sizeof unsorted / sizeof *unsorted; i++)
        assert(min_heap_push(&heap, unsorted[i]));
    for (size_t i = 0; i < sizeof sorted / sizeof *sorted; i++)
    {
        assert(min_heap_peek(&heap, &value) && value == sorted[i]);
        assert(min_heap_pop(&heap, &value) && value == sorted[i]);
    }
    assert(!min_heap_pop(&heap, &value));
    min_heap_free(&heap);
}

static void test_avl(void)
{
    AvlTree tree;
    avl_init(&tree);
    for (int i = 0; i < 1024; i++)
        assert(avl_insert(&tree, i));
    assert(!avl_insert(&tree, 511) && tree.size == 1024);
    for (int i = 1; i < 1024; i += 2)
        assert(avl_remove(&tree, i));
    assert(!avl_remove(&tree, 511) && tree.size == 512);
    for (int i = 0; i < 1024; i++)
        assert(avl_contains(&tree, i) == (i % 2 == 0));
    for (int i = 1022; i >= 0; i -= 2)
        assert(avl_remove(&tree, i));
    assert(tree.size == 0 && tree.root == NULL);
    assert(avl_insert(&tree, 3));
    assert(avl_insert(&tree, 1));
    assert(avl_insert(&tree, 2));
    avl_free(&tree);
}

static void test_hash_map(void)
{
    HashMap map;
    int value = 99;
    hash_map_init(&map);
    assert(!hash_map_get(&map, 0, &value) && value == 99);
    for (int key = -256; key < 256; key++)
        assert(hash_map_put(&map, key, key * 2));
    assert(hash_map_put(&map, INT_MIN, INT_MAX));
    for (int key = -256; key < 256; key++)
        assert(hash_map_get(&map, key, &value) && value == key * 2);
    assert(hash_map_put(&map, 17, 42) && map.size == 513);
    assert(hash_map_get(&map, 17, &value) && value == 42);
    for (int key = -256; key < 256; key += 2)
        assert(hash_map_remove(&map, key));
    assert(!hash_map_remove(&map, 0) && map.size == 257);
    assert(hash_map_get(&map, INT_MIN, &value) && value == INT_MAX);
    hash_map_free(&map);
    assert(map.size == 0 && map.capacity == 0);
}

static void test_trie(void)
{
    Trie trie;
    trie_init(&trie);
    assert(!trie_has_prefix(&trie, ""));
    assert(trie_insert(&trie, ""));
    assert(trie_insert(&trie, "car"));
    assert(trie_insert(&trie, "cart"));
    assert(trie_insert(&trie, "cat"));
    assert(trie_insert(&trie, "dog"));
    assert(trie_insert(&trie, "cart") && trie.size == 5);
    assert(!trie_contains(&trie, "ca") && trie_has_prefix(&trie, "ca"));
    assert(!trie_contains(&trie, "CAT"));
    assert(trie_remove(&trie, "car") && trie_contains(&trie, "cart"));
    assert(trie_remove(&trie, "cart") && !trie_has_prefix(&trie, "car"));
    assert(trie_contains(&trie, "cat") && trie_contains(&trie, "dog"));
    assert(trie_remove(&trie, "dog") && trie_contains(&trie, "cat"));
    assert(trie_remove(&trie, "") && !trie_contains(&trie, ""));
    assert(!trie_remove(&trie, "catnip") && trie.size == 1);
    trie_free(&trie);
    assert(!trie_has_prefix(&trie, ""));
}

static void test_graph(void)
{
    Graph graph;
    size_t order[5];
    assert(graph_init(&graph, 5, false));
    assert(graph_add_edge(&graph, 0, 1));
    assert(graph_add_edge(&graph, 0, 1));
    assert(graph_add_edge(&graph, 1, 2));
    assert(graph_add_edge(&graph, 2, 0));
    assert(graph_add_edge(&graph, 2, 3));
    assert(graph_add_edge(&graph, 3, 3));
    assert(!graph_add_edge(&graph, 0, 5));
    assert(graph_has_edge(&graph, 1, 0));
    assert(graph_bfs(&graph, 0, order, 4) == 0);
    assert(graph_bfs(&graph, 0, order, 5) == 4);
    assert(order[0] == 0 && order[3] == 3);
    assert(graph_remove_edge(&graph, 2, 3));
    assert(!graph_has_edge(&graph, 3, 2));
    assert(graph_bfs(&graph, 3, order, 5) == 1 && order[0] == 3);
    graph_free(&graph);

    assert(graph_init(&graph, 2, true));
    assert(graph_add_edge(&graph, 0, 1) && !graph_has_edge(&graph, 1, 0));
    assert(graph_bfs(&graph, 1, order, 5) == 1);
    graph_free(&graph);
    assert(!graph_init(&graph, SIZE_MAX, false));
    graph_free(&graph);
}

static void test_disjoint_set(void)
{
    DisjointSet set;
    size_t first, second;
    assert(disjoint_set_init(&set, 6));
    assert(disjoint_set_union(&set, 0, 1));
    assert(disjoint_set_union(&set, 2, 3));
    assert(disjoint_set_union(&set, 1, 3));
    assert(disjoint_set_union(&set, 0, 3) && set.components == 3);
    assert(disjoint_set_find(&set, 0, &first));
    assert(disjoint_set_find(&set, 3, &second) && first == second);
    assert(disjoint_set_find(&set, 4, &second) && first != second);
    assert(!disjoint_set_union(&set, 0, 6) && set.components == 3);
    disjoint_set_free(&set);
    assert(!disjoint_set_init(&set, SIZE_MAX));
    disjoint_set_free(&set);
}

int main(void)
{
    test_list_and_stack();
    test_vector();
    test_deque_and_queue();
    test_heap();
    test_avl();
    test_hash_map();
    test_trie();
    test_graph();
    test_disjoint_set();
    return 0;
}
