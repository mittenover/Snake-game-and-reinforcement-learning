#include "gameEnv.h" 
#include "Qlearning.h"






void alloc_grid(){  //On alloue dynamiquement un tableau carré de caractère de la taille de la dimension
     grid = malloc(dim * sizeof(char*));

     for(int i=0; i<dim; i++) {
         grid[i] = malloc(dim * sizeof(char*));
     }
}

void alloc_grid_terrain(){
	grid_terrain = malloc(dim * sizeof(enum terrain*));

     for(int i=0; i<dim; i++) {
         grid_terrain[i] = malloc(dim * sizeof(enum terrain));
     }
}

void actualize_terrain(){
	for (int i = 0; i < dim; ++i)
	{
		for (int j = 0; j < dim; ++j)
		{
			if (grid[i][j] == '+')
			{
				grid_terrain[i][j] = wall;
			}
			else if (grid[i][j] == '.')
			{
				grid_terrain[i][j] = snake;
			}
			else if (grid[i][j] == 'f')
			{
				// printf("The fruit is in (%d, %d)\n", i, j);
				grid_terrain[i][j] = fruit;
			}
			else {grid_terrain[i][j] = blank;}
		}
	}
}


void grid_make(){
	for(int i=0;i<dim;++i){
		grid[i][0]='+';
		grid[0][i]='+';
		grid[dim-1][i]='+';
		grid[i][dim-1]='+';
	}

	for (int i = 0; i < dim; ++i)
	{
		for (int j = 0; j < dim; ++j)
		{
			if (grid[i][j] != '+' && grid[i][j] != '.')
			{
				grid[i][j] = ' ';
			}
		}
	}

	new_fruit();
}

// Entre le serpent dans la grille
void grid_actualize(){
	for (int i = 0; i < dim; ++i)
	{
		for (int j = 0; j < dim; ++j)
		{
			if (grid[i][j] != '+' && grid[i][j] != 'f')
			{
				grid[i][j] = ' ';
			}
		}
	}

	struct queue *q = queue;
	state_row = queue->elem->queue_row;
	state_col = queue->elem->queue_col;
	while (q != NULL)
	{
		grid[q->elem->queue_row][q->elem->queue_col] = '.';
		q = q->next;
	}

	actualize_terrain();
}

void grid_render(){

    for (int i=0; i<dim; i++) {
        for (int j=0; j< dim; j++){
            printf("%c ", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");

}


void new_fruit(){
	int i=rand()%(dim-2) + 1;
	int j=rand()%(dim-2) + 1;
	int k=0;
	while((grid[i][j]=='+')||(grid[i][j]=='.')||(k<100*dim*dim)){  //on tire des positions aléatoire dans la grille, si cette position correspond à un mur on retire jusqu'à avoir une position vide. Le compteur k permet de mettre une limite sur les tirages au cas où à la fun du jeu plus aucune position ne peut accueillir de fruit
		i=rand()%(dim-2) + 1;
		j=rand()%(dim-2) + 1;
		k+=1;
	}
	grid[i][j]='f';
	nfruit->f_row=i;
	nfruit->f_col=j;

}

void init_snake(){  //Création du serpent initial qui occupe 3 cases
	size_snake=3; //AU début le serpent est de longueur 3

	queue=malloc(sizeof(struct queue));  //Allocation de la liste représentant le serpent

	struct bout_queue *b0 = malloc(sizeof(struct bout_queue));
	
	b0->queue_col=start_col;
	b0->queue_row=start_row;
	
	queue->elem = b0;
	

	struct queue *next_1 = malloc(sizeof(struct queue));
	struct bout_queue *b1 = malloc(sizeof(struct bout_queue));
	b1->queue_col=start_col-1;
	b1->queue_row=start_row;
	next_1->elem=b1;

	struct queue *next_2 = malloc(sizeof(struct queue));
	struct bout_queue *b2 = malloc(sizeof(struct bout_queue));
	b2->queue_col=start_col-2;
	b2->queue_row=start_row;
	next_2->elem=b2;

	next_1->next = next_2;
	queue->next = next_1;

	struct queue *q = queue;
	while (q != NULL)
	{
		grid[q->elem->queue_row][q->elem->queue_col] = '.';
		q = q->next;
	}
}

void eat_a_fruit(){ //Cette fonction applique la transformation sur le serpent lorsqu'il mange un fruit

	struct queue *queue_queue=malloc(sizeof(struct queue));  //Création de la queue (temporaire) qu'on va rajouter à la suite de la nouvelle tete qui prend la place du fruit

	struct bout_queue *new_bout=malloc(sizeof(struct bout_queue)); //Création (permanente) des coordonnées de la nouvelle tete

	//La nouvelle tete du serpent prend la position du fruit en cours
	new_bout->queue_col=nfruit->f_col;  
	new_bout->queue_row=nfruit->f_row;


	queue_queue->elem=new_bout;
	queue_queue->next=queue;

	queue = queue_queue;

	size_snake+=1; //Lorsque l'on mange un fruit la taille du serpent augmente de 1

	// Actualisation du serpent dans la grille
	grid_actualize();

    // Génération d'un nouveau fruit
    new_fruit();

    // Actualisation du fruit dans la grille
    grid_actualize();

}

struct queue* delete_last(struct queue* I)
{
	struct queue* p=I;
	struct queue* l=NULL;
	struct queue* t=NULL;

	while(p->next->next!=NULL)
	{
		p=p->next;
	}

	l=p;
	t=p->next;
	l->next=NULL;
	free(t);
 
	return I;	
}

bool n_eat_a_fruit(action a){  //Cette fonction applique la transformation sur le seprent lorsqu'il avance sans manger un fruit, à priori on est obligé de prendre l'action a en argument
	struct queue *queue_queue=malloc(sizeof(struct queue));  //Création de la queue (temporaire) qu'on va rajouter à la suite de la nouvelle tete qui prend la place du fruit

	struct bout_queue *new_bout=malloc(sizeof(struct bout_queue)); //Création (permanente) des coordonnées de la nouvelle tete
	
	//On paramètre la nouvelle tete en fonction de l'action : la nouvelle tete correspond aux coordonnées de la case vers laquelle on avance
    switch (a){
        case up:
        	if (grid_terrain[queue->elem->queue_row-1][queue->elem->queue_col] == wall || grid_terrain[queue->elem->queue_row-1][queue->elem->queue_col] == snake)
        	{
        		return false;
        	}
            new_bout->queue_row = queue->elem->queue_row-1;
            new_bout->queue_col = queue->elem->queue_col;
        break;

        case down:
        	if (grid_terrain[queue->elem->queue_row+1][queue->elem->queue_col] == wall || grid_terrain[queue->elem->queue_row+1][queue->elem->queue_col] == snake)
        	{
        		return false;
        	}
            new_bout->queue_row = queue->elem->queue_row+1;
            new_bout->queue_col = queue->elem->queue_col;
        break;

        case right:
        	if (grid_terrain[queue->elem->queue_row][queue->elem->queue_col+1] == wall || grid_terrain[queue->elem->queue_row][queue->elem->queue_col+1] == snake)
        	{
        		return false;
        	}
            new_bout->queue_row = queue->elem->queue_row;
            new_bout->queue_col = queue->elem->queue_col+1;
        break;

        case left:
        	if (grid_terrain[queue->elem->queue_row][queue->elem->queue_col-1] == wall || grid_terrain[queue->elem->queue_row][queue->elem->queue_col-1] == snake)
        	{
        		return false;
        	}
            new_bout->queue_row = queue->elem->queue_row;
            new_bout->queue_col = queue->elem->queue_col-1;
        break;

        default:
        break;
    }

   	queue_queue->elem = new_bout;
   	queue_queue->next = queue;
   	queue = queue_queue;
    // //Jusqu'ici on a fait la meme chose que dans eat_a_fruit, il faut désormais supprimer le dernier élement de la liste sur seprent
   	// On delete le bout de la queue
   	struct queue *q = queue;

    queue=delete_last(queue);
    
    // Actualisation du serpent dans la grille
    grid_actualize();

    // Tout s'est bien passé 
    return true;    
}


// Avance le serpent
int step_foward(action a)
{
	switch (a){
        case up:
            if (grid[queue->elem->queue_row-1][queue->elem->queue_col] == 'f')
            {
            	eat_a_fruit(a);
            	return 0;
            }
            else {return n_eat_a_fruit(a);}
        break;

        case down:
            if (grid[queue->elem->queue_row+1][queue->elem->queue_col] == 'f')
            {
            	eat_a_fruit(a);
            	return true;
            }
            else {return n_eat_a_fruit(a);}
        break;

        case right:
            if (grid[queue->elem->queue_row][queue->elem->queue_col+1] == 'f')
            {
            	eat_a_fruit(a);
            	return true;
            }
            else {return n_eat_a_fruit(a);}
        break;

        case left:
            if (grid[queue->elem->queue_row][queue->elem->queue_col-1] == 'f')
            {
            	eat_a_fruit(a);
            	return true;
            }
            else {return n_eat_a_fruit(a);}
        break;

        default:
        	return false;
        break;
    }
}	


// Vérifie la taille du serpent : correspond au score
void taille_queue(struct queue *q)
{
	int n=1;
	struct queue *p = queue;
	while(p->next != NULL)
	{
		n++;
		p = p->next;
	}
	printf("%d\n", n);
	return;
}


// 0 if no fruit, 1 if UP, 2 if DOWN, 3 if LEFT, 4 if RIGHT
int is_a_fruit_ahead(){

	// Pour l'instant regarde sur le tableau grid_terrain

	// UP
	for (int i = 0; i < state_row; ++i)
    {
     	if (grid_terrain[i][state_col] == fruit)
          	{
          		printf("The fruit is UP\n");
         		return 1;
          	}
    }

    // DOWN
    for (int i = state_row+1; i < dim; ++i)
    {
       	if (grid_terrain[i][state_col] == fruit)
       	{
       		printf("The fruit is DOWN\n");
      		return 2;
      	}
    }

    // LEFT
    for (int i = state_col-1; i > 0; i--)
    {
           	if (grid_terrain[state_row][i] == fruit)
           	{
           		printf("The fruit is LEFT\n");
           		return 3;
           	}
    }

    // RIGHT
    for (int i = state_col+1; i < dim; i++)
    {
           	if (grid_terrain[state_row][i] == fruit)
           	{
           		printf("The fruit is RIGHT\n");
           		return 4;
           	}
    }

    printf("There is no fruit ahead\n");
    return 0;
}

int is_a_obstacle_up(){

	// Pour l'instant regarde sur le tableau grid_terrain

	// UP
	for (int i = state_row-1; i >=0; --i)
    {
     	if ((grid_terrain[i][state_col] == wall)||(grid_terrain[i][state_col] == snake))
          	{
         		return state_row-i-1;
          	}
    }

   
    return 0;
}

int is_a_obstacle_down(){
	for (int i = state_row+1; i < dim; ++i)
    {
       	if ((grid_terrain[i][state_col] == wall)||(grid_terrain[i][state_col] == snake))
       	{
       		return(i-state_row-1);
      	}
    }
    return 0;
}

int is_a_obstacle_right(){
	for (int i = state_col+1; i < dim; i++)
    {
           	if ((grid_terrain[state_row][i] == wall)||(grid_terrain[state_row][i] == snake))
           	{
           		return(i-state_col-1);
           	}
    }
return 0;
}

int is_a_obstacle_left(){

	// Pour l'instant regarde sur le tableau grid_terrain

	// UP
	for (int i = state_col-1; i >=0; --i)
    {
     	if ((grid_terrain[state_row][i] == wall)||(grid_terrain[state_row][i] == snake))
          	{
         		return state_col-i-1;
          	}
    }

   
    return 0;
}

envOutput game_step(action a){
   	int end=1;
    envOutput stepOut;

    //Pour chaque situation on applique des récompenses en fonction de l'environnement autour (est-ce qu'on a mangé un fruit ? est ce qu'il ya un obstacle au loin ? Est ce qu'il y a un fruit au loin ?)

 	//On utilise de variable locale dans 
}
