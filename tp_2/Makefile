CC= gcc
V= valgrind
GDB= gdb
CFLAGS= -std=c99 -g -O0
GFLAGS= -tui
WFLAGS= -Wall -Wconversion -Werror
VFLAGS= --leak-check=full --track-origins=yes --show-reachable=yes

CFILE=code/main.c
EXE= juego.exe

TEST_FILE=test/pruebas.c
HEAP_FILE=test/pruebas_heap.c

TEST_EXE= test/prueba.exe
HEAP_EXE= test/heap.exe

LIB_FILE= toolbox/tools.c code/batallas.c code/aventura.c
TDA_FILE= toolbox/tools.c toolbox/tdas/*.c


$(EXE): $(CFILE) $(LIB_FILE) $(TDA_FILE)
	clear
	$(CC) $(CFILE) $(LIB_FILE) $(TDA_FILE) $(CFLAGS) $(WFLAGS) -o $(EXE)
play: $(EXE)
	clear
	./$(EXE)

$(TEST_EXE): $(TEST_FILE) $(LIB_FILE) 
	clear
	$(CC) $(TEST_FILE) $(LIB_FILE) $(CFLAGS) $(WFLAGS) -o $(TEST_EXE)
test: $(TEST_EXE)
	clear
	$(V) $(VFLAGS) ./$(TEST_EXE)

$(HEAP_EXE): $(HEAP_FILE) $(TDA_FILE)
	clear
	$(CC) $(HEAP_FILE) $(TDA_FILE) $(CFLAGS) $(WFLAGS) -o $(HEAP_EXE)
heap: $(HEAP_EXE)
	clear
	$(V) $(VFLAGS) ./$(HEAP_EXE)

