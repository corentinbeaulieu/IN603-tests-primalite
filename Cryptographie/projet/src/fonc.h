#ifndef FONC_H_INCLUDED
#define FONC_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <gmp.h>
#include <stdbool.h>
#include <time.h>
#include <omp.h>

#define COMPOSE false
#define PREMIER true


void Square_Multiply (mpz_t, mpz_t, mpz_t, mpz_t);

bool Test_Fermat (mpz_t, unsigned int);

bool Test_Miller_Rabin(mpz_t, unsigned int);


#endif
