CC ?= cc
AR ?= ar
CFLAGS ?= -std=c99 -Wall -Wextra -Wpedantic
CPPFLAGS += -Iinclude

ifeq ($(OS),Windows_NT)
EXEEXT = .exe
endif

LIBRARY = libcds.a
MODULES = linked_list stack vector deque queue min_heap avl_tree hash_map graph disjoint_set trie
OBJECTS = $(addprefix src/,$(addsuffix .o,$(MODULES)))
HEADERS = $(addprefix include/,$(addsuffix .h,$(MODULES)))
EXAMPLE = examples/demo$(EXEEXT)
TEST = tests/test_structures$(EXEEXT)

.PHONY: all example test
all: $(LIBRARY)

example: $(EXAMPLE)

test: $(TEST)
	"$(CURDIR)/$(TEST)"

$(LIBRARY): $(OBJECTS)
	$(AR) rcs $@ $^

$(OBJECTS): src/%.o: include/%.h
src/vector.o src/min_heap.o: src/int_storage.h
src/queue.o: include/deque.h

$(EXAMPLE): examples/demo.c $(LIBRARY) include/linked_list.h include/stack.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LIBRARY) $(LDLIBS)

$(TEST): tests/test_structures.c $(LIBRARY) $(HEADERS)
	$(CC) $(CPPFLAGS) $(CFLAGS) -UNDEBUG $(LDFLAGS) -o $@ $< $(LIBRARY) $(LDLIBS)
