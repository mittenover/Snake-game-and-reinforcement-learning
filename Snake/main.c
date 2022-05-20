#include "functions.h"
#include "gameEnv.h"
#include "Qlearning.h"
#include "string.h"
#include <time.h>

void test_snake()
{
	char entree[100] = "\n";
	is_a_fruit_ahead();
	printf("u:%d, ",is_a_obstacle_up());
	printf("d:%d, ",is_a_obstacle_down());
	printf("r:%d, ",is_a_obstacle_right());
	printf("l:%d\n",is_a_obstacle_left());

	while(strcmp(entree, "q\n") != 0)
	{

		printf("Score : %d\n", taille_queue(queue));

		printf("Action suivante : ");
		fgets(entree, 100, stdin);
		if (strcmp(entree, "u\n") == 0)
		{
			if (step_forward(up) == 2)
			{
				printf("Game over !\n");
				break;
			}
			grid_render();
		}

		if (strcmp(entree, "d\n") == 0)
		{
			if (step_forward(down) == 2)
			{
				printf("Game over !\n");
				break;
			}
			grid_render();
		}

		if (strcmp(entree, "l\n") == 0)
		{
			if (step_forward(left) == 2)
			{
				printf("Game over !\n");
				break;
			}
			grid_render();
		}

		if (strcmp(entree, "r\n") == 0)
		{
			if (step_forward(right) == 2)
			{
				printf("Game over !\n");
				break;
			}
			grid_render();
		}

		is_a_fruit_ahead();
		printf("u:%d, ",is_a_obstacle_up());
		printf("d:%d, ",is_a_obstacle_down());
		printf("r:%d, ",is_a_obstacle_right());
		printf("l:%d\n",is_a_obstacle_left());
	}
}

int main(int argc, char const *argv[])
{
	if (argc != 1)
	{
		printf("Too much arguments.\n");
		return 0;
	}

	srand(time(0));
	nfruit=malloc(sizeof(struct ffruit)); //Allocation dynamique du fruit (variable globale), on le désalloue à la fin du main

	dim=17;
	start_col=5;
	start_row=8;

	alloc_grid();
	alloc_grid_terrain();
	grid_make();
	init_new_game();
	grid_render();
	step_forward(up);
	grid_render();
	init_snake();
	grid_render();

	// Tests sur les fonctions du Q learning
	table_reward = alloc_table_reward();
	fill_table(table_reward);
	table_reward = reset_table_reward(table_reward);
	// table_reward = reset_table_reward(table_reward);

	// // Jouer avec le snake
	// test_snake();

	// // On recommence le jeu
	// init_new_game();
	// grid_render();
	// test_snake();

	
	// Suppression des alloc
	while(queue != NULL)
	{
		free(queue->elem);
		queue = queue->next;
	}
	free(queue);
	free(nfruit);
	free(table_reward);
	printf("Le jeu s'est arrêté correctement.\n");
	return 0;
}