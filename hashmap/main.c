#include "hashmap.h"

int main(){
  hashmap* map = hashmap_init(TYPE_INT, TYPE_INT);
  int key1 = 8;
  int key2 = 9;
  int val1 = 10;
  int val2 = 11;
  hashmap_insert(map, &key1, &val1);
  hashmap_insert(map, &key2, &val2);
  printf("Printing map:\n");
  hashmap_print(map);

  hashmap* strmap = hashmap_init(TYPE_STRING, TYPE_STRING);
  hashmap_insert(strmap, "braden", "baller");
  hashmap_insert(strmap, "lebron", "james");
  hashmap_insert(strmap, "new_key", "new_value");
  printf("Printing strmap:\n");
  hashmap_print(strmap);

  hashmap* str_int_map = hashmap_init(TYPE_STRING, TYPE_INT);
  int nums[10];
  for(int i = 0; i < 10; i++) nums[i] = i;
  hashmap_insert(str_int_map, "Hello", &nums[3]);
  hashmap_insert(str_int_map, "Woah", &nums[9]);
  printf("Printing str_int_map:\n");
  hashmap_print(str_int_map);
  
  char* str = hashmap_get(strmap, "lebron");
  printf("lebron -> %s\n", str);

  str = hashmap_get(strmap, "braden");
  printf("braden -> %s\n", str);

  str = hashmap_get(strmap, "colts");
  if(str == NULL) printf("did not find key colts\n");

  str = hashmap_get(strmap, "braden");
  strcat(str, " and new msg");
  
  hashmap_print(strmap);

  hashmap_free(map);
  hashmap_free(strmap);
  hashmap_free(str_int_map);

  if (!map) return EXIT_FAILURE;
  printf("success\n");
  return EXIT_SUCCESS;
}
