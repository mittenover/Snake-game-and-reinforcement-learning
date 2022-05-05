#include <time.h>
#include <math.h>

#include "mazeEnv.h"
#include "Qlearning.h"


int dfs(int row, int col){
    int* current = &visited[row][col];

    if(*current == goal){
        return 1;
    }else if(*current == unknown){
        *current = known;

        if (dfs(row, col-1)){
            *current = crumb;
            return 1;
        } else if (dfs(row+1, col)){
            *current = crumb;
            return 1;
        }  else if (dfs(row, col+1)){
            *current = crumb;
            return 1;
        }  else if (dfs(row-1, col)){
            *current = crumb;
            return 1;
        }

    }

    return 0;
}


int main(int argc, char *argv[]){


    if (argc != 2)
    {
        printf("Erreur : pas de fchier en entrée.\n");
        return 0;
    }
    // On redéfinit l'aléatoire
    srand(time(0));

    learn(argv[1]);
    
    free(table_reward);
    return 0;
}

