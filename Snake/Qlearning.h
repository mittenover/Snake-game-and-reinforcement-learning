#ifndef QLEARNING_H
#define QLEARNING_H

#include <stdlib.h>
#include <stdio.h>

#include "gameEnv.h"

double****** table_reward;
double alpha;
double epsilon;

double****** alloc_table_reward();

double max_future_state();

void fill_table(double****** table_reward);

void learn();

bool one_learning();

#endif