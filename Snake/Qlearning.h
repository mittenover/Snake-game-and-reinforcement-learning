#ifndef QLEARNING_H
#define QLEARNING_H

#include <stdlib.h>
#include <stdio.h>

#include "gameEnv.h"

double****** table_reward;
double alpha;
double epsilon;

double****** alloc_table_reward();

double****** reset_table_reward(double****** table_reward);

double max_future_state();

void fill_table(double****** table_reward);

int one_learning();

double max_future_state(int d_u, int d_d, int d_l, int d_r, int f_ahead);

action choose_max_action(int d_u, int d_d, int d_l, int d_r, int f_ahead);

#endif