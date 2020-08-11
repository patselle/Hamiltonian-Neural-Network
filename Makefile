CC=gcc
CFLAGS=-O3 -pipe

SOURCES := $(shell find src -name '*.c')
OBJECTS := $(patsubst src/%.c,%.o,$(SOURCES))

%.o : src/%.c
	$(CC) $(CFLAGS) -c $< -o obj/$@

all: clean $(OBJECTS)
	$(CC) -o bin/main $(addprefix obj/, $(OBJECTS))

clean:
	@mkdir -p obj bin
	@rm -rf obj/* bin/*

