#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STACK_INIT_CAP 10

//stack structure
typedef struct {
  int* arr;
  int size;
  int cap;
} stack;

//functions like pop and top require user to check if stack is empty before calling

//initialize empty stack
stack* stack_init(void);
//initialize stack from arr
stack* stack_init_arr(int* arr, int size);
//push entry onto stack
void stack_push(stack *s, int val);
//push array onto stack value by value
void stack_push_arr(stack *s, int* arr, int arr_size);
//pop entry from stack
int stack_pop(stack *s);
//peek at top element
int stack_top(stack *s);
//check if stack is empty
bool stack_isEmpty(stack *s);
//print contents of stack (from top)
void stack_print(stack *s);
//cleanup stack
void stack_free(stack *s);

//internal functions
//increase size of stack dynamically
static void grow_stack(stack *s, int size);
