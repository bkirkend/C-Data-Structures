#include "stack.h"
#include <stdlib.h>

stack* stack_init(void){
  stack *s = malloc(sizeof(stack));
  if(s == NULL){
    perror("Error: stack allocation\n");
    exit(1);
  } 
  
  s->size = 0;
  s->cap = STACK_INIT_CAP;
  s->arr = malloc(sizeof(int) * STACK_INIT_CAP);
  if(s->arr == NULL){
    perror("Error: stack array allocation\n");
    exit(1);
  }

  return s;
}

stack* stack_init_arr(int* arr, int size){
  stack *s = malloc(sizeof(stack));
  if(s == NULL){
    perror("Error: stack allocation\n");
    exit(1);
  }

  int init_cap = STACK_INIT_CAP;

  //check if array larger than initial capacity, else double until large enough
  while(size > init_cap) init_cap <<= 1;

  s->size = size;
  s->cap = init_cap;
  s->arr = malloc(sizeof(int) * init_cap);
  if(s->arr == NULL){
    perror("Error: stack array allocation\n");
    exit(1);
  }

  //copy contents of array
  for(int i = 0; i < size; i++) s->arr[i] = arr[i];

  return s;
}

static void grow_stack(stack *s, int size){
  //double capacity until suitable size
  while(size > s->cap) s->cap <<= 1;

  int* new_arr = (int *) realloc(s->arr, s->cap);
  if(new_arr == NULL){
    printf("could not increase array size - realloc failed\n");
    exit(1);
  }
  s->arr = new_arr;
}

void stack_push(stack *s, int val){
  if(s->size + 1 > s->cap){
    grow_stack(s, s->size + 1);
  }
  s->arr[s->size++] = val;
}

void stack_push_arr(stack *s, int* arr, int arr_size){
  int new_stack_size = s->size + arr_size;
  if(new_stack_size > s->cap){
    grow_stack(s, new_stack_size);
  }
  for(int i = 0; i < arr_size; i++) s->arr[s->size++] = arr[i];
}

int stack_pop(stack *s){ 
  return s->arr[--s->size];
}

int stack_top(stack *s){
  return s->arr[s->size - 1];
}

bool stack_isEmpty(stack *s){
  return s->size <= 0;
}

void stack_print(stack *s){
  for(int i = s->size - 1; i >= 0; i--) printf("%d\n", s->arr[i]); 
}

void stack_free(stack *s){
  if(s != NULL) {
    free(s->arr);
    free(s);
  }
}


