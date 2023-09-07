#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
    Pair *buckets_block;
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {


}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap *createMap(long capacity) {
     HashMap *map = (HashMap *)malloc(sizeof(HashMap));

    if (map == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria para el mapa.\n");
        exit(1);
    }

    map->size = capacity;
    map->current = -1;

    // Inicializar el arreglo de casillas con punteros nulos
    map->buckets = (Pair **)malloc(sizeof(Pair *) * capacity);

    if (map->buckets == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria para el arreglo de casillas.\n");
        free(map);
        exit(1);
    }

    for (int i = 0 ; i < capacity ; i++){
      map->buckets[i] = (Pair *)malloc(sizeof(Pair));

      if (map->buckets[i] == NULL){
        fprintf(stderr, "Error: No se pudo asignar memoria para una casilla.\n");
        for (int j = 0; j < i; j++){
          free(map->buckets[j]);
        }
        free(map->buckets);
        free(map);
        exit(1);
      }
    }
  return map;
}

void eraseMap(HashMap * map,  char * key) {    


}

Pair * searchMap(HashMap * map,  char * key) {   


    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
