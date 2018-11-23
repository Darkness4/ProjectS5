/**
 * @file manip_fichier.c
 * 
 * @brief Gère la liste journalières des clients et leurs informations.
 * 
 * Crée et enregistre dans un fichier la liste journalières des clients et les informations relatives à leur service (date d’arrivée, durée d’attente, date du début de service, date de fin de service, etc.).
 * 
 * Mesure aussi les métriques de performance.
 * 
 * @author Marc NGUYEN
 * @author Mathieu POIGNANT
 * @date 17 Nov 2018
 */

#include "manip_fichier.h"
struct Performance {
  double moy_file;
  int taille_max;
  double deb_moy;
  double taux_trait;
  double temps_reponse_moy;
}
