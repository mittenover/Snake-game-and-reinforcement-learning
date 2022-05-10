#ifndef GAMEENV_H
#define GAMEENV_H

#include <stdio.h>
#include <stdlib.h>


char** grid;
int** visited;
int dim;
int start_row;
int start_col;
int state_row;
int state_col;
int goal_row;
int goal_col;

enum terrain{
    wall,
    fruit,
    snake
};

enum action{
     up,
     down,
     left,
     right,
     number_actions 
};

struct envOutput{
  int new_col;
  int new_row;
  int reward;
  int done;
};

void alloc_grid();

void grid_make(int);

void grid_render(); 

void new_fruit();


#endif