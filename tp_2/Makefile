CC= gcc
V= valgrind
GDB= gdb
CFLAGS= -std=c99 -g -O0
GFLAGS= -tui
WFLAGS= -Wall -Wconversion -Werror
VFLAGS= --leak-check=full --track-origins=yes --show-reachable=yes

MAIN_FILE=main.c
EXE= juego.exe

TEST_FILE=test/test_juego.c 
TEST_EXE= test/prueba.exe

HEAP_FILE=test/test_heap.c
HEAP_EXE= test/heap.exe

INTERFAZ_FILE=test/test_interfaz.c 
INTERFAZ_EXE= test/interfaz.exe

LIB_FILE=code/*.c
TOOL_FILE= toolbox/tools.c 
TDA_FILE=toolbox/tdas/*.c


$(EXE): $(MAIN_FILE) $(CFILE) $(TOOL_FILE) $(TDA_FILE)
	clear
	$(CC) $(MAIN_FILE) $(LIB_FILE) $(TOOL_FILE) $(TDA_FILE) $(CFLAGS) $(WFLAGS) -o $(EXE)
play: $(EXE)
	clear
	./$(EXE)

$(TEST_EXE): $(TEST_FILE) $(TOOL_FILE) $(TDA_FILE) $(LIB_FILE) 
	clear
	$(CC) $(TEST_FILE) $(LIB_FILE) $(TOOL_FILE) $(TDA_FILE) $(CFLAGS) $(WFLAGS) -o $(TEST_EXE)

test: $(TEST_EXE)
	clear
	$(V) $(VFLAGS) ./$(TEST_EXE)

$(INTERFAZ_EXE): $(INTERFAZ_FILE) $(TOOL_FILE) $(TDA_FILE) $(LIB_FILE) 
	clear
	$(CC) $(INTERFAZ_FILE) $(LIB_FILE) $(TOOL_FILE) $(TDA_FILE) $(CFLAGS) $(WFLAGS) -o $(INTERFAZ_EXE)

interfaz: $(INTERFAZ_EXE)
	clear
	./$(INTERFAZ_EXE)

$(HEAP_EXE): $(HEAP_TEST) $(TDA_FILE)
	clear
	$(CC) $(HEAP_TEST) $(TDA_FILE) $(CFLAGS) $(WFLAGS) -o $(HEAP_EXE)

heap: $(HEAP_EXE)
	clear
	$(V) $(VFLAGS) ./$(HEAP_EXE)

