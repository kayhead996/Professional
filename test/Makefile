NAME = pipes
SRC = pipes.c
OBJ = $(SRC:.c=.o)

CFLAGS = -g -Wall -Werror --pedantic -I../include
CC = gcc
RM = rm -f

all: $(OBJ)
	$(CC) -L../lib $(OBJ) -o $(NAME) 

clean:
	$(RM) $(OBJ)
	$(RM) $(NAME)

re: clean all
