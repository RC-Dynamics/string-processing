# Name of the project
PROJ_NAME=pmt

# .cpp files
C_SOURCE=$(wildcard ./src/*.cpp)

# .h files
H_SOURCE=$(wildcard ./src/*.h)

# Object files
OBJ=$(subst .cpp,.o,$(subst src,generated_files,$(C_SOURCE)))

# Compiler and linker
CC=g++

# Flags for compiler
CC_FLAGS=-std=c++11 \
		 -c         \
         -W         \
         -Wall      \
         -ansi      \
         -pedantic

RM = rm -rf

all: objFolder $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	$(CC) $^ -o bin/$@

./generated_files/%.o: ./src/%.cpp ./src/%.h
	$(CC) $< $(CC_FLAGS) -o $@

./generated_files/main.o: ./src/main.cpp $(H_SOURCE)
	$(CC) $< $(CC_FLAGS) -o $@

objFolder:
	mkdir -p bin
	mkdir -p generated_files

clean:
	$(RM) ./generated_files/*.o $(PROJ_NAME) *~
	rmdir generated_files
