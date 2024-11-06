CC=gcc
OPT=-Wall -Wextra -pedantic $(shell pkg-config --cflags --libs glib-2.0)

sources := $(wildcard src/*.c)

all: main

main: $(sources)
	mkdir -p build/
	$(CC) $^ $(OPT) -o build/main

clean:
	rm -rf build/