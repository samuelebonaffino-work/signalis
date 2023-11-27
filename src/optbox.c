#include "optbox.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

optbox_t optbox_create(char* name, int num_opts)
{
  optbox_t opt;

  opt.name = name;
  opt.num_opts = num_opts;
  opt.counter = 0;
  if (num_opts > 0)
  {
    opt.opts = (optbox_t**) malloc(num_opts * sizeof(optbox_t*));
    for (int i = 0; i < num_opts; i++)
    {
      opt.opts[i] = NULL;
    }
  }

  return opt;
}

void optbox_add(optbox_t* opt, optbox_t* child)
{
  if(opt->counter < opt->num_opts)
  {
    opt->opts[opt->counter++] = child;
  }
}

int optbox_select(optbox_t opt)
{
  int choice = -1;

  printf("%s:\n", opt.name);
  for (int i = 0; i < opt.num_opts; i++)
  {
    printf("%d. %s\n", i + 1, opt.opts[i]->name);
  }
  printf("Choice: ");
  scanf("%u", &choice);

  if (choice < 1 && choice > opt.num_opts)
  {
    printf("ERR: invalid choice, skipping.\n");
    return -1;
  }

  return choice;
}

int optbox_input(optbox_t opt)
{
  int input = -1;
  printf("%s = ", opt.name);
  scanf("%d", &input);
  return input ? input : 0;
}

bool optbox_run(optbox_t opt, int* selection, int* value)
{
  int select = -1;

  while (opt.num_opts > 0)
  {
    select = optbox_select(opt);
    if (select < 0)
    {
      return false;
    }
    opt = *(opt.opts[select - 1]);
    printf("\n");
  }
  *selection = select;
  *value = optbox_input(opt);
  printf("\n");

  return true;
}

void optbox_free(optbox_t* opt)
{
  if(opt->num_opts > 0)
  {
    free(opt->opts);
  }
}