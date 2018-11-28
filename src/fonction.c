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
 * Le guichet travaille pendant 540 minutes. Ferme l'accès à 510 minutes. Offset 510 minutes;
 *
 * @author Marc NGUYEN
 * @author Mathieu POIGNANT
 * @date 17 Nov 2018
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "fonction.h"

const int MIN = 5;
const int MAX = 30;
const float LAMBDA = 0.1;
const int HEURE_ACCEPTE = 510;  // 510 minutes acceptés

/**
 * @brief Crée et ajoute un client à la liste.
 *
 * @param listeclients Liste des clients avec un pointeur HEAD.
 */
int creerClient(struct ListeClients* listeclients) {
    struct Client *nouvClient = (struct Client *)malloc(sizeof(struct Client));
    double U = (double)rand()/RAND_MAX;  // U prend une valeur entre [0, 1]
    int duree = rand() % (MAX + 1 - MIN) + MIN;  // duree prend un valeur entre [min, max]
    if (listeclients -> HEAD != NULL) {  // Cas : "Il existe un précédent"
        struct Client *dernierClient = listeclients -> HEAD;

        // Déplacement du curseur vers le dernier
        while (dernierClient -> suivant != NULL)
            dernierClient = dernierClient -> suivant;

        // Ajout de données
        nouvClient -> arrivee = dernierClient -> arrivee - (int)(log(1-U)/LAMBDA);
        if(dernierClient -> fin_service < nouvClient -> arrivee) {  // Cas : "Il n'attend pas"
            nouvClient -> attente = 0;
            nouvClient -> fin_service = nouvClient -> arrivee + duree;
        } else {
            nouvClient -> attente = dernierClient -> fin_service - nouvClient -> arrivee;
            nouvClient -> fin_service = dernierClient -> fin_service + duree;
        }

        // Append
        nouvClient -> suivant = NULL;
        nouvClient -> precedent = dernierClient;
        dernierClient -> suivant = nouvClient;
    } else {  // Cas : "Il n'existe pas un précédent"
        nouvClient -> arrivee = (int)(-log(1-U)/LAMBDA);
        nouvClient -> attente = 0;
        nouvClient -> fin_service = nouvClient -> arrivee + duree;
        nouvClient -> suivant = NULL;
        listeclients -> HEAD = nouvClient;
    }
    return nouvClient -> arrivee;
}


/**
 * @brief Créer la liste journalière.
 *
 * @return struct ListeClients* Liste des clients.
 */
struct ListeClients *creerListeJournaliere(void) {
    struct ListeClients *listeclients = (struct ListeClients *)malloc(sizeof(struct ListeClients));
    listeclients -> HEAD = NULL;
    int compteur = 0;
    while (creerClient(listeclients) < HEURE_ACCEPTE) compteur++;  // Créer un client jusqu'à HEURE_ACCEPTE
    printf("%i clients sont venus!\n", compteur);
    popClient(listeclients);  // Ejecte le dernier qui est > 510
    return listeclients;
}


/**
 * @brief Ejecte le dernier client de la liste.
 *
 * @param listeclients Liste des clients avec un pointeur HEAD.
 */
void popClient(struct ListeClients* listeclients) {
    struct Client *dernierClient = listeclients -> HEAD;
    while (dernierClient -> suivant != NULL)
        dernierClient = dernierClient -> suivant;
    dernierClient -> precedent -> suivant = NULL;
    free(dernierClient);
}
