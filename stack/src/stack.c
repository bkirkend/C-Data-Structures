#include <stdlib.h>
#include <string.h>
#include "stack.h"

stack* stack_init(var_type type){
  stack *s = malloc(sizeof(stack));
  if(s == NULL){
    perror("Error: stack allocation\n");
    exit(1);
  } 
  s->type = type; 
  s->size = 0;
  s->cap = STACK_INIT_CAP;
  s->arr = malloc(s->cap * sizeof(void*));
  if(s->arr == NULL){
    perror("Error: stack array allocation\n");
    exit(1);
  }

  return s;
}

stack* stack_init_arr(var_type type, const void *const arr, size_t size){
  stack *s = malloc(sizeof(stack));
  if(s == NULL){
    perror("Error: stack allocation\n");
    exit(1);
  }

  size_t init_cap = STACK_INIT_CAP;

  //check if array larger than initial capacity, else double until large enough
  while(size > init_cap) init_cap <<= 1;
  
  s->type = type;
  s->size = size;
  s->cap = init_cap;
  s->arr = malloc(init_cap * sizeof(void*));
  
  switch(s->type){
    case TYPE_INT:
      for(size_t i = 0; i < s->size; i++) {
        s->arr[i] = malloc(sizeof(int));
        if(s->arr[i] == NULL) {
          perror("Error: allocation of elements\n");
          exit(1);
        }
        *(int*)s->arr[i] = ((const int*)arr)[i];
      }
      break;
    case TYPE_CHAR:
      for(size_t i = 0; i < s->size; i++) {
        s->arr[i] = malloc(sizeof(char));
        if(s->arr[i] == NULL) {
          perror("Error: allocation of elements\n");
          exit(1);
        }
        *(char*)s->arr[i] = ((const char*)arr)[i];
      }
      break;
    case TYPE_FLOAT:
      for(size_t i = 0; i < s->size; i++) {
        s->arr[i] = malloc(sizeof(float));
        if(s->arr[i] == NULL) {
          perror("Error: allocation of elements\n");
          exit(1);
        }
        *(float*)s->arr[i] = ((const float*)arr)[i];
      }
      break;
    case TYPE_DOUBLE:
      for(size_t i = 0; i < s->size; i++) {
        s->arr[i] = malloc(sizeof(double));
        if(s->arr[i] == NULL) {
          perror("Error: allocation of elements\n");
          exit(1);
        }
        *(double*)s->arr[i] = ((const double*)arr)[i];
      }
      break;
    case TYPE_STRING:
      for(size_t i = 0; i < s->size; i++) {
        s->arr[i] = strdup(((const char**)arr)[i]);
        if(s->arr[i] == NULL) {
          perror("Error: allocation of elements\n");
          exit(1);
        }
      }
      break;
    case TYPE_STRUCT:
      //implent custom dup function
      break;
    default:
      perror("Error: unrecognized var_type\n");
      exit(1);
  }
  if(s->arr == NULL){
    perror("Error: stack array allocation\n");
    exit(1);
  }

  return s;
}

static void grow_stack(stack *s, size_t size){
  //double capacity until suitable size
  while(size > s->cap) s->cap <<= 1;

  void** new_arr = realloc(s->arr, s->cap);
  if(new_arr == NULL){
    printf("could not increase array size - realloc failed\n");
    exit(1);
  }
  s->arr = new_arr;
}

void stack_push(stack *s, void *val){
  if(s->size + 1 > s->cap){
    grow_stack(s, s->size + 1);
  }
  s->arr[s->size++] = val;
}

void stack_push_arr(stack *const s, const void *const arr, size_t arr_size){
  int new_stack_size = s->size + arr_size;
  if(new_stack_size > s->cap){
    grow_stack(s, new_stack_size);  // Grow the stack if the new size exceeds capacity
  }
  
  switch(s->type){
    case TYPE_INT:
      for(size_t i = 0; i < arr_size; i++) {  // Loop over the input array size
        s->arr[s->size] = malloc(sizeof(int));  // Allocate memory for each new element
        if(s->arr[s->size] == NULL) {  // Check allocation error
          perror("Error: allocation of elements\n");
          exit(1);
        }
        *(int*)s->arr[s->size++] = ((const int*)arr)[i];  // Copy the value and increment size
      }
      break;
    case TYPE_CHAR:
      for(size_t i = 0; i < arr_size; i++) {
        s->arr[s->size] = malloc(sizeof(char));
        if(s->arr[s->size] == NULL) {
          perror("Error: allocation of elements\n");
          exit(1);
        }
        *(char*)s->arr[s->size++] = ((const char*)arr)[i];
      }
      break;
    case TYPE_FLOAT:
      for(size_t i = 0; i < arr_size; i++) {
        s->arr[s->size] = malloc(sizeof(float));
        if(s->arr[s->size] == NULL) {
          perror("Error: allocation of elements\n");
          exit(1);
        }
        *(float*)s->arr[s->size++] = ((const float*)arr)[i];
      }
      break;
    case TYPE_DOUBLE:
      for(size_t i = 0; i < arr_size; i++) {
        s->arr[s->size] = malloc(sizeof(double));
        if(s->arr[s->size] == NULL) {
          perror("Error: allocation of elements\n");
          exit(1);
        }
        *(double*)s->arr[s->size++] = ((const double*)arr)[i];
      }
      break;
    case TYPE_STRING:
      for(size_t i = 0; i < arr_size; i++) {
        s->arr[s->size] = strdup(((const char**)arr)[i]);  // Duplicate string for storage
        if(s->arr[s->size] == NULL) {
          perror("Error: allocation of elements\n");
          exit(1);
        }
        s->size++;  // Increment size after copying the string
      }
      break;
    case TYPE_STRUCT:
      // Implement custom duplication function for structs
      break;
    default:
      perror("Error: unrecognized var_type\n");
      exit(1);
  }
}

void* stack_pop(stack *const s){
  return s->arr[--s->size];
}

void* stack_top(const stack *const s){
  return s->arr[s->size - 1];
}

bool stack_isEmpty(const stack *const s){
  return s->size <= 0;
}

void stack_print(const stack *const s){
  switch(s->type){
    case TYPE_INT:
      for(size_t i = s->size; i > 0; i--){
        printf("%d\n", *(int*)s->arr[i - 1]); 
      }
      break;
    case TYPE_CHAR:
      for(size_t i = s->size; i > 0; i--){
        printf("%c\n", *(char*)s->arr[i - 1]); 
      }
      break;
    case TYPE_FLOAT:
      for(size_t i = s->size; i > 0; i--){
        printf("%f\n", *(float*)s->arr[i - 1]); 
      }
      break;
    case TYPE_DOUBLE:
      for(size_t i = s->size; i > 0; i--){
        printf("%f\n", *(double*)s->arr[i - 1]); 
      }
      break;
    case TYPE_STRING:
      for(size_t i = s->size - 1; i >= 0; i--){
        printf("%s\n", (char*)s->arr[i - 1]); 
      }
      break;
    case TYPE_STRUCT:
      //custom print fxn
      break;
    default:
      perror("Error: unrecognized var_type\n");
      exit(1);
  }
}

void stack_free(stack *const s){
  if(s != NULL) {
    for(size_t i = 0; i < s->size; i++) free(s->arr[i]);
    free(s->arr);
    free(s);
  }
}

