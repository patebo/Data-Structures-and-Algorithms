#ifndef _SIMAP_H
#define _SIMAP_H

typedef struct SIMapData* SIMap;

// out: an empty SIMap
SIMap sim_create();

// in: a SIMap
// side effect: the map is destroyed and all memory freed
void sim_destroy(SIMap M);

// in: a SIMap M, a key and a value.
// side effect: the key is bound to the value in M.
//   if the key was already in the map, the old association is removed.
void sim_set(SIMap M, char* key, int value);


// in: a SIMap M and a key.
// side effect: if the key k occurs in the map, it is removed.
void sim_remove(SIMap M, char* key);

// in: a SIMap M and a key k.
// out: -1 if key is not in M,
//      value if a binding (key,value) is in the map.
int sim_lookup(SIMap M, char* key);

// in: a SIMap M
// out: the number of bindings in the SIMap
int sim_size(SIMap M);


#endif
