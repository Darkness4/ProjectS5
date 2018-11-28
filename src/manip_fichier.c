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
#include "fonction.h"
#include "manip_fichier.h"


/**
 * @brief Rentre la liste des clients dans le fichier.
 *
 * @param listeclients Liste des clients avec un pointeur HEAD.
 */
void ecrireList(struct ListeClients *listeclients) {
  FILE *fp;
  struct Client *curseur;
  //variables à écrire dans le fichier
  int arr;
  int att;
  int fin_serv;
  int deb_serv;
  //initialisation
  fp = fopen("simulation.txt", "w");
  curseur = listeclients-> HEAD;
  while(curseur != NULL) {   //tant qu'il reste des clients
    //calcul et écriture des valeurs
    arr = curseur -> arrivee;
    att = curseur -> attente;
    deb_serv = arr + att;
    fin_serv = curseur -> fin_service;
    fprintf(fp, "%d %d %d %d\n", arr, att, deb_serv, fin_serv);
    curseur = curseur -> suivant;
  }
  fclose(fp);
}


double fileMoy(void) {
  FILE *fp;
  double moy;
  int somme=0;
  int i;
  //variables servant à lire les valeurs
  int arr;
  int att;
  int fin_serv;
  int deb_serv;
  bool end=false;   //indique si les clients suivants ne sont pas encore entrés dans la file
  //vérification de l'ouverture du fichier
  fp = fopen("simulation.txt", "r");
  if(fp == NULL)
    return -1;
  for(i =0 ;i <= 540;i ++) {   //calcul pour chaque minute
    while(!end && fscanf(fp, "%d %d %d %d\n", &arr, &att, &deb_serv, &fin_serv) == 4) {   //tant qu'il reste des clients à compter dans la file
      if(deb_serv > i) {   //on ne regarde que ceux qui n'ont pas été servis
      if(arr < i)   //on ne regarde que ceux qui sont arrivés
        somme ++;
      else
        end = true;
      }
    }
    //réinitiaisation
    end = false;
    fseek(fp,0,SEEK_SET);
  }
  moy = somme / 540.0;
  fclose(fp);
  return moy;
}


int fileMax(void) {
  FILE *fp;
  int somme=0;
  int max=0;
  int i;
  //variables servant à lire les valeurs
  int arr;
  int att;
  int fin_serv;
  int deb_serv;
  bool end=false;   //indique si les clients suivants ne sont pas encore entrés dans la file
  //vérification de l'ouverture du fichier
  fp = fopen("simulation.txt", "r");
  if(fp == NULL)
    return 0;
  for(i =0 ;i <= 540;i ++) {   //calcul pour chaque minute
    while(!end && fscanf(fp, "%d %d %d %d\n", &arr, &att, &deb_serv, &fin_serv) == 4) {   //tant qu'il reste des clients à compter dans la file
      if(deb_serv > i) {   //on ne regarde que ceux qui n'ont pas été servis
        if(arr < i)   //on ne regarde que ceux qui sont arrivés
          somme ++;
        else
          end = true;
      }
    }
    //réinitiaisation
    end = false;
    fseek(fp,0,SEEK_SET);
    if(somme > max)
      max = somme;
    somme = 0;
  }
  fclose(fp);
  return max;
}


double debMoy(void) {
  FILE *fp;
  int nbClients = 0;
  double deb;
  //variables servant à lire les valeurs
  int arr;
  int att;
  int fin_serv;
  int deb_serv;
  //vérification de l'ouverture du fichier
  fp = fopen("simulation.txt", "r");
  if(fp == NULL)
    return -1;
  while(fscanf(fp, "%d %d %d %d\n", &arr, &att, &deb_serv, &fin_serv) == 4)   //tant qu'il y a des clients
    nbClients ++;
  deb = (double)nbClients / 540;
  return deb;
}


double tauxTraite(void) {
  FILE *fp;
  int nbClients = 0;
  int non_traites = 0;
  float nb;
  double taux;
  //variables servant à lire les valeurs
  int arr;
  int att;
  int fin_serv;
  int deb_serv;
  //vérification de l'ouverture du fichier
  fp = fopen("simulation.txt", "r");
  if(fp == NULL)
    return -1;
  while(fscanf(fp, "%d %d %d %d\n", &arr, &att, &deb_serv, &fin_serv) == 4) {   //tant qu'il y a des clients
    nbClients ++;
    if(fin_serv > 540)   //si il doit être traité après la fermeture
      non_traites ++;
  }
  nb = nbClients;   //on passe l'entier en double pour que la division ne soit pas euclidienne
  taux = 1 - non_traites / nb;
  return taux;
}


double tempsRep(void) {
  FILE *fp;
  int nbClients = 0;
  int temps_tot = 0;
  double temps;
  double reponse;
  //variables servant à lire les valeurs
  int arr;
  int att;
  int fin_serv;
  int deb_serv;
  //vérification de l'ouverture du fichier
  fp = fopen("simulation.txt", "r");
  if(fp == NULL)
    return -1;
  while(fscanf(fp, "%d %d %d %d\n", &arr, &att, &deb_serv, &fin_serv) == 4) {   //tant qu'il y a des clients
    nbClients ++;
    temps_tot = temps_tot + (fin_serv - arr);
  }
  temps = temps_tot;   //on passe l'entier en double pour que la division ne soit pas euclidienne
  reponse = temps / nbClients;
  return reponse;
}
