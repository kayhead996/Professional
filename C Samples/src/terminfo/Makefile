NAME = my_select
SRC = my_select.c saveoutput.c setup.c displayfiles.c parsekey.c maxstrlen.c movecursor.c highlightfile.c
OBJ = $(SRC:.c=.o)
INCLUDES = ../../include
RM = rm -f
CFLAGS = -g -Wall -Werror --pedantic -I$(INCLUDES)
LDFLAGS = -c

all: $(OBJ)
	$(CC) -L../../lib $(OBJ) -o $(NAME) -lncurses -lmy

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) ../../lib/$(NAME)
	
re: fclean all
