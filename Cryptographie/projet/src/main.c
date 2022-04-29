#include "fonc.h"


int main(int argc, char *argv[]) {

    int option;
    bool miller = false;
    bool optfichier = false;
    bool  hexa = false;
    char *nombre = argv[argc-1];


    while( (option = getopt(argc, argv, "f:mx")) != -1) {
        switch (option) {
            case 'f':
                FILE *file;
                file = fopen(optarg, "r");
                if(!file) {
                    printf("ERREUR : Impossible d'ouvrir le fichier %s\n", optarg);
                    return 10;
                }
                unsigned long int nbCar;
                fseek(file, 0, SEEK_END);
                nbCar = ftell(file);
                nbCar++;
                rewind(file);
                nombre = malloc(nbCar*sizeof(char));
                fgets(nombre, nbCar, file);
                
                fclose(file);
                optfichier = true;
                break;

            case 'm': 
                miller = true;
                break;

            case 'x':
                hexa = true;
                break;

            default:
                printf("ERREUR : Option %d non reconnu\n", option);
                return 11;
        }
    } 

    if(optfichier && (optind != argc)) {
        printf("USAGE : %s -f chemin_fichier\n", argv[0]);
        free(nombre);
        return 12;
    }

    if(!optfichier && (optind != argc-1)) {
        printf("USAGE : %s -[mx] nombre_a_tester\n", argv[0]);
        return 13;
    }

    mpz_t aTester;
    if(hexa) mpz_init_set_str(aTester, nombre, 16);
    else mpz_init_set_str(aTester, nombre, 10);
    if(optfichier) free(nombre);


	bool test;

    if(miller) test = Test_Miller_Rabin(aTester, 30);
    else test = Test_Fermat(aTester, 60);

    gmp_printf("Le nombre soumis est %s \n", test ? "premier" : "composé");

	mpz_clear(aTester);

    return 0;
}
