#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Qlearning.h"
#include "gameEnv.h"

double****** alloc_table_reward()
{
	// On est obligé de créer 5 boucle pour créer un tableau de flottant à 5 dimensions
	double****** table_reward = malloc(sizeof(double*****)*dim);

	for (int i = 0; i < dim; ++i)
	{
		table_reward[i] = malloc(sizeof(double****)*15);

		for (int j = 0; j < dim; ++j)
		{
			table_reward[i][j] = malloc(sizeof(double***)*15);

			for (int k = 0; k < dim; ++k)
			{
				table_reward[i][j][k] = malloc(sizeof(double**)*15);

				for (int l = 0; l < dim; ++l)
				{
					table_reward[i][j][k][l] = malloc(sizeof(double*)*5);

					for (int m = 0; m < 4; ++m)
					{
						
						table_reward[i][j][k][l][m] = malloc(sizeof(double)*4);
					}
				}
			}
		}
	}

	return table_reward;
}

// Renvoie la valeur maximale du tableau Q en balayant les actions de l'état futur
// Remarque : l'état futur correspond à l'état global, puisque celui-ci vient d'être actualisé par game_step
double max_future_state()
{
	// Distances des obstacles dans chaque directions
	int d_u;
	int d_d;
	int d_l;
	int d_r;

	// Présence d'un fruit et dans quelle direction
	int f_ahead;

	double max = table_reward[d_u][d_d][d_l][d_r][f_ahead][0];
	for (int i = 1; i < 4; ++i)
	{
		if ( max < table_reward[d_u][d_d][d_l][d_r][f_ahead][i])
		{
			max = table_reward[d_u][d_d][d_l][d_r][f_ahead][0];
		}
	}

	return max;
}


void fill_table(double****** table_reward)
{
	for (int i = 0; i < dim; ++i)
	{
		for (int j = 0; j < dim; ++j)
		{
			for (int k = 0; k < dim; ++k)
			{
				for (int l = 0; l < dim; ++l)
				{
					for (int m = 0; m < 5; ++m)
					{
						for (int n = 0; n < 4; ++n)
						{
						table_reward[i][j][k][l][m][n] = rand() % 2;
						}
					}
				}
			}
		}
	}
	return;
}

// Enter the table reward you want to reset it gives you a blank one.
double****** reset_table_reward(double****** table_reward)
{
	free(table_reward);

	double****** new_table_reward = alloc_table_reward();
	fill_table(new_table_reward);

	return new_table_reward;
}


// Effectue une boucle d'apprentissage: part de l'état initial, va jusqu'à l'état final ou s'arrête au bout d'un certain nombre d'itérations
bool one_learning(){

	// VARIABLE :
	double r; // Récompense
	enum action a; // Action choisie
	struct envOutput state; // Structure donnant les informations sur l'état après l'action dans l'environnement
	double max_future_s;

	// Paramètre de l'algorithme de Qlearning
	double g = 0.9;
	alpha = 0.02;

	// Distances des obstacles dans chaque directions
	int d_u;
	int d_d;
	int d_l;
	int d_r;

	// Présence d'un fruit et dans quelle direction
	int f_ahead;

	// Action choisie
	int a_nb;

	// Score
	int score;

	// Compteur d'itération
	int compteur;

	// Variable qui enregistre le resultat de step_forward
	int step_forward_value = 1;




	// Initialisation

	while(compteur < 1000 && step_forward_value != 2) // Définir la condition d'arrêt
		{

			// Choix de l'action:
			// a = env_action_sample(); // Attendre que la fonction soit définie dans gameEnv

			// state = env_step(a); // Attendre que la fonction soit définie dans gameEnv

			// Lit la récompense
			// r = state.reward;

			// Actualisation des paramètres d'indices du tableau Q
			d_u = is_a_obstacle_up();
			d_l = is_a_obstacle_down();
			d_l = is_a_obstacle_left();
			d_r = is_a_obstacle_right();

			f_ahead = is_a_fruit_ahead();

			score = taille_queue(queue);

			max_future_s = 0; // max_future_state();

			// Actualisation du tableau Q
			table_reward[d_u][d_d][d_l][d_r][f_ahead][a_nb] = table_reward[d_u][d_d][d_l][d_r][f_ahead][a_nb] + alpha*(r + g*max_future_s - table_reward[d_u][d_d][d_l][d_r][f_ahead][a_nb]);

			// Indentation 
			compteur++;
		}
}


// Fonction d'apprentissage
void learn(char *maze)
{
	// On va apprendre progressivement, en traçant à chaque tur de boucle le trajet choisi par le tableau Q calculé
	// En gros on reprend la structure du main mais on le boucle

	// Initialisation du jeu
	
    // Initialisation du tableau Q
    table_reward = alloc_table_reward();
    fill_table(table_reward);

    // Variable d'entrée clavier
    char entree[100] = "\n";

    //Nombre d'apprentissages
    int number_learning = 0;


	while(strcmp(entree, "\n") == 0 || strcmp(entree, "r\n") == 0)
	{
		// On fait une boucle d'apprentissage
		one_learning();
		number_learning++;

		printf("Nombre d'apprentissages : %d\n\n", number_learning);

		// On entre si on souhaite continuer
		printf("Continuer ? ");
		fgets(entree, 100, stdin);

		// Affichage des commandes disponibles
		if (strcmp(entree, "c\n") == 0)
		{
		printf("\nLes commandes disponibles sont :\n");
		printf("- r pour reset : recommence l'apprentissage.\n");
		printf("- q pour afficher le tableau Q du Qlearning.\n");
		printf("- entrée pour continuer l'apprentissage.\n\n");

		// On entre si on souhaite continuer
		printf("Continuer ? ");
		fgets(entree, 100, stdin);
		}
	}
}