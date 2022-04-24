#include "fonc.h"

void Square_Multiply (mpz_t a, mpz_t mod, mpz_t exp, mpz_t res) {

    mpz_init_set(res, a);

    mp_size_t t;
    t = mpz_sizeinbase(exp, 2);
    mp_size_t i;

    for(i = t-1; i > 0; i--) {
        mpz_mul(res, res, res);
        mpz_mod(res, res, mod);
        if(mpz_tstbit(exp, i)) {
            mpz_mul(res, res, a);
            mpz_mod(res, res, mod);
        }
        
    } 

    return;
}