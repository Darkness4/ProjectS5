/**
 * @file fonction.c
 *
 * @brief Simulateur de guichet.
 *
 * Fonctions permettant de faire simuler le fonctionnement d'un guichet.
 *
 * 1. Créer la liste journalière de clients;
 * 2. Initialiser la date d’arrivée, la durée d’attente et la date de la fin de
 * service de chacun des clients.
 *
 * Les dates sont des entiers indiquant des minutes.
 *
 * Le principe suivant permet de générer des réalisations d’une variable
 * aléatoire X obéissant à une loi exponentielle : si U ∼ [0, 1], alors
 * X = −ln(1 − U )/λ.
 *
 * Pour information, la fonction rand() retourne un nombre pseudo-aléatoire 
 * (de type int) compris entre 0 et RAND_MAX.
 *
 * Le guichet travaille pendant 540 minutes (17h30-8h30).
 * Ferme l'accès à 510 minutes (17h-8h30).
 * Offset 510 minutes (8h30).
 *
 * @author Marc NGUYEN
 * @author Mathieu POIGNANT
 * @date 17 Nov 2018
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "fonction.h"

/**
 * @brief duree prend un valeur entre [MIN, MAX] suivant la loi uniforme.
 */
const int MIN = 5;
/**
 * @brief duree prend un valeur entre [MIN, MAX] suivant la loi uniforme.
 */
const int MAX = 10;
/**
 * @brief Constante de la loi exponentielle.
 * 
 * L'arrivée d'un client suit la loi exponentielle.
 * Le principe suivant permet de générer des réalisations d’une variable
 * aléatoire X obéissant à une loi exponentielle : si U ∼ [0, 1], alors
 * X = −ln(1 − U )/λ.
 */
const float LAMBDA = 0.1;
/**
 * @brief Heure en minutes de fermeture de l'accès.
 */
const int MINUTE_ACCEPTE = 510;

/**
 * @brief Crée et ajoute un client à la liste.
 * 
 * Etapes:
 * - Allocation de mémoire ;
 * - Initialise les probabilités ;
 * - Ajoute un Client à la liste chaîné ListeClients ;
 *
 * Avant d'ajouter un Client, on identifie le cas : "Somme-nous en phase init?"
 * L'ajout d'un Client nécessite 3 variables et 2 pointeurs :
 * - arrivee = offset + (-log(1-U)/LAMBDA) ; avec U ∼ [0, 1]
 * - fin_service = durée + arrivee ;
 * - attente = fin_service de Client précédent - arrivee du nouveau Client
 * - suivant = NULL ;
 * - précédent = dernierClient ;
 *
 * @param listeclients Liste des clients avec un pointeur HEAD.
 */
int creerClient(struct ListeClients* listeclients) {
    struct Client *nouvClient = (struct Client *)malloc(sizeof(struct Client));
    double U = (double)rand()/RAND_MAX;  // U prend une valeur entre [0, 1]
    int duree = rand() % (MAX + 1 - MIN) + MIN;  // duree prend un valeur entre [MIN, MAX]
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
 * Génère des clients en répétant l'appel creerClient. 
 * Comme creerClient retourne la minute d'arrivée du dernier Client, on peut en
 * créer tant que arrivee < MINUTE_ACCEPTE (heure où les clients peuvent 
 * toujours rentrer).
 * 
 * On éjecte le dernier, car il dépasse MINUTE_ACCEPTE.
 * 
 * @return struct ListeClients* Liste des clients.
 */
struct ListeClients *creerListeJournaliere(void) {
    struct ListeClients *listeclients = (struct ListeClients *)malloc(sizeof(struct ListeClients));
    listeclients -> HEAD = NULL;
    int compteur = 0;
    while (creerClient(listeclients) < MINUTE_ACCEPTE) compteur++;  // Créer un client jusqu'à MINUTE_ACCEPTE
    printf("%i clients sont venus!\n", compteur);
    popClient(listeclients);  // Ejecte le dernier qui est > 510
    return listeclients;
}


/**
 * @brief Ejecte le dernier client de la liste.
 *
 * On restaure les pointeurs et on libère la mémoire.
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
