#ifndef _fonction_h
#define _fonction_h

/**
 * @brief Modélisation d'un client.
 * 
 * On définit une liste chaînée puisque le guichet ne lit qu'un par un, et dans
 * l'ordre.
 * 
 * On utilise une variable arrivee afin de stocker la minute d'arrivée.
 * Il faut une variable fin_service, pour voir quand le guichet est occupé.
 * On utilise une variable attente, pour mesurer l'attente d'un client.
 * 
 * Un Client devra donc pointer sur le précédent afin de voir si le guichet est 
 * occupé per celui-ci.
 * 
 * Il pointera sur le suivant afin de pouvoir se déplacer dans la liste chaînée.
 * 
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


int creerClient(struct ListeClients* listeclients);
void popClient(struct ListeClients* listeclients);
struct ListeClients *creerListeJournaliere(void);

#endif  // _fonction_h
