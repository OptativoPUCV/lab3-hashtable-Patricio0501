#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair **buckets;
    Pair **array;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
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
  if (map == NULL || key == NULL) {
        return; 
    }

    long index = hash(key, map->capacity);

    while (map->buckets[index] != NULL && (map->buckets[index]->key == NULL || strcmp(map->buckets[index]->key, key) != 0)) {
        index = (index + 1) % map->capacity;
    }

    if (map->buckets[index] == NULL) {
        Pair *newPair = (Pair *)malloc(sizeof(Pair));
        if (newPair == NULL) {
            perror("Error al alocar memoria para el nuevo par");
            exit(EXIT_FAILURE);
        }
        newPair->key = strdup(key);
        newPair->value = value;
        map->buckets[index] = newPair;
        map->size++;
    } else {
        return;
    }
    map->current = index;
}

void enlarge(HashMap * map) {
    enlarge_called = 1; 
   
    Pair **old_buckets = map->buckets;
    map->capacity *= 3;
    map->buckets = (Pair **)malloc(sizeof(Pair *) * map->capacity);
    map->size = 1;

    for (long i = 0; i < map->capacity / 2; i++) {
        Pair *currentPair = old_buckets[i];
        if (currentPair != NULL && currentPair->key != NULL) {
            insertMap(map, currentPair->key, currentPair->value);
        }
    }
    free(old_buckets);
}

HashMap *createMap(long capacity) {
    HashMap* map = (HashMap*)malloc(sizeof(HashMap));
    if (map == NULL) {
        perror("Error al alocar memoria para la tabla de hash");
        exit(EXIT_FAILURE);
    }

    map->buckets = (Pair**)malloc(sizeof(Pair*) * capacity);

    if (map->buckets == NULL) {
        perror("Error al alocar memoria para el arreglo de pares");
        exit(EXIT_FAILURE);
    }

    for (long i = 0; i < capacity; i++) {
        map->buckets[i] = NULL;
    }

    map->capacity = capacity;
    map->size = 0;
    map->current = -1;

    return map;
}

void eraseMap(HashMap * map, char * key) {
    long index = hash(key, map->capacity);
    long initialIndex = index;

    do {
        Pair *currentPair = map->buckets[index];

        if (currentPair != NULL && is_equal(currentPair->key, key)) {
            currentPair->key = NULL; 
            map->size--;
            return;
        }
        index = (index + 1) % map->capacity;
    } while (index != initialIndex); 
}


Pair * searchMap(HashMap * map, char * key) {
    long index = hash(key, map->capacity);
    long initialIndex = index;

    do {
        Pair *currentPair = map->buckets[index];

        if (currentPair == NULL) {
            map->current = -1;
            return NULL;
        }

        if (is_equal(currentPair->key, key)) {
            map->current = index;
            return currentPair;
        }

        index = (index + 1) % map->capacity;
    } while (index != initialIndex); 

    map->current = -1;
    return NULL;
}

Pair * firstMap(HashMap * map) {
    if (map == NULL && map->size == 0) {
        return NULL; 
    }

    for (long i = 0; i < map->capacity; i++) {
        Pair *currentPair = map->buckets[i];
        if (currentPair != NULL && currentPair->key != NULL) {
            map->current = i; 
            return currentPair;
        }
    }

    return NULL; 
}

Pair * nextMap(HashMap * map) {
    if (map == NULL && map->current == -1) {
        return NULL;
    }

    long currentIndex = map->current + 1;

    while (currentIndex < map->capacity) {
        Pair *currentPair = map->buckets[currentIndex];

        if (currentPair != NULL && currentPair->key != NULL) {
            map->current = currentIndex; 
            return currentPair;
        }
        currentIndex++;
    }

    map->current = -1; 
    return NULL;
}

