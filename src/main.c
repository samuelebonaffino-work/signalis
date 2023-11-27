#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "optbox.h"
#include "raw.h"

///////////////////////////////////// STRUCTS

// char* blob = "u:1,u:2,u:3,u:4,u:5,s:1";
typedef struct test_a
{
  uint16_t val_1 : 1;
  uint16_t val_2 : 2;
  uint16_t val_3 : 3;
  uint16_t val_4 : 4;
  uint16_t val_5 : 5;
  uint16_t spare : 1;
} test_a_t;

typedef struct test_b
{
  uint16_t val_4_1 : 4;
  uint16_t val_4_2 : 4; 
  uint16_t val_4_3 : 4;
  uint16_t val_4_4 : 4;
} test_b_t;

///////////////////////////////////// MAIN

int main()
{
  test_a_t a = {0};
  raw_t raw = raw_create((void*) &a, "u:1,u:2,u:3,u:4,u:5,s:1");

  optbox_t opt = optbox_create("opt", 1);
  optbox_t opt_test = optbox_create("test", 6);
  optbox_t opt_test_val_1 = optbox_create("val_1", 0);
  optbox_t opt_test_val_2 = optbox_create("val_2", 0);
  optbox_t opt_test_val_3 = optbox_create("val_3", 0);
  optbox_t opt_test_val_4 = optbox_create("val_4", 0);
  optbox_t opt_test_val_5 = optbox_create("val_5", 0);
  optbox_t opt_test_spare = optbox_create("spare", 0);

  optbox_add(&opt, &opt_test);
  optbox_add(&opt_test, &opt_test_val_1);
  optbox_add(&opt_test, &opt_test_val_2);
  optbox_add(&opt_test, &opt_test_val_3);
  optbox_add(&opt_test, &opt_test_val_4);
  optbox_add(&opt_test, &opt_test_val_5);
  optbox_add(&opt_test, &opt_test_spare);

  int selection = 0;
  int value = 0;
  if(optbox_run(opt, &selection, &value))
  {
    raw_set(raw, selection, value);
  }

  printf("a.val_1 = %u\n", a.val_1);
  printf("a.val_2 = %u\n", a.val_2);
  printf("a.val_3 = %u\n", a.val_3);
  printf("a.val_4 = %u\n", a.val_4);
  printf("a.val_5 = %u\n", a.val_5);
  printf("a.spare = %u\n", a.spare);

  optbox_free(&opt);
  optbox_free(&opt_test);

  return 0;
}