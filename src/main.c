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


/**
 * @brief Modélisation d'un client.
 * 
 */
struct client{
  /**
   * @brief Pointeur vers client suivant.
   * 
   */
  struct client *suivant;
  /**
   * @brief Minute d'arrivée.
   * 
   */
  int arrivee;
};

int main(void)
{
    return 0;
}
