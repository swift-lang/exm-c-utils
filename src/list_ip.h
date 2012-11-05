
/**
   Extremely simple singly-linked list of int-keyed data items.
 */

#ifndef LIST_IP_H
#define LIST_IP_H

#include <stdbool.h>
#include <stdio.h>

// Maximum size of a list_ip datum
#define LIST_IP_MAX_DATUM 100

struct list_ip_item
{
  int   key;
  void* data;
  struct list_ip_item* next;
};

struct list_ip
{
  struct list_ip_item* head;
  struct list_ip_item* tail;
  int size;
};

void list_ip_init(struct list_ip* target);

struct list_ip* list_ip_create(void);

void list_ip_append(struct list_ip* target, int key, void* data);

bool list_ip_add(struct list_ip* target, int key, void* data);

#define list_ip_push(target, key, data) list_ip_add(target, key, data)

//struct list_ip_item* list_ip_replace(struct list_ip* target,
//                                 int key, void* data);

bool list_ip_contains(const struct list_ip* target, int key);

bool list_ip_matches(const struct list_ip* target,
                     int (*cmp)(void*,void*), void* data);

struct list_ip_item* list_ip_ordered_insert(struct list_ip* target,
                                        int key, void* data);
struct list_ip_item*
list_ip_ordered_insert_unique(struct list_ip* target,
                            int (*cmp)(void*,void*),
                            int key, void* data);

void* list_ip_pop(struct list_ip* target);

void* list_ip_poll(struct list_ip* target);

void* list_ip_get(struct list_ip* target, int i);

void* list_ip_search(struct list_ip* target, int key);

void list_ip_free(struct list_ip* target);

void list_ip_destroy(struct list_ip* target);

void* list_ip_remove(struct list_ip* target, int key);

//// Output methods...
void list_ip_dump(char* (f)(void*), struct list_ip* target);
void list_ip_printf(char* format, struct list_ip* target);
void list_ip_fdump(FILE* file, char* (f)(void*), struct list_ip* target);
void list_ip_fprintf(FILE* file, char* format, struct list_ip* target);
void list_ip_dumpkeys(struct list_ip* target);
void list_ip_xdumpkeys(struct list_ip* target);
void list_ip_fdumpkeys(FILE* file, struct list_ip* target);
void list_ip_output(char* (*f)(void*), struct list_ip* target);
int  list_ip_snprintf(char* str, size_t size,
                      const char* format,
                      const struct list_ip* target);
int list_ip_marshal(char* str, size_t size,
                    char* (f)(void*), struct list_ip* target);
char* list_ip_serialize_ptrs(struct list_ip* target);


#endif