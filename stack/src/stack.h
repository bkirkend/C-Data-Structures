#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../headers/var_type.h"

#define STACK_INIT_CAP 10

typedef struct {
  var_type type;
  void** arr;
  size_t size;
  size_t cap;
} stack;

//functions like pop and top require user to check if stack is empty before calling

//initialize empty stack
stack* stack_init(var_type type);
//initialize stack from arr
stack* stack_init_arr(var_type type, const void *const arr, size_t size);
//push entry onto stack
void stack_push(stack *const s, void *val);
//push array onto stack value by value
void stack_push_arr(stack *const s, const void *const arr, size_t arr_size);
//pop entry from stack
void* stack_pop(stack *const s);
//peek at top element
void* stack_top(const stack *const s);
//check if stack is empty
bool stack_isEmpty(const stack *const s);
//print contents of stack (from top)
void stack_print(const stack *const s);
//cleanup stack
void stack_free(stack *const s);

//internal functions
//increase size of stack dynamically
static void grow_stack(stack *s, size_t size);
