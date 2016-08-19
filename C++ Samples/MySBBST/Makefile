NAME = mysbbst
TARBALL = keyur-$(NAME).tar.gz
SRC = comparators.cpp add.cpp order.cpp rotations.cpp main.cpp print.cpp height.cpp remove.cpp removeMin.cpp search.cpp
OBJ = $(SRC:.cpp=.o)
RM = rm -f
CPPFLAGS=-g 

all: $(OBJ)
	g++ -g $(OBJ) -o $(NAME)

clean:
	-$(RM) *~
	-$(RM) \#*
	-$(RM) *.o
	-$(RM) *.core

fclean:	clean
	-$(RM) $(NAME)

re: fclean all

submit: fclean
	tar cvzf $(TARBALL) *


