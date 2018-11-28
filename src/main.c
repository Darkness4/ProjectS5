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


int main(void) {
  struct ListeClients *listeclients = creerListeJournaliere();
  ecrireList(listeclients);
  int file_max = fileMax();
  double file_moy = fileMoy();
  double deb_moy = debMoy();
  double taux_traitement = tauxTraite();
  double temps_reponse_moy = tempsRep();
  // printf("%lf,%i,%lf,%lf,%lf\n", file_moy, file_max, deb_moy, taux_traitement, temps_reponse_moy);
  ecrireTableau(file_moy, file_max, deb_moy, taux_traitement, temps_reponse_moy);
  return 0;
}
