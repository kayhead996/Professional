NAME = libsockettalk.a
LIB = ../../lib/$(NAME)
SRC = bzero.c bcopy.c error.c newclient.c sendmessage.c special.c changeusername.c
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
