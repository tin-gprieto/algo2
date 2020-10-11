CC= gcc
V= valgrind
CFLAGS= -std=c99 -g -O0
WFLAGS= -Wall -Wconversion -Werror
VFLAGS= --leak-check=full --track-origins=yes --show-reachable=yes
CLIBRARY= evento_pesca.c

compile: pesca.c
		$(CC) pesca.c $(CLIBRARY) $(CFLAGS) $(WFLAGS) -o evento_pesca
valgrind: compile
				$(V) $(VFLAGS) ./evento_pesca
