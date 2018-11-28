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


void ecrireTableau(struct Performance *performance) {
    FILE *ftableau = fopen("Tableau de Bord.txt", "w");
    fprintf(ftableau, "---Performance---\n");
    fprintf(ftableau, "Taille moyenne des files d'attente : %lf\n", performance -> file_moy);
    fprintf(ftableau, "Taille maximum des files d’attente : %i\n", performance -> file_max);
    fprintf(ftableau, "Débit moyen (nombre moyen de clients par unité de temps) : %lf\n", performance -> deb_moy);
    fprintf(ftableau, "Taux de clients non servis : %lf\n", performance -> taux_trait);
    fprintf(ftableau, "Temps de réponse moyen : %lf\n", performance -> temps_reponse_moy);
    fclose(ftableau);
}


