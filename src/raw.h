#ifndef RAW_H
#define RAW_H

#include <stdbool.h>

typedef struct raw
{
  char* blob;
  int num_fields;
  void* ptr_data;
} raw_t;

raw_t raw_create(void* ptr_data, char* blob);
bool raw_set(raw_t raw, int id, int value);

#endif // RAW_H
