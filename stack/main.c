#include <stdio.h>

#include "stack.h"

#define SIZE(arr) (sizeof(arr)) / (sizeof(*arr))

int main(int argc, char** argv){
  int arr[] = {1, 2, 3, 4, 5};
  stack* stack = stack_init_arr(arr, SIZE(arr));
  
  printf("printing stack after initialization\n");
  stack_print(stack);

  printf("printing stack after pushing array\n");
  int arr2[] = {12, 13, 14};
  stack_push_arr(stack, arr2, SIZE(arr2));
  stack_print(stack);
  
  stack_push(stack, 42);
  printf("printing stack after pushing 42\n");
  stack_print(stack);
  
  while(!stack_isEmpty(stack)) printf("popping value: %d\n", stack_pop(stack));

  stack_print(stack);

  stack_free(stack);

  return 0;
}