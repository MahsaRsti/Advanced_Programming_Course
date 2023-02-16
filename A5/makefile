CC = g++
FLAGS = -std=c++11 -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer
COMPILE_FLAGS = $(FLAGS) -c 

starwars.out: main.o game.o ship.o gunshot.o enemy.o hostage.o map_funcs.o
	$(CC) main.o game.o ship.o gunshot.o enemy.o hostage.o map_funcs.o rsdl.cpp $(FLAGS) -o starwars.out

main.o: main.cpp game.hpp ship.hpp rsdl.hpp gunshot.hpp enemy.hpp hostage.hpp map_funcs.hpp
	$(CC) $(COMPILE_FLAGS) main.cpp

ship.o: ship.cpp game.hpp ship.hpp rsdl.hpp
	$(CC) $(COMPILE_FLAGS) ship.cpp

game.o: game.cpp game.hpp ship.hpp rsdl.hpp gunshot.hpp enemy.hpp hostage.hpp
	$(CC) $(COMPILE_FLAGS) game.cpp

gunshot.o: gunshot.cpp gunshot.hpp rsdl.hpp
	$(CC) $(COMPILE_FLAGS) gunshot.cpp

enemy.o: enemy.cpp enemy.hpp rsdl.hpp
	$(CC) $(COMPILE_FLAGS) enemy.cpp

hostage.o: hostage.cpp hostage.hpp rsdl.hpp
	$(CC) $(COMPILE_FLAGS) hostage.cpp

map_funcs.o: map_funcs.cpp map_funcs.hpp game.hpp ship.hpp rsdl.hpp gunshot.hpp enemy.hpp hostage.hpp
	$(CC) $(COMPILE_FLAGS) map_funcs.cpp

.PHONY: clean

clean:
	rm *.o starwars.out