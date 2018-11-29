# ProjetS5

## Projet : Étude et simulation d’une file d’attente

> Afin d’améliorer la gestion des flux journaliers des clients, une banque souhaite simuler le fonctionnement de son guichet unique.
>
> Les clients arrivent à des dates aléatoires et rentrent dans une queue représentée par un système de tickets numérotées dans un ordre croissant.
>
> L’intervalle entre l’arrivée de deux clients successifs est un nombre aléatoire qui suit une loi exponentielle de paramètre λ.
>
> Lorsque le guichetier a fini de traiter un client, il appelle le client suivant dont le service s’étale sur une durée aléatoire modélisée par une loi uniforme de paramètre [min, max].
>
> La banque ouvre à 8h30 et ferme à 17h30. Les clients peuvent entrer dans le système jusqu’à 17H00.
>
> > 1. Proposer et définir les structures de données nécessaires pour la simulation du fonctionnement du guichet. Justifier votre choix
> >
> > 2. Simuler le fonctionnement :  créer la liste journalière de clients ; (ii) initialiser la date d’arrivée, la durée d’attente et la date de la fin de service de chacun des clients. Les dates sont des entiers indiquant des minutes.
> >
> >    Le principe suivant permet de générer des réalisations d’une variable aléatoire X obéissant à une loi exponentielle : si $`U ∼ [0, 1]`$, alors $`X = −ln(1 − U )/λ`$
> >
> > 3. Créer et enregistrer dans un fichier la liste journalières des clients et les informations relatives à leur service (date d’arrivée, durée d’attente, date du début de service, date de fin de service, etc.).
> >
> > 4. En se basant sur la liste journalière des clients détaillée dans un fichier, mesurer les métriques de performance suivantes :
> >    - taille moyenne des files d’attente ;
> >    - taille maximum des files d’attente ;
> >    - débit moyen (nombre moyen de clients par unité de temps) ;
> >    - taux de clients non servis ;
> >    - temps de réponse moyen (temps de traitement moyen des clients). Le temps de réponse pour un client est la différence entre sa date d’arrivée et sa date de fin de service.
> >
> > 5. Imaginer et proposer un tableau de bord bien présenté dans un fichier qui recense les différentes métriques de performance du fonctionnement journalier du guichet.
