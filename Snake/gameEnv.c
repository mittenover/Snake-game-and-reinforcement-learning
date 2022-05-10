#include "gameEnv.h" 
#include "Qlearning.h"

void alloc_grid(){  //On alloue dynamiquement un tableau carré de caractère de la taille de la dimension
     grid = malloc(dim * sizeof(char*));

     for(int i=0; i<dim; i++) {
         grid[i] = malloc(dim * sizeof(char*));
     }
}

void grid_make(int size){
	for(int i=0;i<size;++i){
		grid[i][0]='+';
		grid[0][i]='+';
		grid[size-1][i]='+';
		grid[0][size-1]='+';
	}
}

void grid_render(){
     for (int i=0; i<dim; i++) {
         for (int j=0; j< dim; j++){
             printf("%c ", grid[i][j]);
         }
         printf("\n");
     }
     printf("\n");
}


void new_fruit(){
	int i=rand()%dim;
	int j=rand()%dim;
	int k=0;
	while((grid[i][j]==wall)&&(k<100*size**2)){
		i=rand()%dim;
		j=rand()%dim;
		k+=1;
	}
	grid[i][j]='°';

}
