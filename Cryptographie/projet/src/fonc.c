#include "fonc.h"

/* Performe une exponentiation rapide avec l'algorithme Square & Multiply.
 * Cette opération est modulaire.
 * 
 * paramètres :
 *		retour 		in/out 		variable contenant le resultat de l'exponentiation
 *		a			in			variable contenant la base de l'exponentiation
 *		mod 		in			variable contenant le modulo de l'opération modulaire
 *		exp 		in			variable contenant l'exposant de l'exponentiation
 *	retour doit être initialisé avant d'être passé en argument.
 */
void Square_Multiply (mpz_t retour, const mpz_t a, const mpz_t mod, const mpz_t exp) {
	// Initialisation de retour à la base
    mpz_set(retour, a);

	// initialisation de t à la taille en bits de l'exposant
    mp_size_t t;
    t = mpz_sizeinbase(exp, 2);
    mp_size_t i;

	// Boucle principaple de l'algorithme
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

/* Fonction performant une test de Fermat un certain nombre de fois.
 * Elle renvoie faux si le nombre est composé, elle renvoie vrai sinon.
 *
 * paramètres :
 * 		n			in			Variable contenant le nombre à tester
 *		nbRep		in			Variable contenant le nombre de répétitions du test à effectuer
 */

bool Test_Fermat(const mpz_t n, unsigned int nbRep)  {
	// Initialisation de la valeur de retour
	bool retour;
	retour = PREMIER;

	// Initialisation de deux constantes nécessaires plus tard
	mpz_t nMoins1, nMoins2;

	mpz_init_set(nMoins1, n);
	mpz_sub_ui(nMoins1, nMoins1, 1);

	mpz_init_set(nMoins2, n);
	mpz_sub_ui(nMoins2, nMoins2, 2);

	// Initialisation de la graine aléatoire
	gmp_randstate_t state;
	gmp_randinit_mt(state);
	gmp_randseed_ui(state, time(0));

	int i;
	// Boucle principale parallélisée
	#pragma omp parallel for shared(retour)
	for(i = 0; i < nbRep; i++) {
		// Si on sait déjè que n est composé ne rien faire
		if(!retour) continue;
		// Initialisation de a le nombre nombre aléatoire de cette itération
		mpz_t a, res;
		mpz_init(a);
		// Initialisation de res qui contiendra le résultat de l'exponentiation a^(n-1) % n
		mpz_init(res);

		// Tirage aléroire de a entre 0 et n-2
		mpz_urandomm(a, state, nMoins2);
		// On incrémente a pour qu'il soit dans l'ensemble {1,...,n-1}
		mpz_add_ui(a, a, 1);

		// Exponentiation rapide de a^(n-1) mod n
		Square_Multiply (res, a, n, nMoins1);
		// Si a^(n-1) = 1 mod n alors n est composé
		if(mpz_cmp_ui(res, 1)){
			retour = COMPOSE;
		}
		mpz_clear(a);
		mpz_clear(res);
	}
	// Libération des variables
	gmp_randclear(state);
	mpz_clear(nMoins1);
	mpz_clear(nMoins2);

	// Renvoie du résultat des tests 
	return retour;
}

/* Fonction décomposant n-1 en 2^s * t 
 * Elle divise n-1 par 2 jusqu'à obtenir un nombre impair qui est t.
 * Le nombre de fois où n-1 se divise par 2 est s.
 * 
 * paramètres :
 * 		n		in		Variable contenant le nombre à décomposer après décrémentation
 *		s		inout	Variable contenant le résultat de la décomposition (exposant)
 *		t		inout	Variable contenant le résultat de la décomposition (nombre impair)
 *	s et t doivent être initialisés avant d'être passés en arguments.
 */
void Decomposition (const mpz_t n, mpz_t s, mpz_t t) {
	// Initialisation d'un x à n-1
	mpz_t x;
	mpz_init_set(x, n);
	mpz_sub_ui(x, x, 1);

	// Tant que x est divisible par 2, on le divise par deux et on incrémente s
	while(!(mpz_fdiv_ui(x, 2))) {
		mpz_div_ui(x, x, 2);
		mpz_add_ui(s, s, 1);
	}
	// Lorque x n'est plus pair alors, on a le t que l'on cherchait
	mpz_set(t, x);
	mpz_clear(x);

	return;
}

/* Fonction performant un test de Miller-Rabin un certain nombre de fois.
 * Elle renvoie faux si le nombre est composé, elle renvoie vrai sinon.
 *
 * paramètres :
 *		n		in			Variable contenant le nombre à tester
 *		nbRep	in			Variable contenant le nombre de répétition du test à effectuer
 */

bool Test_Miller_Rabin (const mpz_t n, unsigned int nbRep) {
	// Initialisation des résultats de la décomposition
	mpz_t s, t;
	mpz_init(s);
	mpz_init(t);
	Decomposition(n, s, t);
	mpz_sub_ui(s, s, 1);

	// Initialisation de la graine aléatoire
	gmp_randstate_t state;
	gmp_randinit_mt(state);
	gmp_randseed_ui(state, time(0));

	// Initialisation de constantes qui serviront plus tard
	mpz_t nMoins1;
	mpz_init_set(nMoins1, n);
	mpz_sub_ui(nMoins1, nMoins1, 1);

	mpz_t nMoins2;
	mpz_init_set(nMoins2, n);
	mpz_sub_ui(nMoins2, nMoins2, 2);

	
	// Initialisation de la variable contenant la valeur de retour
	bool retour = PREMIER;
	int i;
	unsigned long int j;
	// Boucle principale parallélisée
	#pragma omp parallel for shared(retour)
	for(i = 0; i < nbRep; i++) {
		// Si on sait déjà que le nombre est composé ne rien faire
		if(!retour) continue;
		// Initialisation du nombre aléatoire et du résultat de l'exponentiation rapide
		mpz_t a, y;
		mpz_init(a);
		mpz_init(y);

		// Tirage du nombre alétoire dans {0,..,n-2}
		mpz_urandomm(a, state, nMoins2);
		// Décrémentation pour que a soit dans {1,...,n-1}
		mpz_add_ui(a, a, 1);

		// Exponentiation rapide y = a^t mod n
		Square_Multiply(y, a, n, t);

		// Si y != 1 mod n et y != -1 mod n => y != n-1 mod n
		// En effet la fonction mpz_mod renvoie toujours un nombre positif ou nul
		if(mpz_cmp_ui(y, 1) && mpz_cmp(y, nMoins1)) {
			// Pour j de 0 à s-2 (on l'a décrémenté avant)
			for(j = 0; mpz_cmp_ui(s, j); j++) {
				// Si on sait déjà que le nombre est composé on sort de la boucle j
				if(!retour) break;
				// y = y^2 mod n
				mpz_mul(y, y, y);
				mpz_mod(y, y, n);
				// Si y = 1 mod n => n est composé
				if(mpz_cmp_ui(y, 1))
					retour = COMPOSE;

				// Si y = -1 mod n => on sort de la boucle j
				if(mpz_cmp(y, nMoins1))
					goto yModnEgalMoinsUn;
			}
			retour = COMPOSE;		
		}
		yModnEgalMoinsUn:
			mpz_clear(a);
			mpz_clear(y);
	}

	// Libération des variables
	gmp_randclear(state);
	mpz_clear(s);
	mpz_clear(t);
	mpz_clear(nMoins1);
	mpz_clear(nMoins2);
	
	// Renvoie du résultat
	return retour;
}