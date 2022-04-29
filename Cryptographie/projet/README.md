# Test de primalité
Corentin Beaulieu - 21906966
---
---

## Introduction

L'archive remise contient les fichiers suivants:
* _README.md_ : le fichier que vous êtes en train de lire contenant une description du programme et de son utilisation.
* _src/Makefile_ disposant des cibles suivantes :
    * *primalite* pour compiler le programme et obtenir un exécutable nommé primalite.
    * *run* pour lancer un test de fermat sur le nombre 2^23209 - 1.
    * *miler* pour lancer un test de miller sur le nombre 2^21701 - 1 contenu dans un fichier.
    * *clean* pour effacer tous les produits de la compilation.
* _src/main.c_ qui contient la foction main du programme.
* _src/fonc.c_ qui contient les implémentations des fonctions de test de primalite et d'exponentiation.
* _src/fonc.h_ le fichier d'entête contenant les signatures des fonctions de test et d'exponnentiation.
* _src/test.txt_ qui contient un nombre pour montrer l'utilisation de l'option de lecture dans un fichier.

---
## Usage

L'usage du programme compilé est le suivant: 
`./primalite \[option\] nombre_a_tester`
où `nombre_a_tester` est l'entrée du programme.

Les options possibles sont les suivantes:
* `-m` pour exécuter un test de Miller-Rabin au lieu d'un test de Fermat.
* `-x` pour spécifier que l'entrée est écrite en base 16 au lieu de la base 10.
* `-f` pour lire l'entrée dans un fichier texte.
    * L'usage devient alors `./primalité \[option\] -f chemin_fichier` où `chemin_fichier` est le chemin vers un fichier contenant un unique nombre écrit sans retour chariot.

---

## Description
Les différentes fonctions ont été implémentées à partir des algorithmes donnés dans le sujet.\
La librairie **GMP** est utilisée pour gérer de grands nombres.\
La librairie **OpenMP** est utilisée pour paralléliser les itérations des tests.

### Square and Multiply
Cette fonction prend en entrée quatre paramètres qui sont tous de type `mpz_t`
* `retour` est la variable dans laquelle sera stocké le resultat de l'exponentiation.
* `a` est la base de l'exponentielle.
* `mod` est le modulo de cette exponentiation modulaire.
* `exp` est l'exposant.

Cette fonction stocke dans `retour` la valeur de `a^exp % mod`.

### Test de Fermat 
Cette fonction performe un test de Fermat.\
Elle prend en entrée deux paramètres :
* `n` le nombre dont l'on souhaite savoir si il est premier ou composé.
* `nbRep` le nombre de fois où le test de Fermat sera répété avant de renvoyer une réponse.

Cette fonction renvoie un booléen valant vrai si le nombre est premier (d'après le test de Fermat après `nbRep` répétitions) ou faux si le nombre est composé.

Dans la fonction principale, on a fixé le nombre de répétitions du test de Fermat à 40 car l'on considère qu'une probabilité au pire de 1/2^60 ~= 1e-18 (d'après ce que l'on a vu en TD) de se tromper en renvoyant "premier" est acceptable.

### Test de Miller-Rabin

Cette fonction performe un test de Miller-Rabin.\
Elle prend en entrée deux paramètres :
* `n` le nombre dont l'on souhaite savoir si il est premier ou composé.
* `nbRep` le nombre de fois où le test de Miller_Rabin sera répété avant de renvoyer une réponse.

Cette fonction renvoie un booléen valant vrai si le nombre est premier (d'après le test de Miller-Rabin après `nbRep` répétitions) ou faux si le nombre est composé.

Dans la fonction principale, on a fixé le nombre de répétitions du test de Miller-Rabin à 20 car l'on considère qu'une probabilité au pire de 1/4^30 ~= 1e-18 (d'après l'énoncé) de se tromper en renvoyant "premier" est acceptable. De plus, cela nous permet de dire que les deux tests implémentés ont la même probabilité de se tromper.