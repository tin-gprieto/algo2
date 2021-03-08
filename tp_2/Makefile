V = valgrind
CFLAGS= -std=c99 -g -O0
WFLAGS= -Wall -Wconversion -Werror
VFLAGS= --leak-check=full --track-origins=yes --show-reachable=yes

LIB_FILE= code/*.c
TOOL_FILE= toolbox/tools.c 
TDA_FILE= toolbox/tdas/*.c

juego: main.c $(CFILE) $(TOOL_FILE) $(TDA_FILE)
	clear
	$(CC) main.c $(LIB_FILE) $(TOOL_FILE) $(TDA_FILE) $(CFLAGS) $(WFLAGS) -o juego
	
play: juego
	./juego

val: juego
	$(V)./juego $(VFLAGS)

test/test.exe: test/test_juego.c $(TOOL_FILE) $(TDA_FILE) $(LIB_FILE) 
	clear
	$(CC) test/test_juego.c  $(LIB_FILE) $(TOOL_FILE) $(TDA_FILE) $(CFLAGS) $(WFLAGS) -o test/test.exe

test: test/test.exe
	clear
	$(V) $(VFLAGS) ./test/test.exe

test/interfaz.exe: test/test_interfaz.c $(TOOL_FILE) $(TDA_FILE) $(LIB_FILE) 
	clear
	$(CC) test/test_interfaz.c $(LIB_FILE) $(TOOL_FILE) $(TDA_FILE) $(CFLAGS) $(WFLAGS) -o  test/interfaz.exe

interfaz:  test/interfaz.exe
	clear
	./ test/interfaz.exe

test/heap.exe: test/test_heap.c $(TDA_FILE)
	clear
	$(CC) test/test_heap.c $(TDA_FILE) $(CFLAGS) $(WFLAGS) -o test/heap.exe

heap: test/heap.exe
	clear
	$(V) $(VFLAGS) ./test/heap.exe

