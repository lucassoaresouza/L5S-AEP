BINFOLDER := bin/
INCFOLDER := inc/
SRCFOLDER := src/
OBJFOLDER := obj/
INCLUDE_DIRS := /usr/include/SDL2
LIBRARIES := SDL2

CC := g++

CPPFLAGS := -w -Wall -ansi -pedantic -std=c++11
LINKER_FLAGS := -lSDL2

SRCFILES := $(wildcard src/*.cpp)

all: $(SRCFILES:src/%.cpp=obj/%.o)
	$(CC) obj/*.o $(CPPFLAGS) $(LINKER_FLAGS) -o bin/aep

obj/%.o: src/%.cpp
	$(CC) -c $< $(CPPFLAGS) $(LINKER_FLAGS) -o $@ -I./inc

run: bin/aep
	bin/aep

.PHONY: clean
clean:
	rm -rf obj/*
	rm -rf bin/*
