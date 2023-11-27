#ifndef OPTBOX_H
#define OPTBOX_H

#include <stdbool.h>

typedef struct optbox
{
  char* name;
  int num_opts;
  struct optbox** opts;
  int counter;
} optbox_t;

optbox_t optbox_create(char* name, int num_opts);
void optbox_add(optbox_t* opt, optbox_t* child);
int optbox_select(optbox_t opt);
int optbox_input(optbox_t opt);
bool optbox_run(optbox_t opt, int* selection, int* value);
void optbox_free(optbox_t* opt);

#endif // OPTBOX_H
