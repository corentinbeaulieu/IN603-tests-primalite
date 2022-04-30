#ifndef FONC_H_INCLUDED
#define FONC_H_INCLUDED

#include <stdio.h>      // Librairie pour l'affichage et la lecture dans un fichier
#include <stdlib.h>     // Librairie standard du C
#include <unistd.h>     // Librairie permettant la gestion d'options
#include <gmp.h>        // Librairie pour la gestion de grands nombres
#include <stdbool.h>    // Librairie pour l'utilisation simplifiée du type bool
#include <time.h>       // Librairie pour récupérer l'heure nécessaire à l'initialisation d'une graine
#include <omp.h>        // Librairie pour la parallélisation

// Définition d'alias
#define COMPOSE false
#define PREMIER true

// Signatures des fonctions 
void Square_Multiply (mpz_t, const mpz_t, const mpz_t, const mpz_t);

bool Test_Fermat (const mpz_t, unsigned int);

bool Test_Miller_Rabin(const mpz_t, unsigned int);


#endif
