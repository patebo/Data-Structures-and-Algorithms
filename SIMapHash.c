#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "SIMap.h"

typedef struct SIMapData* SIMap;
typedef struct ListNodeData* ListNode;

struct SIMapData {
  ListNode* table;
  int size;
  int alloc;
};

struct ListNodeData {
  char* key;
  int value;
  ListNode next;
};

unsigned int hash(char* s) {
  int h = 0;
  for (int i=0; s[i]!='\0'; i++) {
    h = h*31 + (int)s[i];
  }
  return h;
}
// out: an empty SIMap
SIMap sim_create() {
  SIMap M = (SIMap)malloc(sizeof(struct SIMapData));
  if (M==NULL) { printf("Allocation error\n"); exit(1); }
  M->table = (ListNode*)malloc(8000*sizeof(struct ListNodeData*));
  if (M->table==NULL) { printf("Allocation error\n"); exit(1); }
  M->size = 0;
  M->alloc = 8000;
  for (int i=0; i<M->alloc; i++) {
    M->table[i] = NULL;
  }
  return M;
}

// in: a SIMap
// side effect: the map is destroyed and all memory freed
void destroy_rec(ListNode* table, int alloc) {
  for (int i=0; i < alloc; i++) {
    while (table[i]!=NULL) {
      ListNode second_node = table[i]->next;
      free(table[i]);
      table[i] = second_node;
    }
  }
}
void sim_destroy(SIMap M) {
  destroy_rec(M->table,M->alloc);
  free(M->table);
  free(M);
}

// in: a SIMap M, a key and a value.
// side effect: the key is bound to the value in M.
//   if the key was already in the map, the old association is removed.
void sim_set(SIMap M, char* key, int value) {
  int alloc = M->alloc;
  int bucket = hash(key)%alloc;
  ListNode* ln = &(M->table[bucket]);
  while ((*ln) != NULL) {
    if (strcmp((*ln)->key, key)==0) {
      (*ln)->value = value;
      return;
    }
    else {
      ln = &((*ln)->next);
    }
  }
  ListNode new_node = (ListNode)malloc(sizeof(struct ListNodeData));
  new_node->key = key;
  new_node->value = value;
  new_node->next = NULL;
  *ln = new_node;
  M->size ++;
}


// in: a SIMap M and a key.
// side effect: if the key k occurs in the map, it is removed.
void sim_remove(SIMap M, char* key) {
    int alloc = M->alloc;
    int bucket = hash(key)%alloc;
    ListNode* ln = &(M->table[bucket]);
    while ((*ln) != NULL) {
      if (strcmp((*ln)->key, key)==0) {
        ListNode next_node = (*ln)->next;
        free((*ln));
        *ln = next_node;
        M->size --;
        return;
      }
      else {
        ln = &((*ln)->next);
      }
    }
    printf("Key is not in the map\n");
    return;
}

// in: a SIMap M and a key k.
// out: -1 if key is not in M,
//      value if a binding (key,value) is in the map.
int sim_lookup(SIMap M, char* key) {
  int alloc = M->alloc;
  int bucket = hash(key)%alloc;
  ListNode ln = M->table[bucket];
  while (ln != NULL) {
    //testing: print("key:%s\n",ln->key);
    if (strcmp(ln->key, key)==0) {return ln->value; }
    ln = ln->next;
  }
  return -1; //key not found
}

// in: a SIMap M
// out: the number of bindings in the SIMap
int sim_size(SIMap M) {
  return M->size;
}
