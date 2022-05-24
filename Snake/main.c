#include "functions.h"
#include "gameEnv.h"
#include "Qlearning.h"
#include "string.h"
#include <time.h>

//Copié collé
void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;
  
    // Storing start time
    clock_t start_time = clock();
  
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}


void test_snake()
{
	init_new_game();
	grid_render();

	char entree[100] = "\n";
	printf("f:%d, ",is_a_fruit_ahead());
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

		printf("f:%d, ",is_a_fruit_ahead());
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

	char entree[100] = "\n";

	action a;
	int step_value = 1;
	int d_u;
	int d_d;
	int d_l;
	int d_r;
	int f_ahead;

	int iter_max = 0; // Pour éviter qu'il parte en boucle infinie

	while(step_value != 2 && iter_max<100)
	{
		d_u = is_a_obstacle_up();
		d_d = is_a_obstacle_down();
		d_l = is_a_obstacle_left();
		d_r = is_a_obstacle_right();
		f_ahead = is_a_fruit_ahead();

		a = choose_max_action(d_u, d_d, d_l, d_r, f_ahead);

		printf("Tableau Q : (u:%f, d:%f, l:%f, r:%f)\n", table_reward[d_u][d_d][d_l][d_r][f_ahead][0], table_reward[d_u][d_d][d_l][d_r][f_ahead][1], table_reward[d_u][d_d][d_l][d_r][f_ahead][2], table_reward[d_u][d_d][d_l][d_r][f_ahead][3]);
		printf("Etat : f:%d, ",f_ahead);
		printf("u:%d, ",d_u);
		printf("d:%d, ",d_d);
		printf("r:%d, ",d_r);
		printf("l:%d\n",d_l);
		grid_render();
		printf("Action choosen %d\n", a);

		step_value = step_forward(a);

		if (step_value == 0)
		{
			iter_max = 0;
		}

		printf("Mouvement suivant\n");
		// fgets(entree, 100, stdin);
		delay(20);

		if (strcmp(entree, "q\n") == 0)
		{
			break;
		}

		iter_max++;

	}

	if (iter_max == 1000)
	{
		printf("BOUCLE INFINIE - ");
	}
	printf("Score : %d\n", taille_queue(queue));

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

		// grid_render();

		printf("Continuer à apprendre ?\n");
		fgets(entree, 100, stdin);

		if (strcmp(entree, "p\n") == 0)
		{
			play_after_learning();

			// for (int i = 0; i < 19; ++i)
			// {
			// 	play_after_learning();
			// }
		}

		if (strcmp(entree, "r\n") == 0)
		{
			table_reward = reset_table_reward(table_reward);
			nb_apprentissages = 0;
		}

		if (strcmp(entree, "t\n") == 0)
		{
			test_snake();
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
	nfruit=malloc(sizeof(struct ffruit)); //Allocation dynamique du fruit (variable globale), on le désalloc à la fin du main

	dim=17;
	start_col=5;
	start_row=8;

	window = 1;

	printf("Nombre d'états : %d\n", window*window*window*window*5*4);

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