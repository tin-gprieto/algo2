V = valgrind
CFLAGS = -std=c99 -g -O0
GFLAGS = -tui
WFLAGS = -Wall -Wconversion -Werror
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes

TOOLS = toolbox/code/tools/tools.c toolbox/code/TDAs/lista/lista.c
HASH = hash.c

test.exe: $(HASH) $(TOOLS) hash_pruebas.c
	$(CC) hash_pruebas.c $(HASH) $(TOOLS) $(CFLAGS) $(WFLAGS) -o test.exe

test: test.exe
	clear
	$(V) $(VFLAGS) ./test.exe

mini_test.exe: $(HASH) $(TOOLS) hash_minipruebas.c
	$(CC) hash_minipruebas.c $(HASH) $(TOOLS) $(CFLAGS) $(WFLAGS) -o mini_test.exe

mini_test: mini_test.exe
	clear
	$(V) $(VFLAGS) ./mini_test.exe