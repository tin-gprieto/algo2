CC= gcc
V= valgrind
GDB= gdb
R= rm
CFILE=abb_pruebas.c test.c
HFILE=abb.c
FILEXTRA=abb_minipruebas.c
EXE=abb
EXE2= abb_mini
CFLAGS= -std=c99 -g -O0
GFLAGS= -tui
WFLAGS= -Wall -Wconversion -Werror -Wtype-limits -pedantic
VFLAGS= --leak-check=full --track-origins=yes --show-reachable=yes

$(EXE): $(CFILE) $(HFILE)
	clear
	$(CC) $(CFILE) $(HFILE) $(CFLAGS) $(WFLAGS) -o $(EXE)
		
test: $(EXE)
	clear
	$(V) $(VFLAGS) ./$(EXE)

debug: $(EXE)
	$(GDB) $(EXE) $(GFLAGS)

mini_build: $(FILEXTRA) $(HFILE)
	$(CC) $(FILEXTRA) $(HFILE) $(CFLAGS) $(WFLAGS) -o $(EXE2)

mini_test: mini_build
	clear
	$(V) $(VFLAGS) ./$(EXE2)

mini_debug: mini_build
	$(GDB) $(EXE2) $(GFLAGS)