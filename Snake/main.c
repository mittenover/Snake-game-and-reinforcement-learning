#include "functions.h"
#include "gameEnv.h"
#include "Qlearning.h"
#include "string.h"
#include <time.h>

void test_snake()
{
	char entree[100] = "\n";
	while(strcmp(entree, "q\n") != 0)
	{

		printf("Score : ");
		taille_queue(queue);
		actualize_terrain();

		fgets(entree, 100, stdin);
		if (strcmp(entree, "u\n") == 0)
		{
			step_foward(up);
			if (is_a_fruit_ahead(up))
			{
				printf("There is a fruit ahead !\n");
			}
			grid_render();
		}

		if (strcmp(entree, "d\n") == 0)
		{
			step_foward(down);
			if (is_a_fruit_ahead(down))
			{
				printf("There is a fruit ahead !\n");
			}
			grid_render();
		}

		if (strcmp(entree, "r\n") == 0)
		{
			step_foward(right);
			if (is_a_fruit_ahead(right))
			{
				printf("There is a fruit ahead !\n");
			}
			grid_render();
		}

		if (strcmp(entree, "l\n") == 0)
		{
			step_foward(left);
			if (is_a_fruit_ahead(left))
			{
				printf("There is a fruit ahead !\n");
			}
			grid_render();
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
	actualize_terrain();
	grid_render();
	init_snake();
	grid_render();
	test_snake();
	
	while(queue != NULL)
	{
		free(queue->elem);
		queue = queue->next;
	}
	free(queue);
	free(nfruit);
	return 0;
}