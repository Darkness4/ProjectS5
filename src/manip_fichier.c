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
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "fonction.h"
#include "manip_fichier.h"

const int DUREE = 540;  // Durée de travail


/**
 * @brief Rentre la liste des clients dans le fichier.
 *
 * @param listeclients Liste des clients avec un pointeur HEAD.
 */
void ecrireList(struct ListeClients *listeclients) {
  FILE *fp;
  struct Client *curseur;
  // Initialisation
  fp = fopen("simulation.txt", "w");
  curseur = listeclients-> HEAD;
  while(curseur != NULL) {   // Tant qu'il reste des clients
    // Calcul et écriture des valeurs
    int deb_serv = curseur -> arrivee + curseur -> attente;

    fprintf(fp, "%d %d %d %d\n", curseur -> arrivee, 
                                 curseur -> attente, 
                                 deb_serv, 
                                 curseur -> fin_service);
    curseur = curseur -> suivant;
  }
  fclose(fp);
}


double fileMoy(void) {
  FILE *fp;
  double file_moy;
  int somme = 0;
  int i;
  // Variables servant à lire les valeurs
  int arr;
  int att;
  int fin_serv;
  int deb_serv;
  bool is_end = false;  // Indique si les clients suivants ne sont pas encore entrés dans la file
  // Vérification de l'ouverture du fichier
  fp = fopen("simulation.txt", "r");
  if(fp == NULL) {
    printf("Fichier introuvable\n");
    exit(1);
  }

  for(i = 0; i <= DUREE; i ++) {  // Calcul pour chaque minute
    while(!is_end && fscanf(fp, "%d %d %d %d\n", &arr, &att, &deb_serv, &fin_serv) == 4) {   // Tant qu'il reste des clients à compter dans la file
      if(deb_serv > i)  // On ne regarde que ceux qui n'ont pas été servis
        (arr < i) ? somme++ : (is_end = true);
    }
    // Réinitiaisation
    is_end = false;
    fseek(fp, 0, SEEK_SET);
  }
  file_moy = (double)somme / DUREE;
  fclose(fp);
  return file_moy;
}


int fileMax(void) {
  FILE *fp;
  int somme = 0;
  int file_max = 0;
  int i;
  // Variables servant à lire les valeurs
  int arr;
  int att;
  int fin_serv;
  int deb_serv;
  bool is_end = false;   // Indique si les clients suivants ne sont pas encore entrés dans la file
  // Vérification de l'ouverture du fichier
  fp = fopen("simulation.txt", "r");
  if(fp == NULL) {
    printf("Fichier introuvable\n");
    exit(1);
  }
  for(i = 0; i <= DUREE; i ++) {   // Calcul pour chaque minute
    while(!is_end && fscanf(fp, "%d %d %d %d\n", &arr, &att, &deb_serv, &fin_serv) == 4) {   // Tant qu'il reste des clients à compter dans la file
      if(deb_serv > i) {   // On ne regarde que ceux qui n'ont pas été servis
        if(arr < i)   // On ne regarde que ceux qui sont arrivés
          somme ++;
        else
          is_end = true;
      }
    }
    //réinitiaisation
    is_end = false;
    fseek(fp, 0, SEEK_SET);
    if(somme > file_max)
      file_max = somme;
    somme = 0;
  }
  fclose(fp);
  return file_max;
}


double debMoy(void) {
  FILE *fp;
  int nbClients = 0;
  double deb_moy;
  // Variables servant à lire les valeurs
  int arr;
  int att;
  int fin_serv;
  int deb_serv;
  // Vérification de l'ouverture du fichier
  fp = fopen("simulation.txt", "r");
  if(fp == NULL) {
    printf("Fichier introuvable\n");
    exit(1);
  }
  while(fscanf(fp, "%d %d %d %d\n", &arr, &att, &deb_serv, &fin_serv) == 4)   // Tant qu'il y a des clients
    nbClients ++;
  fclose(fp);
  deb_moy = (double)nbClients / DUREE;
  return deb_moy;
}


double tauxTraite(void) {
  FILE *fp;
  int nbClients = 0;
  int non_traites = 0;
  double taux;
  // Variables servant à lire les valeurs
  int arr;
  int att;
  int fin_serv;
  int deb_serv;
  // Vérification de l'ouverture du fichier
  fp = fopen("simulation.txt", "r");
  if(fp == NULL) {
    printf("Fichier introuvable\n");
    exit(1);
  }
  while(fscanf(fp, "%d %d %d %d\n", &arr, &att, &deb_serv, &fin_serv) == 4) {   // Tant qu'il y a des clients
    nbClients ++;
    if(fin_serv > 540)   // Si il doit être traité après la fermeture
      non_traites ++;
  }
  fclose(fp);
  taux = 1 - non_traites / (double)nbClients;
  return taux;
}


double tempsRep(void) {
  FILE *fp;
  int nbClients = 0;
  int temps_tot = 0;
  double temps;
  double temps_reponse_moy;
  // Variables servant à lire les valeurs
  int arr;
  int att;
  int fin_serv;
  int deb_serv;
  // Vérification de l'ouverture du fichier
  fp = fopen("simulation.txt", "r");
  if(fp == NULL) {
    printf("Fichier introuvable\n");
    exit(1);
  }
  while(fscanf(fp, "%d %d %d %d\n", &arr, &att, &deb_serv, &fin_serv) == 4) {   // Tant qu'il y a des clients
    nbClients ++;
    temps_tot = temps_tot + (fin_serv - arr);
  }
  fclose(fp);
  temps = temps_tot;   // On passe l'entier en double pour que la division ne soit pas euclidienne
  temps_reponse_moy = temps / nbClients;
  return temps_reponse_moy;
}
