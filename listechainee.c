// liste_chainee.c
#include "abr.h"
#include "listechainee.h"
#include "hashmap.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief La fonction viderJoueur sert à libérer la mémoire allouée pour une liste de joueurs.
 * Elle parcourt la liste chaînée de joueurs et libère la mémoire associée à chaque joueur.
 * @param joueur Un pointeur vers le premier joueur de la liste à vider.
 */
void viderJoueur(Joueur *joueur) {
    while (joueur != NULL) {
        Joueur *suivant = joueur->next;
         // Libère la mémoire allouée pour le nom du joueur
        free(joueur->nom);
        // Libère la mémoire allouée pour le joueur
        free(joueur);
        joueur = suivant;
    }
}