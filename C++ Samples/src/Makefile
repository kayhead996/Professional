NAME = FSSimulator
SRC = lf_node.cpp ld_node.cpp tr_node.cpp init.cpp run.cpp main.cpp
OBJ = $(SRC:.cpp=.o)
CXX = g++ $(CXXFLAGS)
INCLUDE = ../include
BIN = ../bin
CXXFLAGS = -g -std=c++11 -Wall -I$(INCLUDE)

all: $(OBJ)
	$(CXX) $(OBJ) -o $(NAME) -lpthread 
	mv $(NAME) $(BIN)/$(NAME)

clean:
	-$(RM) *~
	-$(RM) \#*
	-$(RM) *.o
	-$(RM) *.core

fclean:	clean
	-$(RM) $(NAME)

re: fclean all

