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

#include "main.h"
#include "fonction.h"


int main(void)
{
  struct ListeClients *listeclients = (struct ListeClients *)malloc(sizeof(struct ListeClients));
  listeclients -> HEAD = NULL;

  creerClient(listeclients);
  creerClient(listeclients);

  return 0;
}
