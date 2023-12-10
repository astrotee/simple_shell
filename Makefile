CFLAGS=-Wall -Werror -Wextra -pedantic -g -std=gnu89
all: hsh

hsh: *.c
	gcc  $(CFLAGS) $^ -o hsh

