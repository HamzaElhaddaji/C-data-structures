# C-data-structures

A C99 library of common data structures. Most containers store integers.
The trie stores strings, and the graph and disjoint sets use integer indices.

| Header | Structure and operations |
| --- | --- |
| `vector.h` | Dynamic array with indexed reads, updates, insertion, and removal |
| `linked_list.h` | Singly linked list with front and back insertion, search, and removal |
| `deque.h` | Doubly linked list with indexed insertion and removal and constant-time operations at both ends |
| `stack.h` | Last-in, first-out stack |
| `queue.h` | First-in, first-out queue |
| `min_heap.h` | Binary min-heap for priority queue operations |
| `avl_tree.h` | Self-balancing binary search tree for an ordered set of integers |
| `hash_map.h` | Resizable hash table for integer keys and values |
| `trie.h` | Prefix tree for null-terminated, case-sensitive byte strings |
| `graph.h` | Directed or undirected adjacency-list graph with breadth-first traversal |
| `disjoint_set.h` | Union-find with path compression and union by size |

## Build and test

With a C99 compiler and GNU Make:

```sh
make all example test
./examples/demo
```

On Windows with MinGW, use `mingw32-make CC=gcc all example test` and run
`examples\demo.exe`.

Include the header for the structure you want to use and link the static library:

```sh
cc -Iinclude my_program.c libcds.a -o my_program
```

## API behavior

Initialize each container before use and call its `*_free` function to release
its memory and reset it. Use valid, non-null container pointers and pass
separate storage for output arguments. Avoid copying containers that own memory.

- Boolean operations report success. Reads and removals that require an output
  pointer return false on a null pointer and leave the container unchanged.
- Vector and deque indices are zero-based. Insertion at the current size
  appends an element.
- The existing list and stack push APIs return void and leave the container
  unchanged on allocation failure or when its size would exceed `INT_MAX`.
  `list_remove` removes the first matching value.
- AVL insertion returns false for a duplicate or allocation failure. Hash map
  insertion updates the value if the key already exists. Trie insertion
  succeeds for an existing word without increasing the size.
- Graph vertices and disjoint-set elements are numbered from zero to one less
  than their initialization size. Give `graph_bfs` an output array with room
  for every vertex. It returns the number visited, or zero on failure.
