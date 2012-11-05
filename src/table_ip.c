
#include "tools.h"

#include "table_ip.h"

int
hash_int(int key, int N)
{
  valgrind_assert_msg(N != 0, "hash_int(): N==0");
  return (key % N);
}

bool
table_ip_init(struct table_ip* target, int capacity)
{
  if (! target)
    return false;

  target->size     = 0;
  target->capacity = capacity;

  target->array = malloc(sizeof(struct list_ip) * capacity);
  if (!target->array)
    return false;

  for (int i = 0; i < capacity; i++)
    list_ip_init(&target->array[i]);

  return true;
}

struct table_ip*
table_ip_create(int capacity)
{
  struct table_ip *new_table = NULL;

  new_table = (struct table_ip*) malloc(sizeof(struct table_ip));

  table_ip_init(new_table, capacity);

  return new_table;
}

int
table_ip_size(struct table_ip* target)
{
  return target->size;
}

/**
   Add key/data pair to table.
   If key exists, do nothing and return false
*/
bool
table_ip_add(struct table_ip* target, int key, void* data)
{
  int index = hash_int(key, target->capacity);

  bool result = list_ip_add(&target->array[index], key, data);

  if (result)
    target->size++;

  return result;
}

/**
  @return The data or NULL if not found.
*/
void*
table_ip_search(const struct table_ip* target, int key)
{
  valgrind_assert_msg(key >= 0, "negative key: %i", key);
  int index = hash_int(key, target->capacity);
  return list_ip_search(&target->array[index], key);
}

void*
table_ip_remove(struct table_ip* target, int key)
{
  int index = hash_int(key, target->capacity);
  void* result = list_ip_remove(&target->array[index], key);
  if (result)
    target->size--;
  return result;
}

void
table_ip_free(struct table_ip* target)
{
  for (int i = 0; i < target->capacity; i++)
    list_ip_free(&target->array[i]);
  free(target->array);
  free(target);
}

void
table_ip_destroy(struct table_ip* target)
{
  for (int i = 0; i < target->capacity; i++)
    list_ip_destroy(&target->array[i]);

  free(target->array);
  free(target);
}

/**
   @param format specifies the output format for the data items
 */
void
table_ip_dump(const char* format, const struct table_ip* target)
{
  char s[200];
  printf("{\n");
  for (int i = 0; i < target->capacity; i++)
  {
    if (target->array[i].size > 0)
    {
      list_ip_snprintf(s, 200, "%s", &target->array[i]);
      printf("%i: %s \n", i, s);
    }
  }
  printf("}\n");
}

/** Dump list_ip to string a la snprintf()
    size must be greater than 2.
    format specifies the output format for the data items
    internally allocates O(size) memory
    returns int greater than size if size limits are exceeded
            indicating result is garbage
*/
int table_ip_tostring(char* str, size_t size,
                      const char* format,
                      const struct table_ip* target)
{
  int   error = size+1;
  char* ptr   = str;
  ptr += sprintf(str, "{\n");

  char* s = (char*) malloc(sizeof(char) * size);

  for (int i = 0; i < target->size; i++)
  {
    int r = list_ip_snprintf(s, size, format, &target->array[i]);
    if ((ptr-str) + r + 2 < size)
      ptr += sprintf(ptr, "%s\n", s);
    else
      return error;
  }
  sprintf(ptr, "}\n");

  free(s);
  return (ptr-str);
}

#ifdef DEBUG_TABLE_IP

int
main()
{
  char s[200];
  struct table_ip* table = table_ip_create(30);

  table_ip_add(table, 30, "hello30");
  table_ip_add(table, 22, "hello22");
  table_ip_add(table, 21, "hello21");
  table_ip_add(table, 51, "hello51");

  // table_ip_tostring(s, 200, "%s", table);
  table_ip_dump("%s", table);

  table_ip_remove(table, 22);

  table_ip_dump("%s", table);
}

#endif