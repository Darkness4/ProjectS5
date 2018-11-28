/**
 * @file tableau.c
 * 
 * @brief Tableau de bord des performances du guichet.
 * 
 * Affiche dans un fichier les différentes métriques de performance du fonctionnement journalier du guichet.
 * 
 * @author Marc NGUYEN
 * @author Mathieu POIGNANT
 * @date 17 Nov 2018
 */

#include "tableau.h"
#include <stdio.h>

const char* FICHIER_TABLEAU = "Tableau de Bord.txt";


void ecrireTableau(double file_moy, int file_max, double deb_moy, double taux_traitement, double temps_reponse_moy) {
    FILE *ftableau = fopen(FICHIER_TABLEAU, "w");
    fprintf(ftableau, "---Performance---\n");
    fprintf(ftableau, "Taille moyenne des files d'attente : %lf\n", file_moy);
    fprintf(ftableau, "Taille maximum des files d’attente : %i\n", file_max);
    fprintf(ftableau, "Débit moyen (nombre moyen de clients par unité de temps) : %lf\n", deb_moy);
    fprintf(ftableau, "Taux de clients non servis : %lf\n", taux_traitement);
    fprintf(ftableau, "Temps de réponse moyen : %lf\n", temps_reponse_moy);
    fclose(ftableau);
}


