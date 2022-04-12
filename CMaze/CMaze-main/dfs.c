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


int main(){

    learn();

    // On trouve le chemin :
    dfs2(start_row,start_col);
    add_crumbs();

    // On affiche le chemin :
    maze_render();

    // On peut éventuellement afficher te tableau Q
    print_table_reward();

    return 0;
}

