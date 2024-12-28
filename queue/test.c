#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "queue.h"

void test_empty_queue() {
    queue *q = queue_init();
    assert(queue_isEmpty(q) == true);
    printf("Test empty queue passed.\n");
    queue_free(q);
}

void test_enqueue_dequeue() {
    queue *q = queue_init();
    enqueue(q, 1);
    enqueue(q, 2);
    assert(dequeue(q) == 1);
    assert(dequeue(q) == 2);
    assert(queue_isEmpty(q) == true);
    printf("Test enqueue and dequeue passed.\n");
    queue_free(q);
}

void test_full_queue() {
    queue *q = queue_init_size(3); // Small initial size to test resizing
    enqueue(q, 1);
    enqueue(q, 2);
    enqueue(q, 3);
    enqueue(q, 4); //queue should resize here 
    assert(q->cap > 3);
    assert(dequeue(q) == 1);
    enqueue(q, 5);
    assert(dequeue(q) == 2);
    assert(dequeue(q) == 3);
    assert(dequeue(q) == 4);
    assert(dequeue(q) == 5);
    
    printf("Test full queue passed.\n");
    queue_free(q);
}

void test_resize() {
    queue *q = queue_init_size(2); // Small initial size to test resizing
    enqueue(q, 1);
    enqueue(q, 2);
    enqueue(q, 3); // Queue should resize here
    assert(q->cap > 2);
    assert(dequeue(q) == 1);
    assert(dequeue(q) == 2);
    assert(dequeue(q) == 3);
    printf("Test resize passed.\n");
    queue_free(q);
}

void test_wrap_around() {
    queue *q = queue_init_size(3); // Small initial size to test wrap around
    enqueue(q, 1);
    enqueue(q, 2);
    dequeue(q); // Removes 1
    enqueue(q, 3);
    enqueue(q, 4); // Queue should wrap around here
    assert(dequeue(q) == 2);
    assert(dequeue(q) == 3);
    assert(dequeue(q) == 4);
    printf("Test wrap around passed.\n");
    queue_free(q);
}

void test_peek() {
    queue *q = queue_init();
    enqueue(q, 1);
    assert(queue_peek(q) == 1);
    enqueue(q, 2);
    assert(queue_peek(q) == 1);
    dequeue(q);
    assert(queue_peek(q) == 2);
    printf("Test peek passed.\n");
    queue_free(q);
}

void test_init_arr() {
    int arr[] = {1, 2, 3, 4, 5};
    queue *q = queue_init_arr(arr, 5);
    assert(q->size == 5);
    assert(dequeue(q) == 1);
    assert(dequeue(q) == 2);
    assert(dequeue(q) == 3);
    assert(dequeue(q) == 4);
    assert(dequeue(q) == 5);
    printf("Test init with array passed.\n");
    queue_free(q);
}

int main() {
    test_empty_queue();
    test_enqueue_dequeue();
    test_full_queue();
    test_resize();
    test_wrap_around();
    test_peek();
    test_init_arr();
    printf("All tests passed.\n");
    return 0;
}

