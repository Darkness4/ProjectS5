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

const int HEURE_FERMETURE = 540;  // Heure de fermeture du guichet
const int OFFSET_TRAVAIL_H = 8;  // 510 = 8h30
const int OFFSET_TRAVAIL_MIN = 30;
const char* FICHIER_DATA = "Simulation.txt";


/**
 * @brief Convertit les Minutes en Heure et retourne le reste.
 * 
 * @param minutes_to_hour Minutes convertit en Heure.
 * @return int Minutes restantes.
 */
int convert_Minutes_to_Hour(int *minutes_to_hour) {
  int minutes = *minutes_to_hour%60;
  *minutes_to_hour /= 60;
  return minutes;
}


/**
 * @brief Rentre la liste des clients dans le fichier.
 *
 * @param listeclients Liste des clients avec un pointeur HEAD.
 */
void ecrireList(struct ListeClients *listeclients) {
  struct Client *curseur;
  FILE *fp = fopen(FICHIER_DATA, "w");
  curseur = listeclients -> HEAD;

  // Tant qu'il reste des clients
  while(curseur != NULL) {
    int arrivee_h = curseur -> arrivee;
    int arrivee_min = convert_Minutes_to_Hour(&arrivee_h);
    int attente_h = curseur -> attente;
    int attente_min = convert_Minutes_to_Hour(&attente_h);
    int debut_service_h = curseur -> arrivee + curseur -> attente;
    int debut_service_min = convert_Minutes_to_Hour(&debut_service_h);
    int fin_service_h = curseur -> fin_service;
    int fin_service_min = convert_Minutes_to_Hour(&fin_service_h);

    fprintf(fp, "%02d:%02d %02d:%02d %02d:%02d %02d:%02d\n", arrivee_h+OFFSET_TRAVAIL_H, arrivee_min+OFFSET_TRAVAIL_MIN,
                                                             attente_h, attente_min,
                                                             debut_service_h+OFFSET_TRAVAIL_H, debut_service_min+OFFSET_TRAVAIL_MIN,
                                                             fin_service_h+OFFSET_TRAVAIL_H, fin_service_min+OFFSET_TRAVAIL_MIN);
    curseur = curseur -> suivant;
  }

  fclose(fp);
}


/**
 * @brief Retourne la taille moyenne de la file issu de Simulation.txt.
 *
 * @return double Taille moyenne de la file.
 */
double fileMoy(void) {
  double file_moy;  // Moyenne à retourner
  int nPersonnes = 0;

  // Datas
  int arrivee_h;
  int arrivee_min;
  int attente_h;
  int attente_min;
  int debut_service_h;
  int debut_service_min;
  int fin_service_h;
  int fin_service_min;


  // Vérification de l'ouverture du fichier
  FILE *fp = fopen(FICHIER_DATA, "r");
  if(fp == NULL) {
    printf("Fichier introuvable\n");
    exit(1);
  }

  // Calcul {nPersonnes} en attente pour chaque minute
  for(int i = 0; i <= HEURE_FERMETURE; i++) {
    while(fscanf(fp, "%02d:%02d %02d:%02d %02d:%02d %02d:%02d\n", &arrivee_h, &arrivee_min,
                                                                  &attente_h, &attente_min,
                                                                  &debut_service_h, &debut_service_min,
                                                  &fin_service_h, &fin_service_min) != EOF) {   // Tant qu'il reste des clients à compter dans la file
      // Conversion en minutes
      debut_service_min += debut_service_h*60 - OFFSET_TRAVAIL_H*60 - OFFSET_TRAVAIL_MIN;
      arrivee_min += arrivee_h - OFFSET_TRAVAIL_H*60 - OFFSET_TRAVAIL_MIN;

      if(debut_service_min > i) {  // On ne regarde que ceux qui N'ONT PAS été servis
        if (arrivee_min < i)  // On ne compte que ceux qui SONT arrivées
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
 * @brief Retourne la taille moyenne de la file d'attente issu de Simulation.txt.
 *
 * @return double Taille moyenne de la file d'attente.
 */
int fileMax(void) {
  int file_max = 0;  // Maximum à retourner
  int nPersonnes = 0;

  // Datas
  int arrivee_h;
  int arrivee_min;
  int attente_h;
  int attente_min;
  int debut_service_h;
  int debut_service_min;
  int fin_service_h;
  int fin_service_min;

  // Vérification de l'ouverture du fichier
  FILE *fp = fopen(FICHIER_DATA, "r");
  if(fp == NULL) {
    printf("Fichier introuvable\n");
    exit(1);
  }

  // Calcul {nPersonnes} max en attente pour chaque minute
  for(int i = 0; i <= HEURE_FERMETURE; i++) {
    while(fscanf(fp, "%02d:%02d %02d:%02d %02d:%02d %02d:%02d\n", &arrivee_h, &arrivee_min,
                                                                  &attente_h, &attente_min,
                                                                  &debut_service_h, &debut_service_min,
                                                                  &fin_service_h, &fin_service_min) != EOF) {   // Tant qu'il reste des clients à compter dans la file
      // Conversion en minutes
      debut_service_min += debut_service_h*60 - OFFSET_TRAVAIL_H*60 - OFFSET_TRAVAIL_MIN;
      arrivee_min += arrivee_h*60 - OFFSET_TRAVAIL_H*60 - OFFSET_TRAVAIL_MIN;

      if(debut_service_min > i) {  // On ne regarde que ceux qui N'ONT PAS été servis
        if (arrivee_min < i)  // On ne compte que ceux qui SONT arrivées
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
 * @brief Retourne le débit moyen de la file d'attente issu de Simulation.txt.
 *
 * @return double Débit moyen de la file d'attente.
 */
double debMoy(void) {
  int nbClients = 0;  // Nombre de clients total

  // Datas
  int arrivee_h;
  int arrivee_min;
  int attente_h;
  int attente_min;
  int debut_service_h;
  int debut_service_min;
  int fin_service_h;
  int fin_service_min;

  // Vérification de l'ouverture du fichier
  FILE *fp = fopen(FICHIER_DATA, "r");
  if(fp == NULL) {
    printf("Fichier introuvable\n");
    exit(1);
  }

  // Calcul {nbClients} total
  while(fscanf(fp, "%02d:%02d %02d:%02d %02d:%02d %02d:%02d\n", &arrivee_h, &arrivee_min,
                                                                &attente_h, &attente_min,
                                                                &debut_service_h, &debut_service_min,
                                                                &fin_service_h, &fin_service_min) != EOF)
    nbClients++;
  fclose(fp);

  return (double)nbClients / HEURE_FERMETURE;  // Débit de clients moyen
}


/**
 * @brief Retourne le taux de clients non traitées de la file d'attente issu de Simulation.txt.
 *
 * @return double Taux de clients non traitées de la file d'attente.
 */
double tauxTraite(void) {
  int nbClients = 0;
  int non_traites = 0;

  // Datas
  int arrivee_h;
  int arrivee_min;
  int attente_h;
  int attente_min;
  int debut_service_h;
  int debut_service_min;
  int fin_service_h;
  int fin_service_min;

  // Vérification de l'ouverture du fichier
  FILE *fp = fopen(FICHIER_DATA, "r");
  if(fp == NULL) {
    printf("Fichier introuvable\n");
    exit(1);
  }

  // Calcul {non_traites}
  while(fscanf(fp, "%02d:%02d %02d:%02d %02d:%02d %02d:%02d\n", &arrivee_h, &arrivee_min,
                                                                &attente_h, &attente_min,
                                                                &debut_service_h, &debut_service_min,
                                                                &fin_service_h, &fin_service_min) != EOF) {
    nbClients++;
    fin_service_min += fin_service_h*60 - OFFSET_TRAVAIL_H*60 - OFFSET_TRAVAIL_MIN;  // Conversion en minutes
    if(fin_service_min > HEURE_FERMETURE)  // Si il doit être traité après la fermeture
      non_traites++;
  }
  fclose(fp);

  return 1 - (double)non_traites / nbClients;  // Taux de clients non traités
}


/**
 * @brief Retourne le temps de réponse moyen de la file d'attente issu de Simulation.txt.
 *
 * @return double Temps de réponse moyen de la file.
 */
double tempsRep(void) {
  int nbClients = 0;
  int temps_tot = 0;

  // Datas
  int arrivee_h;
  int arrivee_min;
  int attente_h;
  int attente_min;
  int debut_service_h;
  int debut_service_min;
  int fin_service_h;
  int fin_service_min;

  // Vérification de l'ouverture du fichier
  FILE *fp = fopen(FICHIER_DATA, "r");
  if(fp == NULL) {
    printf("Fichier introuvable\n");
    exit(1);
  }

  // Calcul {temps_tot}
  while(fscanf(fp, "%02d:%02d %02d:%02d %02d:%02d %02d:%02d\n", &arrivee_h, &arrivee_min,
                                                                &attente_h, &attente_min,
                                                                &debut_service_h, &debut_service_min,
                                                                &fin_service_h, &fin_service_min) != EOF) {
    arrivee_min += arrivee_h*60 - OFFSET_TRAVAIL_H*60 - OFFSET_TRAVAIL_MIN;
    fin_service_min += fin_service_h*60 - OFFSET_TRAVAIL_H*60 - OFFSET_TRAVAIL_MIN;
    nbClients++;
    temps_tot += fin_service_min - arrivee_min;
  }
  fclose(fp);

  return (double)temps_tot / nbClients;  // Temps de réponse moyen du guichet
}
