#include "fonc.h"

// Fonction principale du programme
int main(int argc, char *argv[]) {

    char *nombre = argv[argc-2];

    //Gestion des options
    int option;
    bool miller = false;
    bool optfichier = false;
    bool  hexa = false;


    while( (option = getopt(argc, argv, "f:mx")) != -1) {
        switch (option) {
            // Option lecture dans un fichier
            case 'f':
                FILE *file;
                file = fopen(optarg, "r");
                if(!file) {
                    fprintf(stderr, "ERREUR : Impossible d'ouvrir le fichier %s\n", optarg);
                    return 10;
                }
                unsigned long int nbCar;
                fseek(file, 0, SEEK_END);
                nbCar = ftell(file);
                nbCar++;
                rewind(file);
                nombre = malloc(nbCar*sizeof(char));
                if(!nombre) {
                    fprintf(stderr, "ERREUR : Echec de l'allocation du nombre\n");
                    return 11;
                }
                fgets(nombre, nbCar, file);
                
                fclose(file);
                optfichier = true;
                break;

            // Option Test de Miller-Rabin
            case 'm': 
                miller = true;
                break;

            // Option écriture en base 16
            case 'x':
                hexa = true;
                break;

            // Gestion des mauvaises options
            default:
                fprintf(stderr, "ERREUR : Option %d non reconnu\n", option);
                return 12;
        }
    } 

    // Gestion du mauvaise usage
    if(optfichier && (optind != argc-1) ) {
        fprintf(stderr, "USAGE : %s -f chemin_fichier nb_iterations\n", argv[0]);
        free(nombre);
        return 13;
    }

    if(!optfichier && (optind != argc-2) ) {
        fprintf(stderr, "USAGE : %s -[mx] nombre_a_tester nb_iterations\n", argv[0]);
        return 14;
    }

    // Gestion du nombre d'itérations
    unsigned int nbIter;
    nbIter = atoi(argv[argc-1]);
    if(!nbIter) {
        fprintf(stderr, "ERREUR : %s n'est pas un nombre d'itérations valide\n", argv[argc-1]);
        return 15;
    }

    // Initialisation du nombre à tester
    mpz_t aTester;
    if(hexa) mpz_init_set_str(aTester, nombre, 16);
    else mpz_init_set_str(aTester, nombre, 10);
    if(optfichier) free(nombre);


    // Test de primalité
	bool test;

    if(!mpz_cmp_ui(aTester, 2)) {
        test = PREMIER;
    }

    else {
        if(miller) test = Test_Miller_Rabin(aTester, nbIter);
        else test = Test_Fermat(aTester, nbIter);
    }

    // Affichage du résultat
    gmp_printf("Le nombre soumis est %s \n", test ? "premier" : "composé");

	mpz_clear(aTester);

    return 0;
}
