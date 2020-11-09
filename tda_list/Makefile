CC= gcc
V= valgrind
GDB= gdb
R= rm
CFLAGS= -std=c99 -g -O0
GFLAGS= -tui
WFLAGS= -Wall -Wconversion -Werror -Wtype-limits -pedantic
VFLAGS= --leak-check=full --track-origins=yes --show-reachable=yes

build: lista_pruebas.c pa2mm.h lista.c
	$(CC) lista_pruebas.c pa2mm.h lista.c $(CFLAGS) $(WFLAGS) -o lista_se
		
mini_build: lista_minipruebas.c lista.c
	$(CC) lista_minipruebas.c lista.c $(CFLAGS) $(WFLAGS) -o lista_se

test: build
	clear
	$(V) $(VFLAGS) ./lista_se

mini_test: mini_build
	clear
	$(V) $(VFLAGS) ./lista_se

gdb: build
	$(GDB) lista_se $(GFLAGS)

mini_gdb: mini_build
	$(GDB) lista_se $(GFLAGS)