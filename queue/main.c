#include <stdio.h>
#include "queue.h"

int main(int argc, char** argv){
  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  queue *q = queue_init_arr(arr, sizeof(arr) / sizeof(*arr));
  queue_print(q);

  dequeue(q);
  dequeue(q);
  dequeue(q);
  queue_print(q);

  printf("cap: %d\n", q->cap);

  enqueue(q, 15);
  queue_print(q);
  enqueue(q, 16);
  queue_print(q);
  enqueue(q, 17);
  queue_print(q);
  enqueue(q, 18);
  queue_print(q);
  printf("cap: %d\n", q->cap);

  while(!queue_isEmpty(q)) printf("Popping %d\n", dequeue(q));
  
  queue_free(q);
  return 0;
}

