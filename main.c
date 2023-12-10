#include "abr.h"
#include "listechainee.h"
#include "hashmap.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Fonction main qui creer une hashmap fracture,
  ajoute des joueurs a cette hashmap, 
  affiche la hashmap,
  modifie les données de un joueur
  recherche un joueur dans la hashmap pour voir il existe et renvoie si il a trouvé ou non
  supprime un joueur de la hashmap 
  puis re affiche la hashmap
 * 
 * @return int 
 */
int main() {

    //creation Hashmap
    HashMap *fracture = createHM(); 

    //propose a l utilisateur de creer un joueur 
    dmdcreerjoueur(fracture);

    //ajout manuellement de plusieurs joueurs 
    ajoutHashMap(fracture,"Mario", 25);
    ajoutHashMap(fracture,"Zak", 10);
    ajoutHashMap(fracture,"Stel", 15);
    ajoutHashMap(fracture,"Liam", 20);
    ajoutHashMap(fracture,"Rayen", 15);
    ajoutHashMap(fracture,"ilian", 24);
    ajoutHashMap(fracture,"Kienson", 23);
    ajoutHashMap(fracture,"Alesky", 18);

    //afficher la hashmap avec les differents joueurs qui ont été ajouté 
    afficherHashMap(fracture);

    //modifie données de mon joueur
    UpdateJoueur(fracture->root,"Mario",35);

    // recherche un joueur et l affiche
    Joueur *joueurTrouve = rechercherJoueur(fracture->root, "Mario");
     if (joueurTrouve != NULL) {
        printf("Joueur modifié: - Nom : %s, Kills : %d\n", joueurTrouve->nom, joueurTrouve->kills);
    } else {
        printf("Le joueur n'a pas été trouvé.\n");
    }
    // supprime un joueur 
     int removed = removeHM(fracture, "ilian");
    if (removed) {
        printf("Le joueur a été supprimé.\n");
    } else {
        printf("Le joueur n'a pas été trouvé.\n");
    }
     printf("                          \n");
    
    afficherHashMap(fracture);
    viderhashmap(fracture);
    return 0;
}