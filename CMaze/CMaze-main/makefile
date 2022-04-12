CC=gcc
CFLAGS=-Wall -Werror -Wfatal-errors
SRC=./
EXEC=main

all: $(EXEC)

main: $(SRC)dfs.c $(SRC)functions.o $(SRC)mazeEnv.o $(SRC)Qlearning.o
	$(CC) -o $(SRC)$@ $^ $(CFLAGS)

$(SRC)%.o: $(SRC)%.c
	$(CC) -o $@ -c $< $(CFLAGS)

# 	Il faut aussi penser à ajouter les fichiers .h, dans le cas où ils sont modifiés.

# On ajoute la commande clean pour supprimer tous les fichiers executables pour réinitialiser les données.

clean:
	rm -f main *.o

# Le -f permet d'ignorer les fichiers non existants.