
CC = g++
CCFLAGS = -std=c++17 -Wall -Wextra -pedantic -Weffc++ -Wold-style-cast -Woverloaded-virtual -fmax-errors=3 -g
LDFLAGS = -lsfml-window -lsfml-graphics -lsfml-system -lsfml-audio
OBJS = $(wildcard src/*.cc)
OBJS_TEST = $(filter-out src/main.cc, $(wildcard src/*.cc test/meleeTest.cc test/test_melee.o) )

game: $(OBJS)
	$(CC) $(CCFLAGS) -o $@ $^ $(LDFLAGS)

testFile: $(OBJS_TEST)
	$(CC) $(CCFLAGS) -o $@ $^ $(LDFLAGS)