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

action next_move(){ // La fonction env_action_sample fait déjà le travail
    return env_action_sample2();
}


int dfs2(int row, int col){
    // int* current = &visited[row][col];

    state_row = start_row;
    state_col = start_col;

    envOutput next;

    // while ((state_row =! goal_row) || (state_col != goal_col))
    for (int i = 0; i < 10; ++i) // On teste pour 10 répététions
    {
        next = maze_step(next_move());
        state_row = next.new_row;
        state_col = next.new_col;
        visited[state_row][state_col] = crumb;
    }

    return 1;
}

void add_crumbs(){
     for (int i=0; i<rows; i++){
          for (int j=0; j<cols; j++){
              if (visited[i][j] ==crumb){
                  maze[i][j] ='.';
              }
          }
     }
     maze[start_row][start_col]= 's';
}

int main(){
    printf("left %d\n", left);
   maze_make("maze.txt");
   init_visited();

   printf("%d, %d \n", rows, cols);
   printf("  of actions :  %d \n", number_actions); 
   maze_render();



   // Apprentissage :
   alloc_table_reward();
   fill_tableau();
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

