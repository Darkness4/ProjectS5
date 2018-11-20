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
 * Le guichet travaille 510 minutes.
 * 
 * @author Marc NGUYEN
 * @author Mathieu POIGNANT
 * @date 17 Nov 2018
 */

#include "fonction.h"
#include <math.h>
#include <stdio.h>

const int min = 0;
const int max = 60;
const int lambda = 1;

void creerClient(struct ListeClients* listeclients) {
    struct Client *nouvClient = (struct Client *)malloc(sizeof(struct Client));
    double U = rand()/RAND_MAX;
    nouvClient -> duree = rand() % (max + 1 - min) + min;
    if (listeclients -> HEAD != NULL) {
        struct Client *curseur = listeclients -> HEAD;

        while (curseur -> suivant != NULL)
            curseur = curseur -> suivant;

        nouvClient -> arrivee = curseur -> arrivee - log(1-U)/lambda;
        nouvClient -> suivant = NULL;
        nouvClient -> precedent = curseur;
        curseur -> suivant = nouvClient;
    } else {
        nouvClient -> arrivee = -log(1-U)/lambda;
        nouvClient -> suivant = NULL;
        listeclients -> HEAD = nouvClient;
    }

}

/*int main(void)
{
    struct ListeClients *listeclients = (struct ListeClients *)malloc(sizeof(struct ListeClients));
    listeclients -> HEAD = NULL;

    creerClient(listeclients);
    creerClient(listeclients);
    return 0;
}*/

