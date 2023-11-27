#include "raw.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void bitfield_set(int *bitfield, int value, int beg, int bits)
{
  // 1. Clear desired portion of bits
  // 2. Store desired value using cleared bitfield portion
  *bitfield &= ~(((1 << bits) - 1) << beg);
  *bitfield |= (value << beg);
}

static char *my_strdup(const char *str)
{
  if (str == NULL)
  {
    return NULL; // Handle NULL input
  }

  size_t len = strlen(str) + 1; // Include space for the null terminator

  char *new_str = (char *)malloc(len); // Allocate memory
  if (new_str == NULL)
  {
    return NULL; // Allocation failure
  }

  strcpy(new_str, str); // Copy the string

  return new_str;
}

raw_t raw_create(void *ptr_data, char *blob)
{
  raw_t raw;

  raw.ptr_data = ptr_data;
  raw.blob = blob;
  raw.num_fields = strlen(blob) > 0 ? 1 : 0;

  char *token = blob;
  while ((raw.num_fields > 0) && ((token = strchr(token, ',')) != NULL))
  {
    raw.num_fields++;
    token++;
  }

  return raw;
}

bool raw_set(raw_t raw, int id, int value)
{
  if (id <= raw.num_fields)
  {
    // Tokenize the string using commas as delimiters
    char *blob_tok = my_strdup(raw.blob);
    char *field_info = strtok(blob_tok, ",");
    char *field_bits;
    int beg = 0;
    int bits = 0;
    int count = 0;

    while (field_info != NULL)
    {
      field_bits = strchr(field_info, ':');
      if (field_bits != NULL)
      {
        field_bits++;
        if (++count == id)
        {
          bits = atoi(field_bits);
          break;
        }
        else
        {
          beg += atoi(field_bits);
          field_info = strtok(NULL, ",");
        }
      }
      else
      {
        printf("ERR: invalid field format\n");
      }
    }
    free(blob_tok);
    bitfield_set(raw.ptr_data, value, beg, bits);

    return true;
  }

  return false;
}
