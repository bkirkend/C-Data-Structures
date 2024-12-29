#include "hashmap.h"

static void* mem_dup(var_type type, const void *const ptr){
  void* copy = NULL;
  switch(type){
    case TYPE_INT: 
      copy = malloc(sizeof(int));
      if(copy == NULL) printf("failed to allocate int copy\n");
      *(int*)copy = *(int*)ptr;
      return copy; 

    case TYPE_CHAR:
      copy = malloc(sizeof(char));
      if(copy == NULL) printf("failed to allocate char copy\n");
      *(char*)copy = *(char*)ptr;
      return copy;

    case TYPE_FLOAT:
      copy = malloc(sizeof(float));
      if(copy == NULL) printf("failed to allocate float copy\n");
      *(float*)copy = *(float*)ptr;
      return copy;

    case TYPE_STRING:
      copy = strdup(ptr);
      if(copy == NULL) printf("failed to allocate string copy\n");
      return copy;

    default:
      //could accept custom behavior here
      return copy;
  }
}

static int keys_are_equal(const hashmap *const h, const void *const key_a, const void *const key_b){
  switch(h->key_type){
    case TYPE_INT: 
      return *(int*)key_a == *(int *)key_b; 

    case TYPE_CHAR:
      return *(char*)key_a == *(char *)key_b;

    case TYPE_FLOAT:
      return *(float*)key_a == *(float*)key_b;

    case TYPE_STRING:
      return !strcmp((char*)key_a, (char*)key_b);

    default:
      //could accept custom behavior here
      return key_a == key_b;
  }
}

static unsigned int int_hash(void *key, unsigned int num_bins){
  int key_int = *(unsigned int*)key;
  return key_int % num_bins;
}

static unsigned int float_hash(void *key, unsigned int num_bins){
  //right now this is the same as int hash since they are the same size
  int key_int = *(unsigned int*)key;
  return key_int % num_bins;
}

static unsigned int str_hash(void *key, unsigned int num_bins){
  //uses djb2 hash function
  char *key_str = (char*)key;

  unsigned int hash = 5381;
  int c;
  while ((c = *key_str++)){
    hash = ((hash << 5) + hash) + c;
  }
  return hash % num_bins;
}

hashmap* hashmap_init(var_type key_type, var_type value_type){
  hashmap *hmap = malloc(sizeof(hashmap));
  if(hmap == NULL){
    printf("Error: could not allocate hashmap\n");
    return NULL;
  }

  hmap->num_bins = INIT_NUM_BINS;
  hmap->size = 0;
  hmap->key_type = key_type;
  hmap->value_type = value_type;
  hmap->bin_list = calloc(hmap->num_bins, sizeof(hash_entry*));

  if(hmap->bin_list == NULL){
    printf("Error: could not allocate bin_list\n");
    free(hmap);
    return NULL;
  }
  
  switch(key_type){
    case TYPE_INT: 
    case TYPE_CHAR:
      hmap->hash_func = int_hash;
      break;

    case TYPE_FLOAT:
      hmap->hash_func = float_hash;
      break;

    case TYPE_STRING:
      hmap->hash_func = str_hash;
      break;

    default:
      hmap->hash_func = NULL;
  }
  return hmap;
}

hashmap* hashmap_init_n(unsigned int num_bins, var_type key_type, var_type value_type){
  hashmap *hmap = malloc(sizeof(hashmap));
  if(hmap == NULL){
    printf("Error: could not allocate hashmap\n");
    return NULL;
  }

  hmap->num_bins = num_bins;
  hmap->size = 0;
  hmap->key_type = key_type;
  hmap->value_type = value_type;
  hmap->bin_list = calloc(hmap->num_bins, sizeof(hash_entry*));

  if(hmap->bin_list == NULL){
    printf("Error: could not allocate bin_list\n");
    free(hmap);
    return NULL;
  }
  
  switch(key_type){
    case TYPE_INT: 
    case TYPE_CHAR:
      hmap->hash_func = int_hash;
      break;

    case TYPE_FLOAT:
      hmap->hash_func = float_hash;
      break;

    case TYPE_STRING:
      hmap->hash_func = str_hash;
      break;

    default:
      hmap->hash_func = NULL;
  }
  return hmap;
}

void hashmap_free(hashmap *const hashmap){
  for(int i = 0; i < hashmap->num_bins; i++){
    hash_entry *prev;
    hash_entry *curr_entry = hashmap->bin_list[i];
    while(curr_entry){
      prev = curr_entry;
      curr_entry = curr_entry->next;
      hash_entry_free(prev);
    }
  }
  free(hashmap->bin_list);
  free(hashmap);
}

static hash_entry *hash_entry_init(hashmap *const hashmap, void *key, void *value){
  hash_entry* h = malloc(sizeof(hash_entry));
  if(h == NULL){
    printf("Could not allocate hash_entry\n");
    return NULL;
  }
  h->key = mem_dup(hashmap->key_type, key);
  h->value = mem_dup(hashmap->value_type, value);
  h->next = NULL;
  return h;
}

static void hash_entry_free(hash_entry *const h){
  free(h->key);
  free(h->value);
  free(h);
}

void hashmap_insert(hashmap *const hashmap, void *key, void *value){
  unsigned int bin = (hashmap->hash_func)(key, hashmap->num_bins);
  hash_entry* bin_head = hashmap->bin_list[bin];
  hash_entry* curr_entry = bin_head;
  while(curr_entry){
    //key found, update value
    if(keys_are_equal(hashmap, curr_entry->key, key)){
      curr_entry->value = mem_dup(hashmap->value_type, value);
      return;
    }
    curr_entry = curr_entry->next;
  }
  //key not found, add to beginning of list
  hash_entry *new_entry = hash_entry_init(hashmap, key, value);
  new_entry->next = bin_head; 
  hashmap->bin_list[bin] = new_entry;
}

void* hashmap_get(const hashmap *const hashmap, void *key){
  unsigned int bin = (hashmap->hash_func)(key, hashmap->num_bins);
  hash_entry* curr_entry = hashmap->bin_list[bin];
  while(curr_entry && !keys_are_equal(hashmap, key, curr_entry->key)){
    curr_entry = curr_entry->next;
  }
  if(!curr_entry) return NULL;
  return curr_entry->value;
}

void hashmap_print(const hashmap *const hashmap){
  for(int i = 0; i < hashmap->num_bins; i++){
    hash_entry *curr_entry = hashmap->bin_list[i];
    while(curr_entry){
      print_data(hashmap->key_type, hashmap->value_type, curr_entry);
      curr_entry = curr_entry->next;
    }
  }
}

//NOTE: can add custom print func support -> need initializer with fxns
static void print_data(const var_type key_type, const var_type value_type, const hash_entry *const h){
  void *key = h->key;
  void *value = h->value;
  switch(key_type){
    case TYPE_INT: 
      printf("key: %d ", *(int*)key);
      break;

    case TYPE_FLOAT:
      printf("key: %f ", *(float*)key);
      break;

    case TYPE_CHAR:
      printf("key: %c ", *(char*)key);
      break;

    case TYPE_STRING:
      printf("key: %s ", (char*)key);
      break;

    default:
      printf("key: unsupported type ");
      //potentially add custom print functionality
  }

  switch(value_type){
    case TYPE_INT:
      printf("value: %d\n", *(int*)value);
      break;

    case TYPE_FLOAT:
      printf("value: %f\n", *(float*)value);
      break;

    case TYPE_CHAR:
      printf("value: %c\n", *(char*)value);
      break;

    case TYPE_STRING:
      printf("value: %s\n", (char*)value);
      break;

    default:
      printf("value: unsupported type\n");
  }
}

void hashmap_remove(hashmap *const hashmap, void* key){
  unsigned int bin = (hashmap->hash_func)(key, hashmap->num_bins);
  hash_entry* prev_entry = NULL;
  hash_entry* curr_entry = hashmap->bin_list[bin];
  while(curr_entry && !keys_are_equal(hashmap, key, curr_entry->key)){
    prev_entry = curr_entry;
    curr_entry = curr_entry->next;
  }
  if(!curr_entry) return;
  if(prev_entry){
    prev_entry->next = curr_entry->next;
  } else {
    //first element in list
    hashmap->bin_list[bin] = curr_entry->next;
  }
  hash_entry_free(curr_entry);
}
