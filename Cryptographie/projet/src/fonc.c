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


void Decomposition (const mpz_t n, mpz_t s, mpz_t t) {
	mpz_t x;
	mpz_init_set(x, n);
	mpz_sub_ui(x, x, 1);


	while(!(mpz_fdiv_ui(x, 2))) {
		mpz_div_ui(x, x, 2);
		mpz_add_ui(s, s, 1);
	}
	mpz_set(t, x);
	mpz_clear(x);

	return;
}


bool Test_Miller_Rabin (mpz_t n, unsigned int nbRep) {
	mpz_t s, t;
	mpz_init(s);
	mpz_init(t);
	Decomposition(n, s, t);
	mpz_sub_ui(s, s, 1);

	gmp_randstate_t state;
	gmp_randinit_mt(state);
	gmp_randseed_ui(state, time(0));

	mpz_t nMoins2;
	mpz_init_set(nMoins2, n);
	mpz_sub_ui(nMoins2, nMoins2, 2);

	mpz_t a, y;
	mpz_init(a);
	mpz_init(y);

	int i, j;
	for(i = 0; i < nbRep; i++) {
		printf("1\n");
		mpz_urandomm(a, state, nMoins2);
		mpz_add_ui(a, a, 1);

		Square_Multiply(y, a, n, t);

		if(mpz_cmp_ui(y, 1) && mpz_cmp_si(y, -1)) {
			for(j = 0; mpz_cmp_si(s, j); j++) {
				printf("2\n");
				mpz_mul(y, y, y);
				mpz_mod(y, y, n);
				if(mpz_cmp_ui(y, 1))
					return COMPOSE;

				if(mpz_cmp_si(y, -1))
					goto yModnEgalMoinsUn;
			}
			return COMPOSE;
			yModnEgalMoinsUn:
			printf("3\n");
		}
	}

	return PREMIER;
}