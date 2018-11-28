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



int main(void) {
  struct ListeClients *listeclients;
  int file_max;
  double file_moy;
  double deb_moy;
  double taux_traitement;
  double temps_reponse;
  listeclients = creerListeJournaliere();
  ecrireList(listeclients);
  file_max = fileMax();
  file_moy = fileMoy();
  deb_moy = debMoy();
  taux_traitement = tauxTraite();
  temps_reponse = tempsRep();
  printf("%d,%f,%f,%f,%f\n", file_max, file_moy, deb_moy, taux_traitement, temps_reponse);
  return 0;
}
