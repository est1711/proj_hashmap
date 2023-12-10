// hashmap.h
#ifndef HASHMAP_H
#define HASHMAP_H

#include "listechainee.h"
#include "abr.h" 

struct Noeud;
typedef struct Noeud Noeud;

/**
 * @brief defintion de la structure hashmap
 * 
 */
typedef struct {
    Noeud *root;
    int size;
} HashMap;

HashMap *createHM();
void afficherHashMap(HashMap *map);
int ajoutHashMap(HashMap *map, char *nom, int kills);
int removeHM(HashMap *map, char *nom);
int sizeHM(HashMap *map);
void viderhashmap(HashMap *map);

int dmdcreerjoueur(HashMap *map);

#endif