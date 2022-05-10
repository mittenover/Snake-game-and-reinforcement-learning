#include "functions.h"
#include "gameEnv.h"
#include "Qlearning.h"

int main(int argc, char const *argv[])
{
	if (argc != 1)
	{
		printf("Too much arguments.\n");
		return 0;
	}

	
start_col=5;
start_row=8;

	alloc_grid();
	grid_make(17);
	grid_render();
	init_snake();
	grid_render();
	


	
	return 0;
}