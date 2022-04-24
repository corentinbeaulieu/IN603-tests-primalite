#include "fonc.h"
#include <gmp.h>


int main(int argc, char *argv[]) {

    mpz_t a, n, h, r;
    mpz_init_set_ui(a, 2000000);
    mpz_init_set_ui(n, 1000000000001);
    mpz_init_set(h, n-1);

    Square_Multiply(a, n, h, r);

    gmp_printf("Ce qu'on a calculé %Zu\n", r);
    

    return 0;
}