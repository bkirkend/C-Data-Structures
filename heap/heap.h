#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
  int* arr;
  int size;
  int cap;
} heap;

//build empty heap
heap* heap_init(int size);
//build heap from existing array
heap* heap_init_arr(int *arr, int size);
//pop element from heap
int heap_pop(heap* h);
//get top element on heap
int heap_top(heap *h);
//add element to heap
void heap_push(heap *h, int ele);
//destroy heap
void heap_free(heap *h);
//print heap 
void heap_print(heap *h);
//check if empty
bool heap_empty(heap *h);

//internal functions
static int left_child(int i);
static int right_child(int i);
static int parent(int i);
static void swap(int *a, int *b);
static void upward_heapify(heap *h, int idx);
static void downward_heapify(heap *h, int idx);
