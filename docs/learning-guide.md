# Learn data structures with C

You’ll get the most from this guide if you’ve written a C function and used
arrays, structs, and pointers. Start with the example below, then follow the
source links to see how the library stores and moves data.

## Run your first program

Build the library from the repository root with `make`. On Windows with
MinGW, use `mingw32-make CC=gcc`.

Save this program as `first.c` in the repository root. It inserts the same
values into a queue and a stack, then reads them back.

```c
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "stack.h"

int main(void)
{
    Queue queue;
    Stack stack;
    const int values[] = {10, 20, 30};
    int next;
    int status = EXIT_FAILURE;

    queue_init(&queue);
    stack_init(&stack);

    for (size_t i = 0; i < sizeof values / sizeof values[0]; i++)
    {
        if (!queue_enqueue(&queue, values[i]))
            goto cleanup;

        stack_push(&stack, values[i]);
        /* stack_push returns void, so check whether the insertion succeeded. */
        if (stack_size(&stack) != (int)i + 1)
            goto cleanup;
    }

    printf("Queue:");
    while (queue_dequeue(&queue, &next))
        printf(" %d", next);
    puts("");

    printf("Stack:");
    while (stack_pop(&stack, &next))
        printf(" %d", next);
    puts("");
    status = EXIT_SUCCESS;

cleanup:
    queue_free(&queue);
    stack_free(&stack);
    return status;
}
```

Compile and run it from the repository root.

```sh
cc -std=c99 -Wall -Wextra -Iinclude first.c libcds.a -o first
./first
```

On Windows, use `gcc` in place of `cc`, name the output `first.exe`, and run
`.\first.exe` in PowerShell.

```text
Queue: 10 20 30
Stack: 30 20 10
```

`&queue` and `&stack` give the library the addresses of the structs so it can
change them. `&next` gives it a place to write the removed value. The loop
checks the Boolean return before using that value. Both containers allocate
nodes as you insert values. The cleanup functions release any nodes that
remain, including when an insertion fails partway through the program.

## Read the implementations in this order

1. **Arrays and pointers.** Start with the dynamic array. Find where
   `vector_insert` grows the backing array and shifts later elements. Then
   compare it with `list_push_front`, which links one node to the old head.
   [Dynamic array](../src/vector.c), [singly linked list](../src/linked_list.c)
2. **Order of removal.** Follow `stack_pop` to see why the newest value comes
   out first. Follow `queue_dequeue` into `deque_pop_front` to see how the
   oldest value comes out first. Trace what happens to both ends of the deque
   when its last node is removed.
   [Stack](../src/stack.c), [queue](../src/queue.c), [deque](../src/deque.c)
3. **Finding values efficiently.** Follow a heap insertion toward the root and
   compare it with an AVL insertion. Then trace how a hash map picks a bucket
   and how a trie follows one byte at a time.
   [Min-heap](../src/min_heap.c), [AVL tree](../src/avl_tree.c),
   [hash map](../src/hash_map.c), [trie](../src/trie.c)
4. **Relationships between items.** In breadth-first search, trace the
   `order` array as it grows. It doubles as the queue of discovered vertices.
   In union-find, trace how joining two sets changes a root and how later
   finds shorten the path to it.
   [Graph](../src/graph.c), [disjoint sets](../src/disjoint_set.c)

## Compare the costs

Here, `n` is the number of stored items. Amortized cost means the average
cost per operation over a sequence of operations.

| Task | Structure | Cost in this library |
| --- | --- | --- |
| Read the item at index `i` | Vector | O(1) |
| Append an item | Vector | O(1) amortized, O(n) when storage grows |
| Insert at the front | Singly linked list | O(1) |
| Append or search | Singly linked list | O(n) |
| Add or remove at an end | Stack, queue, or deque | O(1) |
| Read the smallest item | Min-heap | O(1) |
| Remove the smallest item | Min-heap | O(log n) |
| Find, insert, or remove an integer | AVL tree | O(log n) |
| Find a key | Hash map | O(1) expected with well-distributed keys, O(n) worst case |
| Traverse reachable vertices | Graph BFS | O(V + E) worst case, where V is the number of vertices and E is the number of edges |

## Practice

1. **Predict the order.** Insert `5, 5, -1` into both containers in the first
   program. Write down what each prints before you run it. Then try removing
   one extra element and check the return value.
2. **Try a priority queue.** Replace the stack with a min-heap. Use the same
   inputs and predict the new removal order. Check that duplicates survive.
3. **Trace a graph.** Draw four vertices. Connect 0 to 1, 1 to 2, and leave 3
   isolated. Run `graph_bfs` from 0 and then from 3. Add the edge from 2 to 3
   and predict what changes.
4. **Write a regression test.** Pick an edge case, such as removing the last
   item from a deque and then adding another. Add an assertion in
   [the test suite](../tests/test_structures.c) and run `make test` or
   `mingw32-make CC=gcc test`.
