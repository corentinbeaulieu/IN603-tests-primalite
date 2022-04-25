#include "fonc.h"
#include <gmp.h>


int main(int argc, char *argv[]) {

    mpz_t a, n, h, r;
    mpz_init_set_ui(a, 19);
    mpz_init_set_ui(n, 20);
    mpz_init_set_ui(h, 1); 
	mpz_init(r);

    Square_Multiply(r, a, n, h);
	bool test;

	test = Test_Fermat(r, 80);


    gmp_printf("%Zu est %s \n", r, test?"premier":"composé");

	mpz_clear(a);
	mpz_clear(n);
	mpz_clear(h);
	mpz_clear(r);
    

    return 0;
}
