/* Copyright (c) 2022 Corentin Beaulieu
 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. */


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
