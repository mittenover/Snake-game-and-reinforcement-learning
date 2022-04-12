#include <stdio.h>
#include <stdlib.h>

#include "Qlearning.h"
#include "functions.h"
#include "mazeEnv.h"

/** On créée une fonction qui crée le tableau de récompenses
 * Il s'agira d'un tableau de taille (taille_tableau_labyrinthe)*(nb_d'actions)
**/

void alloc_table_reward()
{
	table_reward = malloc(sizeof(double*) * (rows*cols));
	for (int i = 0; i < rows*cols; ++i)
	{
		table_reward[i] = malloc(sizeof(double) * 4);
	}
}

void fill_tableau()
{
	for (int s = 0; s < rows*cols; ++s)
	{
		for (int a = 0; a < 4; ++a)
		{
			table_reward[s][a] = rand() % 2;
		}
	}
	for (int a = 0; a < 4; ++a)
	{
		table_reward[goal_row*cols + goal_col][a] = 0;
	}
	
}

/* Fonction qui affiche le tableau */

void print_table_reward()
{
	printf("\n");
	for (int s = 0; s < rows*cols; ++s)
	{
		if (s%cols == 0)
		{
			printf("\n%d\n\n", s/cols+1);
		}
		printf("%f | %f | %f | %f\n", table_reward[s][0], table_reward[s][1], table_reward[s][2], table_reward[s][3]);
	}
	printf("\n");
}


/**On peut maintenant commencer l'implémentation de l'aprendtissage par renforcement
 * 
 * On chosira les déplacements aléatoirement entre les 4 dimensions.
 * **/

/*Fonction qui calcule le maximum de la récompense à l'état suivant*/

double max_future_state(int s)
{
	double max = table_reward[s][0];

	for (int i = 1; i < 4; ++i)
	{
		if (table_reward[s][i] > max)
		{
			max = table_reward[s][i];
		}
	}

	return max;
}


/* Fonction qui transforme une valeur d'action en un entier pour faciliter le balayage dans le tableau */

int action_to_int(action a)
{
	if (a==up){return 0;}
	else if (a==down){return 1;}
	else if (a==right){return 2;}
	else {return 3;}
}


/* Fonction d'apprentissage */

void learn()
{
	// Variables :

	int n = 0; // Nombre de répétition de la boucle
	double r; // Variable correspondant à la récompense
	action a;
	int a_nb;
	int s; // Ligne correspondant à l'état actuel
	int future_s; //Ligne correspondant à l'état futur
	double max_future_s; // Calcul de max(Q(s', a))
	envOutput state;
	double g = 0.9;
	alpha = 0.5;

	double max_occurence = 10000;

	while(n < max_occurence)
	{
		maze_reset();
		s = start_row*cols + start_col; // Etat initial

		while(s != goal_row*cols + goal_col)
		{

			// Choix de l'action: (POUR L'INSTANT ON LA PREND ALEATOIRE)
			a = env_action_sample();
			a_nb = action_to_int(a);

			state = maze_step(a);

			// Affichage de l'état actuel dans le labyrinthe

			// visited[state_row][state_col] = crumb;
			// maze_render();

			// Effectue l'action et en déduit une récompense, et la valeur de l'état futur :
			r = state.reward;
			future_s = state.new_row*cols + state.new_col;

			max_future_s = max_future_state(future_s);

			table_reward[s][a_nb] = table_reward[s][a_nb] + alpha *(r + g * max_future_s - table_reward[s][a_nb]);
		
			s = future_s;
			// visited[state_row][start_col] = unknown;
		}
		n++;
	}

}