CC=g++
CFLAGS=-DSFML_STATIC -std=c++17
LLIB=-I .\SFML\include -L .\SFML\lib
LFLAGS=-lm -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -lfreetype -ljpeg 

FILES=main.cpp AI.cpp Simulation.cpp Entity.cpp Bot.cpp Angles.cpp Distance.cpp

main:
	$(CC) $(FILES) -o main $(CFLAGS) $(LLIB) $(LFLAGS)

clean:
	rm -f main *.o core

check: main
	valgrind --leak-check=full ./main
