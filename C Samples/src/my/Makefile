NAME = libmy.a
LIB = ../../lib/$(NAME)
SRC = mychar.c mystr.c myint.c mynumbase.c mynumbaserec.c myalpha.c mydigits.c mystrlen.c myrevstr.c myfind.c myrfind.c mystrindex.c mystrrindex.c mystrcat.c mystrcmp.c mystrncmp.c mystrconcat.c mystrnconcat.c mystrcpy.c mystrncpy.c mystrdup.c myvect2str.c mystr2vect.c myatoi.c mystrreplace.c mymaxstrlen.c
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
