#ifndef _fonction_h
#define _fonction_h

#include <stdlib.h>
// Prototypes
// ----------
/**
 * @brief Modélisation d'un client.
 * 
 */
struct Client{
  /**
   * @brief Pointeur vers client suivant.
   * 
   */
  struct Client *suivant;
  struct Client *precedent;
  /**
   * @brief Minute d'arrivée.
   * 
   */
  int arrivee;
  int duree;
};


/**
 * @brief Liste des Clients.
 * 
 * Store la liste des clients. 
 * HEAD est la tête et doit pointer vers NULL lors de l'initialisation.
 * Il doit ensuite pointer sur le Client suivant.
 */
struct ListeClients {
    /**
     * @brief HEAD est la tête.
     * 
     * Il doit pointer vers NULL lors de l'initialisation.
     * Il doit ensuite pointer sur le Client suivant.
     */
    struct Client* HEAD;
};

void creerClient(struct ListeClients* listeclients) 

#endif  // _fonction_h
