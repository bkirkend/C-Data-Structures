#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "hashmap.h"

// Edge Case: Empty Hashmap
void test_hashmap_empty() {
    printf("Testing empty hashmap:\n");

    hashmap *hmap = hashmap_init(TYPE_INT, TYPE_INT);

    // Check if retrieval returns NULL when the hashmap is empty
    int key1 = 1;
    assert(hashmap_get(hmap, &key1) == NULL);  // Should be NULL
    printf("Retrieving from empty hashmap returns NULL.\n");

    // Test removal on an empty hashmap
    hashmap_remove(hmap, &key1);  // Should not crash, nothing to remove
    printf("Removal from empty hashmap does not crash.\n");

    hashmap_free(hmap);
}

// Edge Case: Duplicate Keys
void test_hashmap_duplicate_keys() {
    printf("Testing hashmap with duplicate keys:\n");

    hashmap *hmap = hashmap_init(TYPE_INT, TYPE_INT);

    int key1 = 1, value1 = 100;
    int value2 = 200;

    hashmap_insert(hmap, &key1, &value1);
    hashmap_insert(hmap, &key1, &value2);  // Insert same key with new value

    // Verify that the value was updated
    assert(*(int*)hashmap_get(hmap, &key1) == 200);

    printf("After duplicate key insertion, value for key 1 is: %d\n", *(int*)hashmap_get(hmap, &key1));

    printf("Before free\n");
    hashmap_free(hmap);
    printf("After free\n");
}

// Edge Case: Hash Collisions
void test_hashmap_collisions() {
    printf("Testing hashmap with hash collisions:\n");

    hashmap *hmap = hashmap_init(TYPE_INT, TYPE_INT);

    // Make sure two keys hash to the same bin (or manually force collision)
    int key1 = 1, value1 = 100;
    int key2 = 2, value2 = 200;
    hashmap_insert(hmap, &key1, &value1);
    hashmap_insert(hmap, &key2, &value2);

    // Ensure both values are retrieved correctly despite being in the same bin
    assert(*(int*)hashmap_get(hmap, &key1) == 100);
    assert(*(int*)hashmap_get(hmap, &key2) == 200);

    printf("Collision handling works correctly.\n");

    hashmap_free(hmap);
}

// Edge Case: Large Number of Elements
void test_hashmap_large_scale() {
    printf("Testing hashmap with large number of elements:\n");

    int num_elements = 1000000;
    hashmap *hmap = hashmap_init_n(10000, TYPE_INT, TYPE_INT);

    for (int i = 0; i < num_elements; i++) {
        hashmap_insert(hmap, &i, &i);
    }

    // Verify that values are correctly inserted
    for (int i = 0; i < num_elements; i++) {
        assert(*(int*)hashmap_get(hmap, &i) == i);
    }

    printf("Inserted %d elements successfully.\n", num_elements);

    hashmap_free(hmap);
}

// Edge Case: Removal from a Large Hashmap
void test_hashmap_large_scale_removal() {
    printf("Testing hashmap removal with large number of elements:\n");

    int num_elements = 1000000;
    hashmap *hmap = hashmap_init_n(10000, TYPE_INT, TYPE_INT);

    for (int i = 0; i < num_elements; i++) {
        hashmap_insert(hmap, &i, &i);
    }

    // Remove every second element
    for (int i = 0; i < num_elements; i += 2) {
        hashmap_remove(hmap, &i);
    }

    // Verify that every second element is removed
    for (int i = 0; i < num_elements; i++) {
        if (i % 2 == 0) {
            assert(hashmap_get(hmap, &i) == NULL);  // Every second element should be removed
        } else {
            assert(*(int*)hashmap_get(hmap, &i) == i);
        }
    }

    printf("Successfully removed half of the elements.\n");

    hashmap_free(hmap);
}

void test_hashmap_int() {
    printf("Testing hashmap with int keys and values:\n");

    hashmap *hmap = hashmap_init(TYPE_INT, TYPE_INT);

    int key1 = 1, value1 = 100;
    int key2 = 2, value2 = 200;
    int key3 = 3, value3 = 300;

    hashmap_insert(hmap, &key1, &value1);
    hashmap_insert(hmap, &key2, &value2);
    hashmap_insert(hmap, &key3, &value3);

    // Verify that the values are inserted correctly
    assert(*(int*)hashmap_get(hmap, &key1) == 100);
    assert(*(int*)hashmap_get(hmap, &key2) == 200);
    assert(*(int*)hashmap_get(hmap, &key3) == 300);

    printf("Retrieved value for key 2: %d\n", *(int*)hashmap_get(hmap, &key2));

    hashmap_free(hmap);
}

void test_hashmap_float() {
    printf("Testing hashmap with float keys and values:\n");

    hashmap *hmap = hashmap_init(TYPE_FLOAT, TYPE_FLOAT);

    float key1 = 1.1f, value1 = 100.1f;
    float key2 = 2.2f, value2 = 200.2f;
    float key3 = 3.3f, value3 = 300.3f;

    hashmap_insert(hmap, &key1, &value1);
    hashmap_insert(hmap, &key2, &value2);
    hashmap_insert(hmap, &key3, &value3);

    // Verify that the values are inserted correctly
    assert(*(float*)hashmap_get(hmap, &key1) == 100.1f);
    assert(*(float*)hashmap_get(hmap, &key2) == 200.2f);
    assert(*(float*)hashmap_get(hmap, &key3) == 300.3f);

    printf("Retrieved value for key 2.2: %.2f\n", *(float*)hashmap_get(hmap, &key2));

    hashmap_free(hmap);
}

void test_hashmap_string() {
    printf("Testing hashmap with string keys and values:\n");

    hashmap *hmap = hashmap_init(TYPE_STRING, TYPE_STRING);

    char *key1 = "key1", *value1 = "value1";
    char *key2 = "key2", *value2 = "value2";
    char *key3 = "key3", *value3 = "value3";

    hashmap_insert(hmap, key1, value1);
    hashmap_insert(hmap, key2, value2);
    hashmap_insert(hmap, key3, value3);

    // Verify that the values are inserted correctly
    assert(strcmp((char*)hashmap_get(hmap, key1), "value1") == 0);
    assert(strcmp((char*)hashmap_get(hmap, key2), "value2") == 0);
    assert(strcmp((char*)hashmap_get(hmap, key3), "value3") == 0);

    printf("Retrieved value for key 'key2': %s\n", (char*)hashmap_get(hmap, key2));

    hashmap_free(hmap);
}

void test_hashmap_char() {
    printf("Testing hashmap with char keys and values:\n");

    hashmap *hmap = hashmap_init(TYPE_CHAR, TYPE_CHAR);

    char key1 = 'a', value1 = 'A';
    char key2 = 'b', value2 = 'B';
    char key3 = 'c', value3 = 'C';

    hashmap_insert(hmap, &key1, &value1);
    hashmap_insert(hmap, &key2, &value2);
    hashmap_insert(hmap, &key3, &value3);

    // Verify that the values are inserted correctly
    assert(*(char*)hashmap_get(hmap, &key1) == 'A');
    assert(*(char*)hashmap_get(hmap, &key2) == 'B');
    assert(*(char*)hashmap_get(hmap, &key3) == 'C');

    printf("Retrieved value for key 'b': %c\n", *(char*)hashmap_get(hmap, &key2));

    hashmap_free(hmap);
}

int main() {
    // Run all tests
    test_hashmap_int();
    test_hashmap_float();
    test_hashmap_string();
    test_hashmap_char();

    // Run edge cases
    test_hashmap_empty();
    test_hashmap_duplicate_keys();
    test_hashmap_collisions();
    test_hashmap_large_scale();
    test_hashmap_large_scale_removal();

    printf("All tests passed successfully.\n");

    return 0;
}
