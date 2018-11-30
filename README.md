# ProjetS5

- [ProjetS5](#projets5)
    - [Projet : Étude et simulation d’une file d’attente](#projet--Étude-et-simulation-dune-file-dattente)
    - [Build](#build)
        - [From Linux](#from-linux)
            - [Target Linux](#target-linux)
            - [Target Windows](#target-windows)
        - [From Windows](#from-windows)
            - [Build for Linux](#build-for-linux)
            - [Build for Windows](#build-for-windows)
                - [MSYS2 MinGW64](#msys2-mingw64)
    - [Usage](#usage)
        - [Linux](#linux)
        - [Windows](#windows)
    - [Paramétrage](#paramétrage)
    - [Documentation](#documentation)

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

## Build

### From Linux

#### Target Linux

```bash
sudo apt update && sudo apt install -y git gcc make
git clone git@gitlab.emse.fr:marc.nguyen/projects5.git
cd projects5
```

```bash
make
```

#### Target Windows

```bash
sudo apt update && sudo apt install -y git gcc-mingw-w64-x86-64 make
git clone git@gitlab.emse.fr:marc.nguyen/projects5.git
cd projects5
```

```bash
make CC=/usr/bin/x86_64-w64-mingw32-gcc TARGET=projects5.exe
```

### From Windows

#### Build for Linux

Plusieurs choix s'offre à vous : Cygwin, WSL, VM...
Note : Ne prenez pas MSYS2, qui cible Windows.

Vous pouvez suivre les instructions de [From Linux Target Linux](#target-linux).

Vérifiez seulement votre package manager : (pacman, apt, apk...).

#### Build for Windows

Plusieurs choix s'offre à vous : Cygwin, MSYS2, WSL, VM...
Important : Notez que votre VM/sous-système Linux doivent être compatible MinGW (sinon compilez le vous même).

Les VM et WSL peuvent suivre les instructions de [From Linux Target Windows](#target-windows).

##### MSYS2 MinGW64

```bash
pacman -Syuu && pacman -S --needed base-devel git mingw-w64-i686-toolchain mingw-w64-x86_64-toolchain
git clone git@gitlab.emse.fr:marc.nguyen/projects5.git
cd projects5
```

```bash
make
```

## Usage

### Linux

```bash
./projects5
```

### Windows

```bat
./projects5.exe
```

Ou lancer simplement le .exe.

Un fichier listant les clients du jour va être généré.

Un tableau de bord permettra de voir les statistiques intéressantes.

## Paramétrage

D'après l'énoncé, on peut jouer sur ces constantes :
```C
// fonction.c

/**
 * @brief duree prend un valeur entre [MIN, MAX] suivant la loi uniforme.
 */
const int MIN = 1;
/**
 * @brief duree prend un valeur entre [MIN, MAX] suivant la loi uniforme.
 */
const int MAX = 20;
/**
 * @brief Constante de la loi exponentielle.
 * 
 * L'arrivée d'un client suit la loi exponentielle.
 * Le principe suivant permet de générer des réalisations d’une variable
 * aléatoire X obéissant à une loi exponentielle : si U ∼ [0, 1], alors
 * X = −ln(1 − U )/λ.
 */
const float LAMBDA = 0.1;
/**
 * @brief Heure en minutes de fermeture de l'accès.
 */
const int MINUTE_ACCEPTE = 510;  // 17h00 - 8h30 = 510 min.
```

```C
// manip_fichier.c

/**
 * @brief Heure en minutes du fermeture de la banque.
 */
const int MINUTE_FERMETURE = 540;  // 17h30 - 8h30 = 540 min.
/**
 * @brief Heure en minute du début du travail.
 */
const int OFFSET_TRAVAIL = 510;  // 8h30 = 510 min.
/**
 * @brief Nom du fichier stockant la liste journalière des clients.
 */
const char* FICHIER_DATA = "Simulation.txt";
```

```C
// tableau.c

/**
 * @brief Nom du fichier stockant le tableau de bord.
 */
const char* FICHIER_TABLEAU = "Tableau de Bord.txt";
```

## Documentation

Vous pouvez aller voir la [documentation](http://marc.nguyen.gitlab.emse.fr/projects5/) généré par Doxygen.

Dans le dossier doc, il est possible de générer une documentation Doxygen.

```bash
sudo apt install -y doxygen texlive-full
cd ./doc/
doxygen
```

Il est possible de générer une documentation [Doxygen m.css](https://mcss.mosra.cz/doxygen/).
