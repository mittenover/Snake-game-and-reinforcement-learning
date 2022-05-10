#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Qlearning.h"
#include "functions.h"
#include "mazeEnv.h"

/** On créée une fonction qui crée le tableau de récompenses
 * Il s'agira d'un tableau de taille (taille_tableau_labyrinthe)*(nb_d'actions)
**/

void alloc_table_reward()
{
	table_reward = malloc(sizeof(double*) * (rows*cols));
	for (int i = 0; i < rows*cols; ++i)
	{
		table_reward[i] = malloc(sizeof(double) * 4);
	}
}

void fill_tableau()
{
	for (int s = 0; s < rows*cols; ++s)
	{
		for (int a = 0; a < 4; ++a)
		{
			table_reward[s][a] = rand() % 2;
		}
	}
	for (int a = 0; a < 4; ++a)
	{
		table_reward[goal_row*cols + goal_col][a] = 0;
	}
	
}

/* Fonction qui affiche le tableau */

void print_table_reward()
{
	printf("\n");
	for (int s = 0; s < rows*cols; ++s)
	{
		if (s%cols == 0)
		{
			printf("\n%d\n\n", s/cols+1);
		}
		printf("%f | %f | %f | %f\n", table_reward[s][0], table_reward[s][1], table_reward[s][2], table_reward[s][3]);
	}
	printf("\n");
}


/**On peut maintenant commencer l'implémentation de l'aprendtissage par renforcement
 * 
 * On chosira les déplacements aléatoirement entre les 4 dimensions.
 * **/

/*Fonction qui calcule le maximum de la récompense à l'état suivant*/

double max_future_state(int s)
{
	double max = table_reward[s][0];

	for (int i = 1; i < 4; ++i)
	{
		if (table_reward[s][i] > max)
		{

			max = table_reward[s][i];
		}
	}

	return max;
}


/* Fonction qui transforme une valeur d'action en un entier pour faciliter le balayage dans le tableau */

int action_to_int(action a)
{
	if (a==up){return 0;}
	else if (a==down){return 1;}
	else if (a==right){return 2;}
	else {return 3;}
}


// La fonction env_action_sample fait déjà le travail
// Pour dfs2
action next_move(){
    int s = state_row*cols + state_col;
    double max = table_reward[s][0];
    action result = up;

    if (table_reward[s][1] > max)
    {
    	max = table_reward[s][1];
    	result = down;
    }
    if (table_reward[s][2] > max)
    {
    	max = table_reward[s][2];
    	result = right;
    }
    if (table_reward[s][3] > max)
    {
    	max = table_reward[s][3];
    	result = left;
    }
    return  result;
}


// Fonction qui trouve le chemin
int dfs2(){
    // int* current = &visited[row][col];

    state_row = start_row;
    state_col = start_col;

    envOutput next;

    delete_crumb(); //On enlève les crumbs éventuels

    // while ((state_row =! goal_row) || (state_col != goal_col))
    for (int i = 0; i < 1000; ++i) // On teste pour 10 répététions
    {
        next = maze_step(next_move());
        state_row = next.new_row;
        state_col = next.new_col;
        visited[state_row][state_col] = crumb;
    }

    return 1;
}


// Ajoute les points sur la map
void add_crumbs(){
     for (int i=0; i<rows; i++){
          for (int j=0; j<cols; j++){
              if (visited[i][j] ==crumb){
                  maze[i][j] ='.';
              }
              if (i == goal_row && j == goal_col) // Erreur sinon
              {
              	maze[i][j] = 'g';
              }
          }
     }
     maze[start_row][start_col]= 's';
}


// Effectue une boucle d'apprentissage: part de l'état initial, va jusqu'à l'état final ou s'arrête au bout d'un certain nombre d'itérations
void one_learning(){

	// Variables :
	double r; // Variable correspondant à la récompense
	action a;
	int a_nb;
	int s; // Ligne correspondant à l'état actuel
	int future_s; //Ligne correspondant à l'état futur
	double max_future_s; // Calcul de max(Q(s', a))
	envOutput state;
	double g = 0.9;
	alpha = 0.02;


	// Initialisation 
	maze_reset();
	s = start_row*cols + start_col; // Etat initial

	while(s != goal_row*cols + goal_col)
		{

			// Choix de l'action: (POUR L'INSTANT ON LA PREND ALEATOIRE)
			a = env_action_boltzmann(s);
			a_nb = action_to_int(a);

			state = maze_step(a);

			// Effectue l'action et en déduit une récompense, et la valeur de l'état futur :
			r = state.reward;
			future_s = state.new_row*cols + state.new_col;

			max_future_s = max_future_state(future_s);

			table_reward[s][a_nb] = table_reward[s][a_nb] + alpha *(r + g * max_future_s - table_reward[s][a_nb]);

			state_row = state.new_row;
			state_col = state.new_col;
			s = future_s;
			// visited[state_row][start_col] = unknown;
		}
}


//
void one_learning_sarsa(){

	// Variables :
	double r; // Variable correspondant à la récompense
	action a;
	action a2;
	int a_nb;
	int a_nb2;
	int s; // Ligne correspondant à l'état actuel
	int future_s; //Ligne correspondant à l'état futur
	double max_future_s; // Calcul de max(Q(s', a))
	envOutput state;
	double g = 0.9;
	alpha = 0.02;
	int old_state_row;
	int old_state_col;


	// Initialisation 
	maze_reset();
	s = start_row*cols + start_col; // Etat initial

	// Choix de l'action:
	a = env_action_greedy();
	a_nb = action_to_int(a);

	while(s != goal_row*cols + goal_col)
		{
			state = maze_step(a);

			// Effectue l'action et en déduit une récompense, et la valeur de l'état futur :
			r = state.reward;
			future_s = state.new_row*cols + state.new_col;

			// On réactualise la position pour que le choix de l'action a' se fasse par rapport à l'état futur :
			// On enregistre les aciennes positions :
			old_state_row = state_row;
			old_state_col = state_col;
			state_row = state.new_row;
			state_col = state.new_col;

			// Choix de l'action a2:
			a2 = env_action_greedy();
			a_nb2 = action_to_int(a);

			// On se replace dans l'état s
			state_row = old_state_row;
			state_col = old_state_col;

			table_reward[s][a_nb] = table_reward[s][a_nb] + alpha *(r + g * table_reward[s][a_nb2] - table_reward[s][a_nb]);

			state_row = state.new_row;
			state_col = state.new_col;
			s = future_s;
			a = a2;
			a_nb = action_to_int(a);
			// visited[state_row][start_col] = unknown;
		}
}

/* Fonction d'apprentissage */

void learn(char *maze)
{
	// On va apprendre progressivement, en traçant à chaque tur de boucle le trajet choisi par le tableau Q calculé
	// En gros on reprend la structure du main mais on le boucle

	// Initialisation du 
	printf("left %d\n", left);
    maze_make(maze);
    init_visited();

    printf("%d, %d \n", rows, cols);
    printf("Number of actions :  %d \n", number_actions); 
    maze_render();

    // Initialisation du tableau Q
    alloc_table_reward();
    fill_tableau();

    // Variable d'entrée clavier
    char entree[100] = "\n";

    //Nombre d'apprentissages
    int number_learning = 0;


	while(strcmp(entree, "\n") == 0 || strcmp(entree, "r\n") == 0)
	{
		// On fait une boucle d'apprentissage
		one_learning();
		number_learning++;



		// On trouve le chemin :
		maze_reset();
    	dfs2(start_row,start_col);
    	add_crumbs();

		// Puis on donne le tableau Q, et on trace le chemin trouvé
		// print_table_reward();

		maze_render();

		printf("Nombre d'apprentissages : %d\n\n", number_learning);

		// On entre si on souhaite continuer
		printf("Continuer ? ");
		fgets(entree, 100, stdin);

		// Affichage des commandes disponibles
		if (strcmp(entree, "c\n") == 0)
		{
		printf("\nLes commandes disponibles sont :\n");
		printf("- r pour reset : recommence l'apprentissage.\n");
		printf("- q pour afficher le tableau Q du Qlearning.\n");
		printf("- entrée pour continuer l'apprentissage.\n\n");

		// On entre si on souhaite continuer
		printf("Continuer ? ");
		fgets(entree, 100, stdin);
		}


		// Vérification du tableau Q
		if (strcmp(entree, "q\n") == 0)
		{
			printf("\nAffichage du tableau Q :\n");
			print_table_reward();

		// On entre si on souhaite continuer
		printf("Continuer ? ");
		fgets(entree, 100, stdin);
		}

		// On peut ajouter l'option reset, qui réinitialise le tableau Q
		// Ne fonctionne pas pour le moment
		if (strcmp(entree, "r\n") == 0)
		{
			// delete_point();
			// maze_render();
			fill_tableau();
			number_learning = 0;
		}
	}

}