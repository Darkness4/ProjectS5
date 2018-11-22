#ifndef _fonction_h
#define _fonction_h

/**
 * @brief Modélisation d'un client.
 */
struct Client{
  /**
   * @brief Pointeur vers client suivant.
   */
  struct Client *suivant;
  /**
   * @brief Pointeur vers client précédent.
   */
  struct Client *precedent;
  /**
   * @brief Date d'arrivée en minute.
   */
  int arrivee;
  /**
   * @brief Date de fin du service en minute.
   */
  int fin_service;
  /**
   * @brief Durée d'attente.
   */
  int attente;
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

// Prototypes
// ----------
void creerClient(struct ListeClients* listeclients);

#endif  // _fonction_h
