#ifndef MAZEENV_H
#define MAZEENV_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


char** maze;
int** visited;
int rows;
int cols;
int start_row;
int start_col;
int state_row;
int state_col;
int goal_row;
int goal_col;

enum terrain{
    unknown,
    wall,
    known,
    goal,
    crumb
};

enum action{
     up,
     down,
     left,
     right,
     number_actions 
};
 
typedef enum action action ;

struct envOutput{
  int new_col;
  int new_row;
  int reward;
  int done;

};

typedef struct envOutput envOutput;

void alloc_maze();

void maze_make(char* );

void maze_render(); 

void maze_reset();

envOutput maze_step(action a); 

action env_action_sample();

action env_action_sample2();

action env_action_greedy(double epsilon);

action env_action_boltzmann(int s, action a);

void alloc_visited();

void init_visited();

void delete_crumb();

void delete_point();

#endif /* MAZEENV_H */
