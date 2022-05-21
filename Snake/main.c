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


// Joue une partie après avoir appris un certains nombre de fois
void play_after_learning()
{
	init_new_game();
	grid_render();

	char entree[100] = "\n";

	action a;
	int step_value = 1;
	int d_u;
	int d_d;
	int d_l;
	int d_r;
	int f_ahead;

	while(step_value != 2)
	{
		d_u = is_a_obstacle_up();
		d_d = is_a_obstacle_down();
		d_l = is_a_obstacle_left();
		d_r = is_a_obstacle_right();
		f_ahead = is_a_fruit_ahead();

		a = choose_max_action(d_u, d_d, d_l, d_r, f_ahead);
		printf("Action choosen %d\n", a);
		step_value = step_forward(a);

		grid_render();

		printf("Mouvement suivant");
		fgets(entree, 100, stdin);
	}

}


void learning(){
	char entree[100] = "\n";
	int nb_apprentissages = 0;

	// Initaialisation
	table_reward = alloc_table_reward();
	fill_table(table_reward);

	while(strcmp(entree, "q\n") != 0)
	{	
		for (int i = 0; i < 1000; ++i)
		{
			one_learning();
			nb_apprentissages++;
		}
		printf("Nombres d'apprentissages : %d\n", nb_apprentissages);

		grid_render();

		printf("Continuer à apprendre ?\n");
		fgets(entree, 100, stdin);

		if (strcmp(entree, "p\n") == 0)
		{
			play_after_learning();
		}
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

	// Tests sur les fonctions du Q learnings
	learning();

	// // Jouer avec le snake
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