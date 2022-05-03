#ifndef QLEARNING_H
#define QLEARNING_H

#include <stdlib.h>
#include <stdio.h>

#include "gameEnv.h"

double alpha;
double epsilon;

double***** alloc_table_reward();

void fill_table(double***** table_reward);

void learn();



#endif