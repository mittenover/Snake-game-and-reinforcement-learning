#ifndef GAMEENV_H
#define GAMEENV_H

#include <stdio.h>
#include <stdlib.h>


char** grid;
struct queue *queue;
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



struct bout_queue{    //Coordonnées d'un bout de queue
    int queue_col;
    int queue_row;
};

struct queue{     //Structure de liste représentant le serpent
    struct bout_queue *elem;
    struct queue *next;
};

void alloc_grid();

void grid_make(int);

void grid_render(); 

void new_fruit();

void init_snake();


#endif