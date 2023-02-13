CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -g
SOURCES = main.c tasks.c tree.c Node.c Doubly_linked_list.c
EXE = minimax

build:
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXE)
clean:
	rm -f $(EXE)