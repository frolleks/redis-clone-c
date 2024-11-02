CC=gcc
OPT=-Wall -Wextra -Werror -pedantic

sources := $(wildcard src/*.c)

all: main

main: $(sources)
	mkdir -p build/
	$(CC) $^ $(OPT) -o build/main

clean:
	rm -rf build/