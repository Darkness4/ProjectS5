/** 
 * @dir src
 * @brief Dossier code source
 */

/**
 * @file main.c
 *
 * @brief Étude et simulation d’une file d’attente.
 *
 * Fichier principal.
 *
 * Fonctionnalités :
 * - Simulateur de guichet
 * - Analyse des performances
 *
 * @author Marc NGUYEN
 * @author Mathieu POIGNANT
 * @date 17 Nov 2018
 */

#include <stdlib.h>
#include <stdio.h>
#include "fonction.h"
#include "manip_fichier.h"
#include "tableau.h"
extern const char* FICHIER_DATA;
extern const char* FICHIER_TABLEAU;


/**
 * @brief Fonction main.
 */
int main(void) {
  printf("Bienvenue au simulateur de file d'attente.\n");

  printf("Simulation en cours...\n");
  struct ListeClients *listeclients = creerListeJournaliere();
  printf("Simulation terminé.\n");

  ecrireList(listeclients);
  printf("Résultats enregistrées dans %s.\n", FICHIER_DATA);

  ecrireTableau(fileMoy(), fileMax(), debMoy(), tauxNonTraites(), tempsRep());
  printf("Performances enregistrées dans %s.\n", FICHIER_TABLEAU);
  return 0;
}
