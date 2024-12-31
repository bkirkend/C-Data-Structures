#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../src/stack.h"

#define STACK_INIT_CAP 10

//functions like pop and top require user to check if stack is empty before calling

//initialize empty stack
stack* stack_init_int(void);
//initialize stack from arr
stack* stack_init_arr_int(int* arr, size_t size);
//push entry onto stack
void stack_push_int(stack *const s, const int val);
//push array onto stack value by value
void stack_push_arr_int(stack *const s, const int *const arr, size_t arr_size);
//pop entry from stack
int stack_pop_int(stack *const s);
//peek at top element
int stack_top_int(const stack *const s);
//check if stack is empty
bool stack_isEmpty_int(const stack *const s);

