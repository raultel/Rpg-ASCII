CC = g++
MAIN = main.cpp
OBJ = Point.cpp Monster.cpp Map.cpp Player.cpp Item.cpp Inventory.cpp
OBJ_NAME = exec
LIBS = -lncurses

all:
	$(CC) $(MAIN) $(OBJ) -o $(OBJ_NAME) $(LIBS)
run:
	./$(OBJ_NAME)