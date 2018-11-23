/**
 * @file fonction.c
 *
 * @brief Simulateur de guichet.
 *
 * Fonctions permettant de faire simuler le fonctionnement d'un guichet.
 *
 * 1. Créer la liste journalière de clients;
 * 2. Initialiser la date d’arrivée, la durée d’attente et la date de la fin de service de chacun des clients.
 *
 * Les dates sont des entiers indiquant des minutes.
 *
 * Le principe suivant permet de générer des réalisations d’une variable aléatoire X obéissant à une loi exponentielle : si U ∼ [0, 1], alors X = −ln(1 − U )/λ.
 *
 * Pour information, la fonction rand() retourne un nombre pseudo-aléatoire (de type int) compris entre 0 et RAND_MAX.
 *
 * Le guichet travaille au 510 minutes.
 *
 * @author Marc NGUYEN
 * @author Mathieu POIGNANT
 * @date 17 Nov 2018
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "fonction.h"

const int MIN = 0;
const int MAX = 60;
const int LAMBDA = 2;


/**
 * @brief Crée et ajoute un client à la liste.
 *
 * @param listeclients Liste des clients avec un pointeur HEAD.
 */
void creerClient(struct ListeClients* listeclients) {
    struct Client *nouvClient = (struct Client *)malloc(sizeof(struct Client));
    double U = (double)rand()/RAND_MAX;  // U prend une valeur entre [0, 1]
    int duree = rand() % (MAX + 1 - MIN) + MIN;  // duree prend un valeur entre [min, max]
    if (listeclients -> HEAD != NULL) {  // Cas : "Il existe un précédent"
        struct Client *dernierClient = listeclients -> HEAD;

        // Déplacement du curseur vers le derner
        while (dernierClient -> suivant != NULL)
            dernierClient = dernierClient -> suivant;

        // Ajout de données
        nouvClient -> arrivee = dernierClient -> arrivee - (int)(log(1-U)/LAMBDA);
        //vérification d'une attente du client
        if(dernierClient->fin_service < nouvClient->arrivee){
          nouvClient->attente=0;
          nouvClient->fin_service=nouvClient->arrivee+duree;
        }

        else{
        nouvClient -> attente = dernierClient -> fin_service - nouvClient -> arrivee;
        nouvClient -> fin_service = dernierClient->fin_service + durée;}

        // Append
        nouvClient -> suivant = NULL;
        nouvClient -> precedent = dernierClient;
        dernierClient -> suivant = nouvClient;
    } else {
        nouvClient -> arrivee = (int)(-log(1-U)/LAMBDA);
        nouvClient -> fin_service = nouvClient -> arrivee + duree;
        nouvClient -> suivant = NULL;
        listeclients -> HEAD = nouvClient;
    }
}


// Tests
/*int main(void)
{
    struct ListeClients *listeclients = (struct ListeClients *)malloc(sizeof(struct ListeClients));
    listeclients -> HEAD = NULL;

    creerClient(listeclients);
    creerClient(listeclients);
    return 0;
}*/
