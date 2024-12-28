#include "queue.h"

queue* queue_init(void){
  queue* q = (queue *)malloc(sizeof(queue));
  if(q == NULL){
    perror("Error: queue allocation\n");
    exit(1);
  }
  q->arr = malloc(QUEUE_INIT_CAP * sizeof(int));
  if(q->arr == NULL){
    perror("Error: queue array allocation\n");
    exit(1);
  }

  q->cap = QUEUE_INIT_CAP;
  q->size = 0;
  q->start = 0;
  q->end = -1;

  return q;
}


queue* queue_init_size(int init_cap){
  queue* q = (queue *)malloc(sizeof(queue));
  if(q == NULL){
    perror("Error: queue allocation\n");
    exit(1);
  }
  q->arr = malloc(init_cap * sizeof(int));
  if(q->arr == NULL){
    perror("Error: queue array allocation\n");
    exit(1);
  }

  q->cap = init_cap;
  q->size = 0;
  q->start = 0;
  q->end = -1;

  return q;
}


queue* queue_init_arr(int *arr, int size){
  queue* q = (queue *)malloc(sizeof(queue));
  if(q == NULL){
    perror("Error: queue allocation\n");
    exit(1);
  }
  q->arr = malloc(size * sizeof(int));
  if(q->arr == NULL){
    perror("Error: queue array allocation\n");
    exit(1);
  }
  
  for(int i = 0; i < size; i++){
    q->arr[i] = arr[i];
  }

  q->cap = size;
  q->size = size;
  q->start = 0;
  q->end = size - 1;

  return q;
}

void enqueue(queue *q, int ele){
  if(q->size + 1 > q->cap){
    grow_queue(q, q->size + 1);
  }
  q->size++;
  q->end = (q->end + 1) % q->cap;
  q->arr[q->end] = ele;
}


int dequeue(queue *q){
  q->size--;
  int ret = q->arr[q->start];
  q->start = (q->start + 1) % q->cap;
  return ret;
}


int queue_peek(queue *q){
  return q->arr[q->start];
}


bool queue_isEmpty(queue *q){
  return !q->size;
}


void queue_free(queue *q){
  free(q->arr);
  free(q);
}

void queue_print(queue *q){
  if(queue_isEmpty(q)){
    printf("{}\n");
  } else {
    for(int i = 0; i < q->size; i++){
      printf("%d ", q->arr[(q->start + i) % q->cap]);
    }
    printf("\n");
  }
}

//internal function - must check if size greater than capacity before calling
static void grow_queue(queue *q, int new_size){
  int prev_cap = q->cap;
  while(q->cap < new_size) q->cap <<= 1;
  q->arr = realloc(q->arr, sizeof(int) * q->cap);
  if(q->arr == NULL){
    perror("Error: array reallocation\n");
    exit(1);
  }
  
  //move elements as necessary to retain circular properties
  //check if circular
  if(q->end <= q->start && q->size > 0){
    for(int i = 0; i <= q->end; i++){
      q->arr[prev_cap + i] = q->arr[i]; 
    }
    q->end += prev_cap;
  }
}

