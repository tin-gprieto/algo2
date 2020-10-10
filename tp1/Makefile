CC= gcc
V= valgrind
CFLAGS= -std=c99 -Wall -Wconversion -Werror -g
VFLAGS= --leak-check=full --track-origins=yes --show-reachable=yes
CLIBRARY= evento_pesca.c

build: pesca.c
		$(CC) pesca.c $(CLIBRARY) $(CFLAGS) -o evento_pesca
valgrind: evento_pesca
				$(V) $(VFLAGS) ./evento_pesca
