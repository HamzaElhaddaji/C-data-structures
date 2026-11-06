CC ?= cc
AR ?= ar
CFLAGS ?= -std=c99 -Wall -Wextra -Wpedantic
CPPFLAGS += -Iinclude

ifeq ($(OS),Windows_NT)
EXEEXT = .exe
endif

LIBRARY = libcds.a
OBJECTS = src/linked_list.o src/stack.o
EXAMPLE = examples/demo$(EXEEXT)

.PHONY: all example
all: $(LIBRARY)

example: $(EXAMPLE)

$(LIBRARY): $(OBJECTS)
	$(AR) rcs $@ $^

src/linked_list.o: include/linked_list.h
src/stack.o: include/stack.h

$(EXAMPLE): examples/demo.c $(LIBRARY) include/linked_list.h include/stack.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LIBRARY) $(LDLIBS)
