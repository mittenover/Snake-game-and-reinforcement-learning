#ifndef GAMEENV_H
#define GAMEENV_H

#include <stdio.h>
#include <stdlib.h>

char** maze;
int rows;
int cols;
int start_row;
int start_col;
int state_row;
int state_col;

// For the ghosts
int start_row_ghost[4];
int start_col_ghost[4];
int state_row_ghost[4];
int state_col_ghost[4];

enum terrain{
    unknown,
    wall,
    dot,
    candie,
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



#endif