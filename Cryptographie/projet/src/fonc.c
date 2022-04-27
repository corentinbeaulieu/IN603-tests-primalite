#include "fonc.h"

void Square_Multiply (mpz_t retour, mpz_t a, mpz_t mod, mpz_t exp) {

    mpz_set(retour, a);

    mp_size_t t;
    t = mpz_sizeinbase(exp, 2);
    mp_size_t i;

    for(i = t-2; i >= 0; i--) {
        mpz_mul(retour, retour, retour);
        mpz_mod(retour, retour, mod);
        if(mpz_tstbit(exp, i)) {
            mpz_mul(retour, retour, a);
            mpz_mod(retour, retour, mod);
        }
    } 

    return;
}

bool Test_Fermat(mpz_t n, unsigned int nbRep)  {
	int i;
	bool retour;
	retour = PREMIER;
	mpz_t a, res, nMoins1, nMoins2;

	mpz_init(a);
	mpz_init(res);

	mpz_init_set(nMoins1, n);
	mpz_sub_ui(nMoins1, nMoins1, 1);

	mpz_init_set(nMoins2, n);
	mpz_sub_ui(nMoins2, nMoins2, 2);

	gmp_randstate_t state;
	gmp_randinit_mt(state);
	gmp_randseed_ui(state, time(0));


	for(i = 0; i < nbRep; i++) {
		mpz_urandomm(a, state, nMoins2);
		mpz_add_ui(a, a, 1);

		Square_Multiply (res, a, n, nMoins1);
		if(mpz_cmp_ui(res, 1)){
			retour = COMPOSE;
			break;
		}
	}
	gmp_randclear(state);
	mpz_clear(a);
	mpz_clear(res);
	mpz_clear(nMoins1);
	mpz_clear(nMoins2);

	return retour;
}
