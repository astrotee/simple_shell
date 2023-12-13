CFLAGS=-Wall -Werror -Wextra -pedantic -g -std=gnu89
all: shell

shell: hsh

hsh: *.c
	gcc  $(CFLAGS) $^ -o hsh


.PHONY: all shell
