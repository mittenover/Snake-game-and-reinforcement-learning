#ifndef QLEARNING_H
#define QLEARNING_H

#include <stdlib.h>
#include <stdio.h>

#include "mazeEnv.h"

double** table_reward;
double alpha;
double epsilon;

void alloc_table_reward();

void fill_tableau();

void print_table_reward();

double max_future_state(int s);

int action_to_int(action a);

void learn();

int dfs2();

void add_crumbs();

action next_move();


#endif