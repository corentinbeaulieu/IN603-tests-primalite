#include "fonc.h"


int main(int argc, char *argv[]) {

    int option;
    //bool optfichier = false;
    bool miller = false;


    while( (option = getopt(argc, argv, "m")) != -1) {
        printf("%d\n", option);
        switch (option) {
            /*case 'f':
                FILE *file;
                file = fopen(optarg, "r");
                unsigned long int nbCar;
                fseek(file, 0, SEEK_END);
                nbCar = ftell(file);
                nbCar++;
                printf("%ld\n", nbCar);
                rewind(file);
                printf("nombre");
                nombre = malloc(nbCar*sizeof(char));
                fgets(nombre, nbCar, file);
                
                optfichier = true;
                fclose(file);
                break;*/

            case 'm': 
                miller = true;
                break;
        }
    } 

    mpz_t aTester;
        mpz_init_set_str(aTester, argv[optind], 10);


	bool test;

    if(miller) test = Test_Miller_Rabin(aTester, 50);
    else test = Test_Fermat(aTester, 50);

    gmp_printf("Le nombre soumis est %s \n", test ? "premier" : "composé");

	mpz_clear(aTester);

    return 0;
}
