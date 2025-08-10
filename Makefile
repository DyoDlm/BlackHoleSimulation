NAME = blackHoleSimulation

SRC = main.cpp 

CC = g++

FLAGS = -lglfw -lGLEW -lGL

all:
	$(CC) $(SRC) $(FLAGS) -o $(NAME)

clean: $(NAME)
	rm $(NAME)


re:
	clean
	all







