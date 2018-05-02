CC := g++
OBJ := objects
SRC := .
LIB := sources

ifeq ($(OS),Windows_NT)
	CFLAGS	:= -DSFML_STATIC -static -std=c++17
	LLIB   	:= -I .\SFML\include -L .\SFML\lib
	LFLAGS  := -lm -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -lfreetype -ljpeg 
else
	CFLAGS 	:= -std=c++17
	LLIB   	:= 
	LFLAGS 	:= -lm -lsfml-graphics -lsfml-window -lsfml-system
endif

TARGET 	:= main
# main code
SOURCES := $(wildcard $(SRC)/*.cpp)
OBJECTS := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SOURCES))
# custom library
LIB_SOURCES := $(wildcard $(LIB)/*.cpp)
LIB_OBJECTS := $(patsubst $(LIB)/%.cpp, $(OBJ)/%.o, $(LIB_SOURCES))

$(TARGET): sources library
	$(CC) $(OBJECTS) $(LIB_OBJECTS) -o $(TARGET) $(CFLAGS) $(LLIB) $(LFLAGS)

# make source
sources: $(OBJECTS)
$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) -c $< -o $@ $(LLIB) $(CFLAGS) $(LFLAGS)

# make library
library: $(LIB_OBJECTS)
$(OBJ)/%.o: $(LIB)/%.cpp
	$(CC) -c $< -o $@ $(LLIB) $(CFLAGS) $(LFLAGS)
	
clean:
	rm -f $(TARGET) $(OBJ)/*.o core

check: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)
