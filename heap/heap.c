#include "heap.h"

heap* heap_init(int cap){
  //can check here if allocation is null
  heap *h = (heap *) malloc(sizeof(heap));
  if (h == NULL){
    perror("Error, heap allocation\n");
    exit(1);
  }
  if((h->arr = malloc(sizeof(int) * cap)) == NULL){
    perror("Error, heap array allocation\n");
    exit(1);
  }
  h->size = 0;
  h->cap = cap;

  return h;
}


heap* heap_init_arr(int* arr, int size){
  //can check here if allocation is null
  heap *h = (heap *) malloc(sizeof(heap));

  
  h->arr = malloc(sizeof(int) * size);
  if(h->arr == NULL){
    perror("Error, heap array allocation\n");
    exit(1);
  }

  //copy array input
  for(int i = 0; i < size; i++){
    h->arr[i] = arr[i];
  }

  
  h->size = size;
  h->cap = size;

  //TODO - upwards heapify the array
  for(int i = h->size - 1; i >= 0; i--){
    downward_heapify(h, i);
  }

  return h;
}


int heap_pop(heap* h){
  int ret = h->arr[0];

  //move last element to the top
  swap(h->arr, h->arr + h->size - 1);
  h->size--;
  downward_heapify(h, 0);

  return ret;
}


int heap_top(heap *h){
  //must validate that heap is size >= 1 before using
  return h->arr[0];
}


void heap_push(heap *h, int ele) {
  if(h->size == h->cap){
    perror("error: not enough space in stack\n");  
    exit(1);
  }
 
  //append to end of heap structure and upwards heapify
  h->arr[h->size++] = ele;
  upward_heapify(h, h->size - 1);
}


void heap_free(heap *h){
  if(h != NULL){
    free(h->arr);
    free(h);
  }
}


void heap_print(heap *h){
  int height = 1;
  int s = h->size;
  while(s > 0){
    s >>= 1;
    height++;
  }
  int base = 1 << (height - 1);
  int num = 0;

  for(int i = 0; i < height; i++){
    int curr = 1 << (i - 1);
    int base_diff = base - curr;
    for(int j = 0; j < curr; j++){
      for(int j = 0; j < (base_diff / curr); j++){
        printf(" ");
      }
      if(num < h->size) {
        printf("%d", h->arr[num++]);
      } else {
        printf("N");
      }
      for(int j = 0; j < (base_diff / curr); j++){
        printf(" ");
      }
    }
    printf("\n");
  }
}

bool heap_empty(heap *h){
  return h->size <= 0;
}


/*
      0
    1   2
   3 4 5 6

*/

//heapify helper functions
static int left_child(int i) {return 2*i + 1;}
static int right_child(int i) {return 2*i + 2;}
static int parent(int i){return (i - 1) / 2;}

static void swap(int *a, int *b){
  *a ^= *b;
  *b ^= *a;
  *a ^= *b;
}

static void upward_heapify(heap* h, int idx){
  //for use when adding new element - only need to move last element up
  
  while(idx > 0){
    int par_idx = parent(idx);

    if(h->arr[idx] > h->arr[par_idx]) {
      swap(h->arr + idx, h->arr + par_idx);
      idx = par_idx;
    } else {
      return;
    }
  }
}


static void downward_heapify(heap *h, int idx){
  for(;;){
    int left_idx = left_child(idx); 
    int right_idx = right_child(idx);

    int max_idx = idx;
    
    if(left_idx < h->size && h->arr[left_idx] > h->arr[max_idx]) {
      max_idx = left_idx;
    }

    if(right_idx < h->size && h->arr[right_idx] > h->arr[max_idx]) {
      max_idx = right_idx;
    }
    
    if(max_idx == idx) return;  

    swap(h->arr + idx, h->arr + max_idx);
    idx = max_idx;

  }
}



