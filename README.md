# C-data-structures

An integer data structures library implemented from scratch in C. It provides a
singly linked list and a last-in, first-out stack.

## Build and run

With a C99 compiler and GNU Make, run:

```sh
make
make example
./examples/demo
```

On Windows with MinGW, use `mingw32-make CC=gcc example` and run
`examples\demo.exe`.

Include `linked_list.h` or `stack.h` in your program and link the static
library:

```sh
cc -Iinclude my_program.c libcds.a -o my_program
```

## API behavior

- Initialize each container with `list_init` or `stack_init` before use.
  Call `list_free` or `stack_free` to release its nodes and reset it to an
  empty state. Pass a non-null container to operations other than cleanup,
  and avoid copying a container that owns nodes.
- `list_search` returns 1 if a value is present and 0 otherwise.
  `list_remove` removes the first matching value.
- `stack_pop` removes the top value and `stack_peek` reads it. Both return
  false for an empty stack or a null output pointer, leaving the stack and
  any output value unchanged.
- The existing push APIs return void. On allocation failure or if the size
  would exceed `INT_MAX`, the container stays unchanged.
