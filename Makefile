CFLAGS = -std=gnu11 -Wall -Werror -Wextra -Wno-unused-parameter

.PHONY: all clean install

all: riverbsp

clean:
	$(RM) bin/riverbsp

install:
	install bin/riverbsp /usr/local/bin

riverbsp: riverbsp.c bstree.h bstree.c
	mkdir -p bin
	$(CC) $(CFLAGS) -o bin/$@ $^ 