
CC = g++
CCFLAGS = -std=c++17 -Wall -Wextra -pedantic -Weffc++ -Wold-style-cast -Woverloaded-virtual -fmax-errors=3 -g 

MAKEFLAGS := --jobs=$(shell nproc)

LDFLAGS = -lsfml-window -lsfml-graphics -lsfml-system -lsfml-audio
OBJS = $(wildcard src/*.cc)
OBJS_TEST = $(filter-out src/main.cc, $(wildcard src/*.cc test/meleeTest.cc test/test_melee.o) )

game: $(OBJS)
	$(CC) $(CCFLAGS) -o $@ $^ $(LDFLAGS)
	@$(ECHO)

testFile: $(OBJS_TEST)
	$(CC) $(CCFLAGS) -o $@ $^ $(LDFLAGS)


ifneq ($(words $(MAKECMDGOALS)),1)
.DEFAULT_GOAL = all
%:
	@$(MAKE) $@ --no-print-directory -rRf $(firstword $(MAKEFILE_LIST))
else
ifndef ECHO
T := $(shell $(MAKE) $(MAKECMDGOALS) --no-print-directory \
      -nrRf $(firstword $(MAKEFILE_LIST)) \
      ECHO="COUNTTHIS" | grep -cc "COUNTTHIS")

N := x
C = $(words $N)$(eval N := x $N)
ECHO = echo "`expr " [\`expr $C '*' 100 / $T\`" : '.*\(....\)$$'`%]"
endif

.PHONY: all clean

all: game
	@$(ECHO) All done

src/%.cc:
	@$(ECHO) Compiling $@
	@sleep 0.1
	@touch $@

endif
