NAME = browser
SRC = browser.c
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
