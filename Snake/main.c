#include "functions.h"
#include "gameEnv.h"
#include "Qlearning.h"
#include <time.h>

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
	grid_make();
	grid_render();
	new_fruit();
	init_snake();
	grid_render();
	n_eat_a_fruit(up);
	grid_render();
	n_eat_a_fruit(up);
	grid_render();
	n_eat_a_fruit(up);
	grid_render();
	n_eat_a_fruit(up);
	grid_render();
	n_eat_a_fruit(left);
	grid_render();
	
	while(queue != NULL)
	{
		free(queue->elem);
		queue = queue->next;
	}
	free(queue);
	free(nfruit);
	return 0;
}