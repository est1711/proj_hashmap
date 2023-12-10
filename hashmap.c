#include "abr.h"
#include "listechainee.h"
#include "hashmap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/**
 * @brief a fonction removeHM a pour objectif de supprimer un joueur de la HashMap.
 * Elle utilise la fonction removeJoueurABR pour effectuer la suppression dans l'ABR associé à la HashMap.
 * @param map Un pointeur vers la HashMap dans laquelle le joueur doit être supprimé.
 * @param nom Le nom du joueur à supprimer.
 * @return int Si la suppression a réussi, la fonction renvoie 1, sinon elle renvoie 0.
 */

int removeHM(HashMap *map, char *nom) {
    //verifie si hashmap vide ou si noeud racine null
    if (map == NULL || map->root == NULL) {
        // La HashMap est vide
        return 0;
    }
    //&removed sert savoir si la suppression a reussi
    int removed = 0;
    map->root = removeJoueurABR(map->root, nom, &removed);
    if (removed) {
        map->size--;
        return 1;  // Le joueur a été supprimé
    } else {
        return 0;  // Le joueur n'a pas été trouvé
    }
}


/**
 * @brief La fonction createHM a pour objectif de créer une nouvelle HashMap et d'initialiser ses paramètres à zéro.
 * @return HashMap* Un pointeur vers la nouvelle HashMap créée.
 * 
 */
HashMap* createHM() {
    HashMap *map = (HashMap *)malloc(sizeof(HashMap));
    if (map != NULL) {
        map->root = NULL;
        map->size = 0;
        return map;
    } else {
          //verification allocation memoire
        printf("Erreur lors de l'allocation mémoire pour la HashMap\n");
        exit(1);
    }
}


 /**
 @brief La fonction sizeHM a pour objectif de calculer la taille de la HashMap.
 * Elle appelle une fonction récursive sizeHMrecur pour compter le nombre de nœuds dans l'ABR associé à la HashMap.
 * @param map Un pointeur vers la HashMap dont on calcule la taille.
 * @return int La taille de la HashMap (nombre de joueurs).
  */
int sizeHM(HashMap *map) {
    if (map == NULL || map->root == NULL) {
        return 0;
    }
    return sizeHMrecur(map->root);
}


/**
 * @brief@brief La fonction afficherHashMap a pour objectif d'afficher la HashMap dans le terminal.
 * Elle utilise la fonction afficherJoueursABR pour afficher les joueurs présents dans l'ABR associé à la HashMap.
 * @param map Un pointeur vers la HashMap à afficher.
 */
void afficherHashMap(HashMap *map) {
    printf("Affichage de la HashMap :\n");
    printf("Affichage des joueurs de la HashMap:\n");
    afficherJoueursABR(map->root, map);
    printf("La taille de la HashMap:%d\n", sizeHM(map));

}

/**
 *@brief La fonction ajoutHashMap a pour objectif d'ajouter un joueur à la HashMap.
 * Elle utilise la fonction ajouterJoueurABR pour effectuer l'ajout dans l'ABR associé à la HashMap.
 * @param map Un pointeur vers la HashMap dans laquelle le joueur doit être ajouté.
 * @param nom Le nom du joueur à ajouter.
 * @param kills Le nombre de kills du joueur à ajouter.
 * @return int Si l'ajout a réussi, la fonction renvoie 1, sinon elle renvoie 0.
 */
int ajoutHashMap(HashMap *map, char *nom, int kills) {
    int ok = 0; 
    map->root = ajouterJoueurABR(map->root, nom, kills, &ok);
    if (ok != 0) {
        map->size++; 
        return 1;     //  l'ajout a réussi
    } else {
        return 0;     // Il'ajout a échoué
    }
}




/**
 * @brief La fonction viderhashmap a pour objectif de vider la HashMap et de libérer la mémoire associée.
 * Elle utilise la fonction viderNoeud pour libérer la mémoire de tous les nœuds de l'ABR associé à la HashMap.
 * @param map Un pointeur vers la HashMap à vider.
 */
void viderhashmap(HashMap*map){
    viderNoeud(map->root);
    map->root=NULL;
    map->size=0;
}


/**
 * @brief La fonction dmdcreerjoueur a pour objectif de créer un joueur en demandant à l'utilisateur s'il souhaite en créer un.
 * Si l'utilisateur répond "oui", il est invité à entrer le nom et le nombre de kills du joueur, puis le joueur est ajouté à la HashMap.
 * @param map Un pointeur vers la HashMap dans laquelle le joueur doit être ajouté.
 * @return int Si le joueur a été créé avec succès, la fonction renvoie 1, sinon elle renvoie 0.
 */
int dmdcreerjoueur(HashMap *map) {
    char reponse[3];
    printf("Voulez-vous créer un joueur ? (oui/non): ");
    scanf("%s", reponse);

    if (strcmp(reponse, "oui") == 0) {
        char nom[50];
        int kills;

        printf("Entrez le nom du joueur : ");
        scanf("%s", nom);

        printf("Entrez le nombre de kills : ");
        scanf("%d", &kills);

        // Créer le joueur directement dans ajouterJoueurABR
        int ok=0;
        map->root = ajouterJoueurABR(map->root, nom, kills,&ok);
        if(ok != 0){
            map->size++;
        }
        // Retourner le joueur créé (ou NULL si une erreur s'est produite)
        return ok;
    } else {
        return 0;
    }
}
