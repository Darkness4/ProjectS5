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
 * @author Marc NGUYEN
 * @author Mathieu POIGNANT
 * @date 17 Nov 2018
 */

#include "fonction.h"
