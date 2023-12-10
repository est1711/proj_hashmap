
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "abr.h"
#include "listechainee.h"
#include "hashmap.h"

/**
 * @brief fonction de hachage simple basée sur la longueur d'une chaîne de caractères.La fonction utilise la fonction strlen de la bibliothèque standard C pour calculer la longueur de la chaîne de caractères
 * 
 * @param nom Le nom du joueur pour lequel la fonction de hachage est calculée.
 * @return int 
 */
int hach(char *nom) {
    return strlen(nom);
}

/**
 * @brief La fonction ajouterJoueurABR a pour objectif d'ajouter un joueur à un ABR en respectant les règles de construction d'un ABR.
 * Elle prend en compte les clés de hachage et veille à ce qu'aucun joueur avec le même nom ne soit ajouté plus d'une fois
 * @param noeud  Le nœud actuel dans lequel on souhaite ajouter le joueur.
 * @param nom  Le nom du joueur à ajouter.
 * @param kills Le nombre de kills du joueur à ajouter.
 * @param reponse  Un pointeur vers une variable qui stocke si le joueur est ajouté avec succès, *reponse est mis à 1, sinon il est mis à 0.
 * @return Noeud* 
 */
Noeud *ajouterJoueurABR(Noeud *noeud, char *nom, int kills, int*reponse) {
    if (noeud == NULL) {
        Noeud *nouveauNoeud = (Noeud *)malloc(sizeof(Noeud));
        if (nouveauNoeud != NULL) {
            nouveauNoeud->a = hach(nom);

            Joueur *nouveauJoueur = (Joueur *)malloc(sizeof(Joueur));
            if (nouveauJoueur != NULL) {
                nouveauJoueur->nom = strdup(nom);
                nouveauJoueur->kills = kills;
                nouveauJoueur->next = NULL;

                nouveauNoeud->list = nouveauJoueur;
                nouveauNoeud->left = NULL;
                nouveauNoeud->right = NULL;
                *reponse= 1;
                return nouveauNoeud;
            } else {
                  //verification allocation memoire
                printf("Erreur lors de l'allocation mémoire pour le joueur\n");
                exit(1);
            }
        } else {
              //verification allocation memoire
            printf("Erreur lors de l'allocation mémoire pour le nœud ABR\n");
            exit(1);
        }
    }

    if (hach(nom) == noeud->a) {
        // Vérifier si le joueur avec le même nom existe déjà
        Joueur *actuel = noeud->list;
        while (actuel != NULL) {
            if (strcmp(actuel->nom, nom) == 0) {
                // Le joueur avec le même nom existe déjà, ne pas l'ajouter à nouveau
                *reponse= 0;
                return noeud;
            }
            actuel = actuel->next;
        }

        // Ajouter le joueur à la liste existante avec la même clé de hachage
        actuel = noeud->list;
        while (actuel->next != NULL) {
            actuel = actuel->next;
        }

        actuel->next = (Joueur *)malloc(sizeof(Joueur));
        if (actuel->next != NULL) {
            actuel->next->nom = strdup(nom);
            actuel->next->kills = kills;
            actuel->next->next = NULL;
            actuel = actuel->next;
        } else {
            //verification allocation memoire
            printf("Erreur lors de l'allocation mémoire pour le joueur\n");
            exit(1);
        }
    } else if (hach(nom) < noeud->a) {
        noeud->left = ajouterJoueurABR(noeud->left, nom, kills,reponse);
    } else {
        noeud->right = ajouterJoueurABR(noeud->right, nom, kills,reponse);
    }
    *reponse= 1;

    return noeud;
}

/**
 * @brief La fonction sizeHMrecur a pour objectif de calculer récursivement la taille totale de l'arbre, en tenant compte du nombre de joueurs présents dans chaque nœud.et récursivement calcule la taille des sous-arbres gauche et droit. Elle retourne la somme de ces valeurs, représentant la taille totale de l'arbre.
 * 
 * @param noeud Le nœud à partir duquel la fonction commence à calculer la taille 
 * @return int 
 */
int sizeHMrecur(Noeud *noeud) {
    if (noeud == NULL) {
        return 0;
    }
    // Calculer la taille des sous-arbres 
    int sizeLeft = sizeHMrecur(noeud->left);
    int sizeRight = sizeHMrecur(noeud->right);
    Joueur *present = noeud->list;
    int joueurdsnoeud = 0;
    while (present != NULL) {
        joueurdsnoeud++;
        present = present->next;
    }

    return sizeLeft + sizeRight + joueurdsnoeud;
}




/**
 * @brief fonction recursive qui affiche les joueurs de la hashmap
 * 
 * @param noeud Le nœud à partir duquel la fonction commence à afficher les joueurs
 * @param map Un pointeur vers la structure HashMap.
 */
void afficherJoueursABR(Noeud *noeud, HashMap *map) {
    if (noeud != NULL) {
        afficherJoueursABR(noeud->left, map);
        printf("Nombre du noeud : %d:\n", noeud->a);

        Joueur *actuel = noeud->list;
        while (actuel != NULL) {
            printf("Nom du joueur : %s, Kills : %d\n", actuel->nom, actuel->kills);
            actuel = actuel->next;
        }

        afficherJoueursABR(noeud->right, map);
    }
}



/**
 * @brief c'est une fonction récursive pour parcourir l'arbre en fonction de la clé de hachage du nom. Si elle trouve un nœud avec la même clé de hachage, elle parcourt la liste chaînée associée pour trouver le joueur avec le même nom. Si le joueur est trouvé, un pointeur vers le joueur est retourné ; sinon, la fonction retourne NULL.
 * 
 * @param noeud Le nœud à partir duquel la fonction commence la recherche.
 * @param nom  Le nom du joueur recherché.
 * @return Joueur* 
 */
Joueur *rechercherJoueur(Noeud *noeud, char *nom) {
    if (noeud == NULL) {
        // le joueur n'existe pas
        return NULL;
    }
   //le hachage du nom recherché correspond au noeud 
    if (hach(nom) == noeud->a) {
        // Recherche les joueurs associée à ce nœud
        Joueur *parcouru = noeud->list;
        while (parcouru != NULL) {
            //compare les chaines de cara 
            if (strcmp(parcouru->nom, nom) == 0) {
                // Le joueur avec le même nom a été trouvé
                return parcouru;
            }
            parcouru = parcouru->next;
        }
        } else if (hach(nom) < noeud->a) {
    // Si la longueur du nom est inférieure à l actuel, recherche à gauche
    return rechercherJoueur(noeud->left, nom);
} else {
    // Si la longueur du nom est supérieure à l actuel, recherche à droite
    return rechercherJoueur(noeud->right, nom);
}
    return NULL;
}


/**
 * @brief Fonction pour trouver le nœud minimum dans un sous-arbre, La fonction utilise une boucle pour traverser les nœuds les plus à gauche jusqu'à atteindre le nœud le plus à gauche du sous-arbre. Elle retourne ce nœud qui est le minimum.
 * 
 * @param noeud Le nœud à partir duquel la recherche du nœud minimum commence.
 * @return Noeud* 
 */
Noeud *findMin(Noeud *noeud) {
    while (noeud->left != NULL) {
        noeud = noeud->left;
    }
    return noeud;
}


/**
 * @brief La fonction removeNoeud a pour objectif de supprimer un nœud de l'ABR tout en maintenant l'ordre de l'arbre. La fonction traite quatre cas différents en fonction des enfants du nœud à supprimer.Elle renvoie le nœud ou son successeur après suppression.
 * 
 * @param noeud Le nœud à supprimer.
 * @return Noeud* 
 */
Noeud *removeNoeud(Noeud *noeud) {
    if (noeud->left == NULL && noeud->right == NULL) {
        // Cas 1: Le nœud n'a pas d'enfants, ca supprime et retourne null
        free(noeud);
        return NULL;
    } else if (noeud->left == NULL) {
        // Cas 2: Le nœud a un enfant à droite
        //on 'saute' le noeud
        Noeud *droit = noeud->right;
        free(noeud);
        return droit;
    } else if (noeud->right == NULL) {
        // Cas 3: Le nœud a un enfant à gauche
        //meme principe que enfant a droite
        Noeud *gauche = noeud->left;
        free(noeud);
        return gauche;
    } else {
        // Cas 4: Le nœud a deux enfants
        //cherche successeur copie ses données ect recursivement
        //permet de maintenir l ordre de l ABR 
        Noeud *successeur = findMin(noeud->right);
        noeud->a = successeur->a;
        noeud->list = successeur->list;
        noeud->right = removeNoeud(noeud->right);
        return noeud;
    }
}



/**
 * @brief c'est une fonction pour supprimer un joueur, elle est récursive pour parcourir l'arbre en fonction de la clé de hachage du nom. Si elle trouve le joueur dans la liste chaînée associée, elle le supprime et met à jour le pointeur du nœud. Si la liste chaînée devient vide après la suppression, elle appelle removeNoeud pour supprimer le nœud. La fonction met à jour la variable *removed en conséquence.
 * 
 * @param noeud Le nœud à partir duquel la fonction commence à chercher le joueur à supprimer.
 * @param nom  Le nom du joueur à supprimer.
 * @param removed Un pointeur vers une variable qui indique si le joueur a été supprimé (1) ou non (0).
 * @return Noeud* 
 */
Noeud *removeJoueurABR(Noeud *noeud, char *nom, int *removed) {
    if (noeud == NULL) {
        // Le joueur n'a pas été trouvé
        *removed = 0;
        return NULL;
    }

    if (hach(nom) == noeud->a) {
        // Recherche les joueurs avec hachage associés à ce nœud
        Joueur *actuel = noeud->list;
        Joueur *precedent = NULL;

        // Parcourir la liste chainée pour trouver le joueur
        while (actuel != NULL) {
            if (strcmp(actuel->nom, nom) == 0) {
                // Le joueur a été trouvé dans la liste chainée
                if (precedent == NULL) {
                    // Cas 1: Le joueur est le premier de la liste chainée
                    //on 'saute' le joueur 
                    Joueur *suivant = actuel->next;
                    free(actuel);
                    noeud->list = suivant;
                    *removed = 1;
                } else {
                    // Cas 2: Le joueur n'est pas le premier on relie celui d avant a celui d apres 
                    precedent->next = actuel->next;
                    free(actuel);
                    *removed = 1;
                }
                break;
            }
            precedent = actuel;
            actuel = actuel->next;
        }

        // Si la liste chainée est vide après la suppression
        // on appelle la fonction pour qu elle supprime le noeud 
        if (noeud->list == NULL) {
            Noeud *successeur = removeNoeud(noeud);
            return successeur;
        }
        //si on est pas dans le bon noeud, on parcourt les prochains noeud
    } else if (hach(nom) < noeud->a) {
        noeud->left = removeJoueurABR(noeud->left, nom, removed);
    } else {
        noeud->right = removeJoueurABR(noeud->right, nom, removed);
    }

    return noeud;
}


/**
 * @brief La fonction UpdateJoueur a pour objectif de mettre à jour le nombre de kills d'un joueur dans l'ABR.La fonction est récursive pour parcourir l'arbre en fonction de la clé de hachage du nom. Si elle trouve le joueur dans la liste chaînée associée, elle met à jour le nombre de kills du joueur.

 * 
 * @param noeud  Le nœud à partir duquel la fonction commence à chercher le joueur à mettre à jour.
 * @param nom  Le nom du joueur à mettre à jour.
 * @param kills Le nouveau nombre de kills.
 * @return Joueur* 
 */
Joueur *UpdateJoueur(Noeud *noeud, char *nom,int kills){
     if (noeud == NULL) {
        // le joueur n'existe pas
        return NULL;
    }
   //le hachage du nom recherché correspond au noeud 
    if (hach(nom) == noeud->a) {
        // Recherche les joueurs associée à ce nœud
        Joueur *parcouru = noeud->list;
        while (parcouru != NULL) {
            //compare les chaines de cara 
            if (strcmp(parcouru->nom, nom) == 0) {
                // Le joueur avec le même nom a été trouvé
                parcouru->kills = kills;
            }
            parcouru = parcouru->next;
        }
        } else if (hach(nom) < noeud->a) {
    // Si la longueur du nom est inférieure à l actuel, recherche à gauche
    return UpdateJoueur(noeud->left, nom,kills);
} else {
    // Si la longueur du nom est supérieure à l actuel, recherche à droite
    return UpdateJoueur(noeud->right, nom,kills);
}
    return NULL;
}

/**
 * @brief La fonction viderNoeud a pour objectif de libérer la mémoire associée à tous les nœuds de l'ABR et de leurs joueurs.La fonction est récursive pour parcourir l'arbre en effectuant un parcours suffixe (gauche, droit, nœud). Pour chaque nœud, elle appelle la fonction viderJoueur pour libérer la mémoire de la liste chaînée de joueurs, puis elle libère la mémoire du nœud lui-même.
 * 
 * @param noeud Le nœud à partir duquel la fonction commence à libérer la mémoire.
 */
void viderNoeud(Noeud*noeud){
    if (noeud!=NULL){
        viderNoeud(noeud->left);
        viderNoeud(noeud->right);
        viderJoueur(noeud->list);
        free(noeud);
    }
}
