/**
 * @file manip_fichier.c
 *
 * @brief Gère la liste journalières des clients et leurs informations.
 *
 * Crée et enregistre dans un fichier la liste journalières des clients et les
 * informations relatives à leur service (date d’arrivée, durée d’attente, date
 * du début de service, date de fin de service, etc.).
 *
 * Mesure aussi les métriques de performance.
 *
 * @author Marc NGUYEN
 * @author Mathieu POIGNANT
 * @date 17 Nov 2018
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "fonction.h"
#include "manip_fichier.h"

const int HEURE_FERMETURE = 540;  // Heure de fermeture


/**
 * @brief Rentre la liste des clients dans le fichier.
 *
 * @param listeclients Liste des clients avec un pointeur HEAD.
 */
void ecrireList(struct ListeClients *listeclients) {
  struct Client *curseur;
  FILE *fp = fopen("simulation.txt", "w");
  curseur = listeclients -> HEAD;

  // Tant qu'il reste des clients
  while(curseur != NULL) {
    int debut_serv = curseur -> arrivee + curseur -> attente;
    fprintf(fp, "%d %d %d %d\n", curseur -> arrivee,
                                 curseur -> attente,
                                 debut_serv,
                                 curseur -> fin_service);
    curseur = curseur -> suivant;
  }

  fclose(fp);
}


/**
 * @brief Retourne la taille moyenne de la file issu de simulation.txt.
 *
 * @return double Taille moyenne de la file.
 */
double fileMoy(void) {
  double file_moy;  // Moyenne à retourner
  int nPersonnes = 0;

  // Datas
  int arrivee;
  int attente;
  int debut_serv;
  int fin_serv;

  // Vérification de l'ouverture du fichier
  FILE *fp = fopen("simulation.txt", "r");
  if(fp == NULL) {
    printf("Fichier introuvable\n");
    exit(1);
  }

  // Calcul {nPersonnes} en attente pour chaque minute
  for(int i = 0; i <= HEURE_FERMETURE; i++) {
    while(fscanf(fp, "%d %d %d %d\n", &arrivee, &attente, &debut_serv, &fin_serv) == 4) {   // Tant qu'il reste des clients à compter dans la file
      if(debut_serv > i) {  // On ne regarde que ceux qui N'ONT PAS été servis
        if (arrivee < i)  // On ne compte que ceux qui SONT arrivées
          nPersonnes++;
        else break;  // Ces arrivants ne sont pas encore arrivées. Note: la liste est classé par date d'arrivée.
      }
    }  // Il y a {nPersonnes} en train d'attendre à cette minute {i}.

    // Réinitialisation
    fseek(fp, 0, SEEK_SET);
  }
  fclose(fp);
  file_moy = (double)nPersonnes / HEURE_FERMETURE; // Population/min

  return file_moy;
}


/**
 * @brief Retourne la taille moyenne de la file d'attente issu de simulation.txt.
 *
 * @return double Taille moyenne de la file d'attente.
 */
int fileMax(void) {
  int file_max = 0;  // Maximum à retourner
  int nPersonnes = 0;

  // Datas
  int arrivee;
  int attente;
  int debut_serv;
  int fin_serv;

  // Vérification de l'ouverture du fichier
  FILE *fp = fopen("simulation.txt", "r");
  if(fp == NULL) {
    printf("Fichier introuvable\n");
    exit(1);
  }

  // Calcul {nPersonnes} max en attente pour chaque minute
  for(int i = 0; i <= HEURE_FERMETURE; i++) {
    while(fscanf(fp, "%d %d %d %d\n", &arrivee, &attente, &debut_serv, &fin_serv) == 4) {  // Tant qu'il reste des clients à compter dans la file
      if(debut_serv > i) {  // On ne regarde que ceux qui N'ONT PAS été servis
        if (arrivee < i)  // On ne compte que ceux qui SONT arrivées
          nPersonnes++;
        else break;// Ces arrivants ne sont pas encore arrivées. Note: la liste est classé par date d'arrivée.
      }
    }  // Il y a {nPersonnes} en train d'attendre à cette minute {i}.
  
    // Réinitialisation
    fseek(fp, 0, SEEK_SET);
    if(nPersonnes > file_max) file_max = nPersonnes;  // Récupère le maximum.
    nPersonnes = 0;
  }
  fclose(fp);

  return file_max;
}


/**
 * @brief Retourne le débit moyen de la file d'attente issu de simulation.txt.
 *
 * @return double Débit moyen de la file d'attente.
 */
double debMoy(void) {
  int nbClients = 0;  // Nombre de clients total

  // Datas
  int arrivee;
  int attente;
  int debut_serv;
  int fin_serv;

  // Vérification de l'ouverture du fichier
  FILE *fp = fopen("simulation.txt", "r");
  if(fp == NULL) {
    printf("Fichier introuvable\n");
    exit(1);
  }

  // Calcul {nbClients} total
  while(fscanf(fp, "%d %d %d %d\n", &arrivee, &attente, &debut_serv, &fin_serv) == 4)
    nbClients++;
  fclose(fp);

  return (double)nbClients / HEURE_FERMETURE;  // Débit de clients moyen
}


/**
 * @brief Retourne le taux de clients non traitées de la file d'attente issu de simulation.txt.
 *
 * @return double Taux de clients non traitées de la file d'attente.
 */
double tauxTraite(void) {
  int nbClients = 0;
  int non_traites = 0;

  // Datas
  int arrivee;
  int attente;
  int debut_serv;
  int fin_serv;

  // Vérification de l'ouverture du fichier
  FILE *fp = fopen("simulation.txt", "r");
  if(fp == NULL) {
    printf("Fichier introuvable\n");
    exit(1);
  }

  // Calcul {non_traites}
  while(fscanf(fp, "%d %d %d %d\n", &arrivee, &attente, &debut_serv, &fin_serv) == 4) {
    nbClients++;
    if(fin_serv > HEURE_FERMETURE)   // Si il doit être traité après la fermeture
      non_traites++;
  }
  fclose(fp);

  return 1 - (double)non_traites / nbClients;  // Taux de clients non traités
}


/**
 * @brief Retourne le temps de réponse moyen de la file d'attente issu de simulation.txt.
 *
 * @return double Temps de réponse moyen de la file.
 */
double tempsRep(void) {
  int nbClients = 0;
  int temps_tot = 0;

  // Datas
  int arrivee;
  int attente;
  int debut_serv;
  int fin_serv;

  // Vérification de l'ouverture du fichier
  FILE *fp = fopen("simulation.txt", "r");
  if(fp == NULL) {
    printf("Fichier introuvable\n");
    exit(1);
  }

  // Calcul {temps_tot}
  while(fscanf(fp, "%d %d %d %d\n", &arrivee, &attente, &debut_serv, &fin_serv) == 4) {
    nbClients++;
    temps_tot += fin_serv - arrivee;
  }
  fclose(fp);

  return (double)temps_tot / nbClients;  // Temps de réponse moyen du guichet
}
