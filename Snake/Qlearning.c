#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Qlearning.h"
#include "gameEnv.h"
#include "functions.h"

// Remarque: on prend la valeur 15 parce qu'on part du principe que la taille du jeu est (17x17)

double****** alloc_table_reward()
{
	double****** table_reward = malloc(sizeof(double*****)*15);

	for (int i = 0; i < 15; ++i)
	{
		table_reward[i] = malloc(sizeof(double****)*15);

		for (int j = 0; j < 15; ++j)
		{
			table_reward[i][j] = malloc(sizeof(double***)*15);

			for (int k = 0; k < 15; ++k)
			{
				table_reward[i][j][k] = malloc(sizeof(double**)*15);

				for (int l = 0; l < 15; ++l)
				{
					table_reward[i][j][k][l] = malloc(sizeof(double*)*5);

					for (int m = 0; m < 5; ++m)
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
double max_future_state(int d_u, int d_d, int d_l, int d_r, int f_ahead)
{
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

// ERREUR DE SEGMENTATION
void fill_table(double****** table_reward)
{
	for (int i = 0; i < 15; ++i)
	{
		for (int j = 0; j < 15; ++j)
		{
			for (int k = 0; k < 15; ++k)
			{
				for (int l = 0; l < 15; ++l)
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
int one_learning(){

	init_new_game();

	// VARIABLE :
	double r; // Récompense
	enum action a; // Action choisie
	struct envOutput state; // Structure donnant les informations sur l'état après l'action dans l'environnement
	double max_future_s;

	// Paramètre de l'algorithme de Qlearning
	double g = 0.9;
	alpha = 0.1;

	// Distances des obstacles dans chaque directions
	int d_u;
	int d_d;
	int d_l;
	int d_r;
	// Précédents
	int p_d_u;
	int p_d_d;
	int p_d_l;
	int p_d_r;

	// Présence d'un fruit et dans quelle direction
	int f_ahead;
	// Précédent
	int p_f_ahead;

	// Action choisie
	int a_nb;

	// Score
	int score;
	// Précédent
	int p_score;

	// Compteur d'itération
	int compteur = 0;

	// Variable qui enregistre le resultat de step_forward
	int step_forward_value = 1;

	// Initialisation
	d_u = is_a_obstacle_up();
	d_d = is_a_obstacle_down();
	d_l = is_a_obstacle_left();
	d_r = is_a_obstacle_right();
	p_d_u = d_u;
	p_d_d = d_d;
	p_d_l = d_l;
	p_d_r = d_r;

	f_ahead = is_a_fruit_ahead();
	p_f_ahead = f_ahead;

	a = env_action_sample();
	a_nb = a;

	while(compteur < 1000) // Définir la condition d'arrêt
		{
			state = game_step(a);
			step_forward_value = state.step_value;

			// grid_render();

			// Lit la récompense
			r = state.reward;

			// Actualisation des paramètres d'indices du tableau Q (correspondant à l'état futur)
			d_u = is_a_obstacle_up();
			d_d = is_a_obstacle_down();
			d_l = is_a_obstacle_left();
			d_r = is_a_obstacle_right();

			f_ahead = is_a_fruit_ahead();

			score = taille_queue(queue); 

			max_future_s = max_future_state(d_u, d_d, d_l, d_r, f_ahead); // max_future_state();

			// Actualisation du tableau Q
			table_reward[p_d_u][p_d_d][p_d_l][p_d_r][p_f_ahead][a_nb] = table_reward[p_d_u][p_d_d][p_d_l][p_d_r][p_f_ahead][a_nb] + alpha*(r + g*max_future_s - table_reward[p_d_u][p_d_d][p_d_l][p_d_r][p_f_ahead][a_nb]);

			// Indentation 
			compteur++;

			// Actualisation
			a = env_action_sample(); // Action future
			a_nb = a;
			p_d_u = d_u;
			p_d_d = d_d;
			p_d_l = d_l;
			p_d_r = d_r;
			p_f_ahead = f_ahead;
		}
	return score; // Renvoie le score pour information
}

action choose_max_action(int d_u, int d_d, int d_l, int d_r, int f_ahead)
{
	int max = table_reward[d_u][d_d][d_l][d_r][f_ahead][up];
	action max_action = up;

	if (table_reward[d_u][d_d][d_l][d_r][f_ahead][down] > max)
	{
		max = table_reward[d_u][d_d][d_l][d_r][f_ahead][down];
		max_action = down;
	}
	if (table_reward[d_u][d_d][d_l][d_r][f_ahead][left] > max)
	{
		max = table_reward[d_u][d_d][d_l][d_r][f_ahead][left];
		max_action = left;
	}
	if (table_reward[d_u][d_d][d_l][d_r][f_ahead][right] > max)
	{
		max = table_reward[d_u][d_d][d_l][d_r][f_ahead][right];
		max_action = right;
	}

	return max_action;
}