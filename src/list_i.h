
/**
   Extremely simple singly-linked list of ints.
   Everything is IN the list, no external pointers.
 */

#ifndef INLIST_H
#define INLIST_H

#include <stdbool.h>
#include <stdlib.h>

struct list_i_item
{
  int data;
  struct list_i_item* next;
};

struct list_i
{
  struct list_i_item* head;
  struct list_i_item* tail;
  int size;
};

void list_i_init(struct list_i* target);

struct list_i* list_i_create(void);

int list_i_size(struct list_i* target);

struct list_i_item* list_i_add(struct list_i* target, int data);
#define list_i_push(target, data) list_i_add(target, data)

struct list_i* list_i_parse(char* s);

int list_i_search(struct list_i* target, int data);

int list_i_random(struct list_i* target);

bool list_i_remove(struct list_i* target, int data);

int list_i_pop(struct list_i* target);

int list_i_peek(struct list_i* target);

int list_i_poll(struct list_i* target);

struct list_i_item* list_i_ordered_insert(struct list_i* target,
                                          int data);

struct list_i_item* list_i_unique_insert(struct list_i* target,
                                         int data);

bool list_i_contains(struct list_i* target, int data);

void list_i_printf(struct list_i* target);

/*
int list_i_tostring(char* str, size_t size,
struct list_i* target); */

char* list_i_serialize(struct list_i* target);

void list_i_clear(struct list_i* target);

void list_i_free(struct list_i* target);

bool list_i_toints(struct list_i* target, int** result, int* count);

#endif