#include "stack_int.h"

stack* stack_init_int(void){
  return stack_init(TYPE_INT);
}

stack* stack_init_arr_int(int* arr, size_t size){
  return stack_init_arr(TYPE_INT, arr, size);
}

void stack_push_int(stack *const s, const int val){
  int* copy = malloc(sizeof(int));
  if(copy == NULL){
    perror("Failed to allocate value\n");
    exit(1);
  }
  *copy = val;
  stack_push(s, copy);
}

void stack_push_arr_int(stack *const s, const int *const arr, size_t arr_size){
  stack_push_arr(s, arr, arr_size);
}

int stack_pop_int(stack *const s){
  int* value_ptr = (int *) stack_pop(s);
  int value = *value_ptr;
  free(value_ptr);
  return value;
}

int stack_top_int(const stack *const s){
  return *(int*) stack_top(s);
}
