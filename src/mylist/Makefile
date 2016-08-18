NAME = libmylist.a
LIB = ../../lib/$(NAME)
SRC = newnode.c addnode.c addelem.c append.c addnodeat.c removenode.c removelast.c removenodeat.c countsnodes.c emptylist.c nodeat.c elemat.c traverseint.c traversechar.c traversestring.c debugint.c debugchar.c debugstring.c printint.c printchar.c printstring.c
OBJ = $(SRC:.c=.o)
INCLUDES = ../../include
RM = rm -f
CFLAGS = -g -Wall -Werror --pedantic -I$(INCLUDES)
LDFLAGS = -c

all: $(OBJ)
	ar -r $(NAME) $(OBJ)
	ranlib $(NAME)
	mv $(NAME) ../../lib

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) ../../lib/$(NAME)
	
re: fclean all
