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


// Effectue une boucle d'apprentissage: part de l'état initial, va jusqu'à l'état final ou s'arrête au bout d'un certain nombre d'itérations
void one_learning(){

	// Variables :
	double r; // Variable correspondant à la récompense
	action a;
	int a_nb;
	int s; // Ligne correspondant à l'état actuel
	int future_s; //Ligne correspondant à l'état futur
	double max_future_s; // Calcul de max(Q(s', a))
	envOutput state;
	double g = 0.9;
	alpha = 0.02;


	// Initialisation 
	grid_reset();
	s = start_row*cols + start_col; // Etat initial

	while(s != goal_row*cols + goal_col)
		{

			// Choix de l'action: (POUR L'INSTANT ON LA PREND ALEATOIRE)
			a = env_action_greedy();
			a_nb = action_to_int(a);

			state = maze_step(a);

			// Effectue l'action et en déduit une récompense, et la valeur de l'état futur :
			r = state.reward;
			future_s = state.new_row*cols + state.new_col;

			max_future_s = max_future_state(future_s);

			table_reward[s][a_nb] = table_reward[s][a_nb] + alpha *(r + g * max_future_s - table_reward[s][a_nb]);

			state_row = state.new_row;
			state_col = state.new_col;
			s = future_s;
			// visited[state_row][start_col] = unknown;
		}
}


// Fonction d'apprentissage
void learn(char *maze)
{
	// On va apprendre progressivement, en traçant à chaque tur de boucle le trajet choisi par le tableau Q calculé
	// En gros on reprend la structure du main mais on le boucle

	// Initialisation du jeu
	grid_make(dim);

    printf("Dimension du tableau : %d x %d.\n", dim, dim);
    grid_render();

    // Initialisation du tableau Q
    table_reward = alloc_table_reward();
    fill_tableau(table_reward);

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


		// Vérification du tableau Q
		if (strcmp(entree, "q\n") == 0)
		{
			printf("\nAffichage du tableau Q :\n");
			print_table_reward();

		// On entre si on souhaite continuer
		printf("Continuer ? ");
		fgets(entree, 100, stdin);
		}

		// On peut ajouter l'option reset, qui réinitialise le tableau Q
		// Ne fonctionne pas pour le moment
		if (strcmp(entree, "r\n") == 0)
		{
			fill_tableau();
			number_learning = 0;
		}
	}
}