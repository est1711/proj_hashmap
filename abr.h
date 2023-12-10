// abr.h
#ifndef ABR_H
#define ABR_H

#include "listechainee.h"
#include "hashmap.h" 


/**
 * @brief definition de la structure noeud
 * 
 */
typedef struct Noeud {
    int a;
    Joueur *list;
    struct Noeud *left;
    struct Noeud *right;
} Noeud;


Noeud *ajouterJoueurABR(Noeud *noeud, char *nom, int kills, int *reponse);
void afficherJoueursABR(Noeud *noeud, HashMap *map);
Joueur *rechercherJoueur(Noeud *noeud, char *nom);
Noeud *findMin(Noeud *noeud);
Noeud *removeNoeud(Noeud *noeud) ;
Noeud *removeJoueurABR(Noeud *noeud, char *nom, int *removed);
Joueur *UpdateJoueur(Noeud *noeud, char *nom,int kills);
void viderNoeud(Noeud *noeud);
int sizeHMrecur(Noeud *noeud);

#endif // ABR_H