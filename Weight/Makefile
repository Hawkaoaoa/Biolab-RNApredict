CC = gcc

PATH_LIB = ./lib
PATH_SRC = ./src
PATH_BIN = ./bin
PATH_HEAD = ./include

NAME_LIB = Bio_RNApredict_dynamic

all: $(PATH_SRC)/*.c
	$(CC) -c ./src/*.c -I $(PATH_HEAD) 
	ar rcs $(PATH_LIB)/lib$(NAME_LIB).a *.o

.PHONY: install
install:
	$(CC) -o $(PATH_BIN)/RNA $(PATH_BIN)/main.c -L $(PATH_LIB) -l$(NAME_LIB) -I $(PATH_HEAD) -g

.PHONY: clean
clean:
	rm -rf *.o
