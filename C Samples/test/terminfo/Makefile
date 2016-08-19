NAME = my_select 
SRC = my_select.c
OBJ = $(SRC:.c=.o)

CFLAGS = -g -Wall -Werror --pedantic -I../../include
CC = gcc
RM = rm -f

all: $(OBJ)
	$(CC) -L../../lib $(OBJ) -o $(NAME) -lncurses -lterminfo -lmy

clean:
	$(RM) $(OBJ)
	$(RM) $(NAME)

re: clean all
