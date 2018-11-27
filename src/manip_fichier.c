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
  /*variables à écrire dans le fichier*/
  int arr;
  int att;
  int fin_serv;
  int deb_serv;
  /*initialisation*/
  fp = fopen("simulation.txt", "w");
  curseur = listeclients-> HEAD;
  /*tant qu'il reste des clients*/
  while(curseur != NULL) {
    /*calcul et écriture des valeurs*/
    arr = curseur -> arrivee;
    att = curseur -> attente;
    deb_serv = arr + att;
    fin_serv = curseur -> fin_service;
    fprintf(fp, "%d %d %d %d\n", arr, att, deb_serv, fin_serv);
  }
  fclose(fp);
}


double fileMoy(void) {
	FILE *fp;
  double moy;
  int somme=0;
  int i;
  /*variables servant à lire les valeurs*/
  int arr;
  int att;
  int fin_serv;
  int deb_serv;
  /*indique si les clients suivants ne sont pas encore entrés dans la file*/
  bool end=false;
  /*vérification de l'ouverture du fichier*/
  fp = fopen("simulation.txt", "r");
  if(fp == NULL)
  	return -1;
  /*calcul pour chaque minute*/
  for(i =0 ;i <= 540;i ++) {
    /*tant qu'il reste des clients à compter dans la file*/
  	while(!end && fscanf(fp, "%d %d %d %d\n", &arr, &att, &deb_serv, &fin_serv) == 4) {
      /*on ne regarde que ceux qui n'ont pas été servis*/
  		if(deb_serv > i) {
        /*on ne regarde que ceux qui sont arrivés*/
  			if(arr < i)
  				somme ++;
  			else
  				end = true;
  		}
  	}
    /*réinitiaisation*/
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
  /*variables servant à lire les valeurs*/
  int arr;
  int att;
  int fin_serv;
  int deb_serv;
  /*indique si les clients suivants ne sont pas encore entrés dans la file*/
  bool end=false;
  /*vérification de l'ouverture du fichier*/
  fp = fopen("simulation.txt", "r");
  if(fp == NULL)
  	return 0;
  /*calcul pour chaque minute*/
  for(i =0 ;i <= 540;i ++) {
    /*tant qu'il reste des clients à compter dans la file*/
  	while(!end && fscanf(fp, "%d %d %d %d\n", &arr, &att, &deb_serv, &fin_serv) == 4) {
      /*on ne regarde que ceux qui n'ont pas été servis*/
  		if(deb_serv > i) {
        /*on ne regarde que ceux qui sont arrivés*/
  			if(arr < i)
  				somme ++;
  			else
  				end = true;
  		}
  	}
    /*réinitiaisation*/
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
  /*variables servant à lire les valeurs*/
	int arr;
  int att;
  int fin_serv;
  int deb_serv;
  /*vérification de l'ouverture du fichier*/
  fp = fopen("simulation.txt", "r");
  if(fp == NULL)
  	return -1;
  /*tant qu'il y a des clients*/
  while(fscanf(fp, "%d %d %d %d\n", &arr, &att, &deb_serv, &fin_serv) == 4)
  	nbClients ++;
  deb = nbClients / 540.0;
  return deb;
}


double tauxTraite(void) {
	FILE *fp;
	int nbClients = 0;
	int non_traites = 0;
	float nb;
	double taux;
  /*variables servant à lire les valeurs*/
	int arr;
  int att;
  int fin_serv;
  int deb_serv;
  /*vérification de l'ouverture du fichier*/
  fp = fopen("simulation.txt", "r");
  if(fp == NULL)
  	return -1;
  /*tant qu'il y a des clients*/
  while(fscanf(fp, "%d %d %d %d\n", &arr, &att, &deb_serv, &fin_serv) == 4) {
  	nbClients ++;
    /*si il doit être traité après la fermeture*/
  	if(fin_serv > 540)
  		non_traites ++;
  }
  /*on passe l'entier en double pour que la division ne soit pas euclidienne*/
  nb = nbClients;
  taux = non_traites / nb;
  return taux;
}


double tempsRep(void) {
	FILE *fp;
	int nbClients = 0;
	int temps_tot = 0;
	double temps;
	double reponse;
  /*variables servant à lire les valeurs*/
	int arr;
  int att;
  int fin_serv;
  int deb_serv;
  /*vérification de l'ouverture du fichier*/
  fp = fopen("simulation.txt", "r");
  if(fp == NULL)
  	return 0;
  /*tant qu'il y a des clients*/
  while(fscanf(fp, "%d %d %d %d\n", &arr, &att, &deb_serv, &fin_serv) == 4) {
  	nbClients ++;
  	temps_tot = temps_tot + (fin_serv - arr);
  }
  /*on passe l'entier en double pour que la division ne soit pas euclidienne*/
  temps = temps_tot;
  reponse = temps / nbClients;
  return reponse;
}

/*
main de test

int main(void) {
  struct ListeClients *listeclients;
  int file_max;
  double file_moy;
  double deb_moy;
  double taux_traitement;
  double temps_reponse;
  listeclients = creerListeJournaliere();
  ecrireList(listeclients);
  file_max = fileMax();
  file_moy = fileMoy();
  deb_moy = debMoy();
  taux_traitement = tauxTraite();
  temps_reponse = tempsRep();
  printf("%d,%f,%f,%f,%f\n", file_max, file_moy, deb_moy, taux_traitement, temps_reponse);
	return 0;
}
*/
