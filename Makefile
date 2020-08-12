##########################################################################
# First, search for all source files
# Second, replace all sources (src/*.c by *.o, i.e. main.o is a rule for all)
# %.o defines the rule for compiling with all source files as dependency
# all rule with clean and all object files as dependencies
# e.g. the object file obj/main.o is linked to the executable bin/main
##########################################################################


CC=gcc
CFLAGS=-O3 -pipe
LDFLAGS=-lglfw -lGL -lpthread -lm 

SOURCES := $(shell find src -name '*.c')
OBJECTS := $(patsubst src/%.c,%.o,$(SOURCES))

%.o : src/%.c
	$(CC) $(CFLAGS) -c $< -o obj/$@

all: clean $(OBJECTS)
	$(CC) -o bin/main $(addprefix obj/, $(OBJECTS)) $(LDFLAGS)

avx2_flags:
	$(eval CFLAGS += -DUSE_AVX2 -mavx2)

avx2: avx2_flags all

clean:
	@mkdir -p obj bin
	@rm -rf obj/* bin/*

