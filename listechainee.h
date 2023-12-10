// liste_chainee.h
#ifndef LISTE_h
#define LISTE_h

#include "abr.h"
#include "hashmap.h" 

/**
 * @brief defintion de la structure joueur
 * 
 */
typedef struct Joueur {
    char *nom;
    int kills;
    struct Joueur *next;
} Joueur;

void viderJoueur(Joueur *joueur);

#endif