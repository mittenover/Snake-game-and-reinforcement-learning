#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Qlearning.h"
#include "gameEnv.h"

double***** alloc_table_reward()
{
	// On est obligé de créer 5 boucle pour créer un tableau de flottant à 5 dimensions
	double***** table_reward = malloc(sizeof(double****)*dim);

	for (int i = 0; i < dim; ++i)
	{
		table_reward[i] = malloc(sizeof(double***)*15);

		for (int j = 0; j < dim; ++j)
		{
			table_reward[i][j] = malloc(sizeof(double**)*15);

			for (int k = 0; k < dim; ++k)
			{
				table_reward[i][j][k] = malloc(sizeof(double*)*15);

				for (int l = 0; l < dim; ++l)
				{
					table_reward[i][j][k][l] = malloc(sizeof(double)*5);
				}
			}
		}
	}

	return table_reward;
}


void fill_table(double***** table_reward)
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
						table_reward[i][j][k][l][m] = rand() % 2;
					}
				}
			}
		}
	}

	return;
}