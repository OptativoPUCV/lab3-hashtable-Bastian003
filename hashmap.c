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
  if(map ==NULL){
    return;
  }
  if(key ==NULL){
    return;
  }

  long indice= hash(key, map->capacity);
  while(map->buckets[indice]!= NULL && map->buckets[indice]->key != NULL){
    
    indice=(indice +1)%(map->capacity);
    
  }
  for(long i=0;i<map->capacity;i++){
    
    if(map->buckets[indice]!=NULL && is_equal(map->buckets[indice]->key,key)){
      return;
    }
    indice=(indice+1)%(map->capacity);
  }
  map->buckets[indice]=createPair(  key,   value);
  map->current=indice;
  map->size=map->size+1;
  

}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {

  HashMap* mapa=(HashMap*)malloc(sizeof(HashMap));
  if(mapa !=NULL){
    
    mapa->size=0;
    mapa->capacity=capacity;
    mapa->current=-1;
    mapa->buckets=(Pair**)malloc(sizeof(Pair*)* capacity);
    if(mapa->buckets !=NULL){
      
      return mapa;
    }
    return NULL;
  }else{
    
    return NULL;
  }
}

void eraseMap(HashMap * map,  char * key) {    
  if(map ==NULL){
    return;
  }
  if(key ==NULL){
    return;
  }
  long indice= hash(key, map->capacity);
  while(map->buckets[indice]!= NULL){
    if(is_equal(map->buckets[indice]->key,key)){
      map->buckets[indice]->key=NULL;
      map->size=map->size-1;
      return;
    }
    indice=(indice+1)%(map->capacity);
  }
  

}

Pair * searchMap(HashMap * map,  char * key) {
  if(map ==NULL){
    return NULL;
  }
  if(key ==NULL){
    return NULL;
  }
  long indice= hash(key, map->capacity);
  while(map->buckets[indice] !=NULL){
    if( is_equal(map->buckets[indice]->key,key)==1){
      map->current=indice;
      return map->buckets[indice];
    }
    indice=(indice+1)%(map->capacity);
  }
  return NULL;
  
}

Pair * firstMap(HashMap * map) {
  if(map ==NULL){
    return NULL;
  }
  if(map->buckets ==NULL){
    return NULL;
  }

  map->current=-1;
  return nextMap(map);
  return NULL;
}

Pair * nextMap(HashMap * map) {
  if(map ==NULL){
    return NULL;
  }
  if(map->buckets ==NULL){
    return NULL;
  }
  
  map->current=map->current+1;
  while(map->current < map->capacity){
    if(map->buckets[map->current]!=NULL && map->buckets[map->current]->key !=NULL){
      return map->buckets[map->current];

    }
    map->current=map->current+1;
  }
  return NULL;
}
