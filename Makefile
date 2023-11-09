
CC = g++
CCFLAGS = -std=c++17 -Wall -Wextra -pedantic -Weffc++ -Wold-style-cast -Woverloaded-virtual -fmax-errors=3 -g
LDFLAGS = -lsfml-window -lsfml-graphics -lsfml-system
OBJS = $(wildcard *.cc)

game: $(OBJS)
	$(CC) $(CCFLAGS) -o $@ $^ $(LDFLAGS)