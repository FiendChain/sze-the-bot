CC=g++
CFLAGS=-DSFML_STATIC -std=c++17
LLIB=-I .\SFML\include -L .\SFML\lib
LFLAGS=-lm -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -lfreetype -ljpeg 
CFLAGS_LINUX=-std=c++17
LFLAGS_LINUX=-lm -lsfml-graphics -lsfml-window -lsfml-system

TARGET := main
SOURCES := $(wildcard *.cpp)
OBJECTS := $(patsubst %.cpp, %.o, $(SOURCES))

$(TARGET):
	$(CC) $(SOURCES) -o $(TARGET) $(CFLAGS) $(LLIB) $(LFLAGS)

linux: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(CFLAGS_LINUX) $(LFLAGS_LINUX)

%.o: %.cpp
	$(CC) $^ -c $(CFLAGS_LINUX) $(LFLAGS_LINUX)
	
clean:
	rm -f main *.o core

check: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)
