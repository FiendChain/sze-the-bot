CC := g++
OBJ := obj

ifeq ($(OS),Windows_NT)
	CFLAGS	:= -DSFML_STATIC -static -std=c++17
	LLIB   	:= -I .\SFML\include -L .\SFML\lib
	LFLAGS 	:= -lm -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -lfreetype -ljpeg 
else
	CFLAGS 	:= -std=c++17
	LLIB   	:= 
	LFLAGS 	:= -lm -lsfml-graphics -lsfml-window -lsfml-system
endif
	
TARGET := main
SOURCES := $(wildcard *.cpp)
OBJECTS := $(patsubst %.cpp, $(OBJ)/%.o, $(SOURCES))

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(CFLAGS) $(LLIB) $(LFLAGS)

$(OBJ)/%.o: %.cpp
	$(CC) -c $< -o $@ $(LLIB) $(CFLAGS) $(LFLAGS)
	
clean:
	rm -f $(TARGET) $(OBJ)/*.o core

check: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)
