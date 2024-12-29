#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/var_type.h"

#define INIT_NUM_BINS 10

// defines array of linked lists to "hash_entry" objects
typedef struct _hashmap {
  //data entries
  struct _hashentry **bin_list;
  unsigned int num_bins;
  unsigned int size;
  var_type key_type;
  var_type value_type;
  //function ptrs
  unsigned int (*hash_func)(void*, unsigned int); //hash function
} hashmap;

// linked-list-style entries with key and value
typedef struct _hashentry {
  void *key;
  void *value;
  struct _hashentry *next;
} hash_entry;

//initialize empty hashmap, types are static and cannot be mixed
//TODO: custom function inputs for hashing, comparison, printing
//requires: mem_dup, hashing, key_comparison, and print functions passed to struct
// NOTE: comparison only required if type used as key
hashmap* hashmap_init(var_type key_type, var_type value_type);
hashmap* hashmap_init_n(unsigned int num_bins, var_type key_type, var_type value_type);
//insert key,value into hashmap; replace key if it exists
void hashmap_insert(hashmap *const hashmap, void *key, void *value);
//retrieve value in hashmap stored with key, return NULL if not found
//note that since a pointer is returned the value can be directly modified
void* hashmap_get(const hashmap *const hashmap, void *key);
//delete key and value entry from hashmap
void hashmap_remove(hashmap *const hashmap, void* key);
//free hashmap memory
void hashmap_free(hashmap *const hashmap);
//print hashmap keys and values
void hashmap_print(const hashmap *const hashmap);

//helper functions
//hash function, assigned in hashmap struct
static unsigned int int_hash(void *key, unsigned int num_bins);
static unsigned int float_hash(void *key, unsigned int num_bins);
static unsigned int str_hash(void *key, unsigned int num_bins);
//initialize hash_entry structure
static hash_entry *hash_entry_init(hashmap *const hashmap, void *key, void *value);
//free hash_entry structure
static void hash_entry_free(hash_entry *const h);
//print helper func
static void print_data(const var_type key_type, const var_type value_type, const hash_entry *const h);
static void* mem_dup(var_type type, const void *const ptr);
static int keys_are_equal(const hashmap *const h, const void *const key_a, const void *const key_b);

//TODO:
// hash algorithm optimization
// dynamic re-sizing
// wrapper functions for ease of input i.e. hashmap_get_int
static void hashmap_resize(hashmap *hashmap);
static float hashmap_load_factor(hashmap *hashmap);
void** get_keys(hashmap *hashmap);
void** get_values(hashmap *hashmap);

