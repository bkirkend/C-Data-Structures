#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define QUEUE_INIT_CAP 10

typedef struct {
  int* arr;
  int cap;
  int size;
  int start;
  int end;
} queue;

//initalize empty queue
queue* queue_init(void);
//initialize queue from size
queue* queue_init_size(int init_cap);
//initialize queue from array
queue* queue_init_arr(int *arr, int size);
//enqueue element to queue
void enqueue(queue *q, int ele);
//dequeue element from queue
int dequeue(queue *q);
//peek at next element
int queue_peek(queue *q);
//check if queue is empty
bool queue_isEmpty(queue *q);
//free queue
void queue_free(queue *q);
//print queue contents
void queue_print(queue *q);

//internal helper functions
static void grow_queue(queue *q, int new_size);
