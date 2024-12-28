#include "heap.h"

int find_kth_largest(int arr[], int size, int k);


int find_kth_largest(int arr[], int size, int k){
  heap *hp = heap_init(k);

  for(int i = 0; i < size; i++){
    if(i < k){
      heap_push(hp, -arr[i]);
    } else if (-arr[i] < heap_top(hp)) {
      heap_pop(hp);
      heap_push(hp, -arr[i]);
    }
  }
  int ret =  -heap_top(hp);

  heap_free(hp);

  return ret;

}

int main(){
  int arr[] = {6, 5, 9, 2, 5, 0, 3, 5};
  //printf("%d\n", find_kth_largest(arr,sizeof(arr) / sizeof(*arr), 1));
  
  heap* h = heap_init_arr(arr, 8);

  heap_print(h);

  while(!heap_empty(h)) printf("%d\n", heap_pop(h));

  heap_free(h);
  
  return 0;
}
