CC = gcc

PATH_LIB = ./lib
PATH_SRC1 = ./src/Dynamic1
PATH_SRC2 = ./src/Dynamic2
PATH_SRC3 = ./src/Weight

PATH_BIN = ./bin
PATH_HEAD = ./include

NAME_LIB = Bio_RNAprediction

all: 
	$(CC) -c $(PATH_SRC1)/*.c -I $(PATH_HEAD)
	$(CC) -c $(PATH_SRC2)/*.c -I $(PATH_HEAD)
	$(CC) -c $(PATH_SRC3)/*.c -I $(PATH_HEAD) 
	ar rcs $(PATH_LIB)/lib$(NAME_LIB).a *.o

.PHONY: install
install:
	$(CC) -o $(PATH_BIN)/RNA $(PATH_BIN)/main.c -L $(PATH_LIB) -l$(NAME_LIB) -I $(PATH_HEAD) -g

.PHONY: clean
clean:
	rm -rf *.o
