CC= gcc
V= valgrind
GDB= gdb
R= rm
CFLAGS= -std=c99 -g -O0
GFLAGS= -tui
ARCHIVOS= simple.txt acuario.txt
ERROR= error.txt acuario.txt
SIMPLE= arrecife.txt acuario.txt
WFLAGS= -Wall -Wconversion -Werror
VFLAGS= --leak-check=full --track-origins=yes --show-reachable=yes

evento_pesca: main.c evento_pesca.c
		$(CC) main.c evento_pesca.c $(CFLAGS) $(WFLAGS) -o evento_pesca
exe: evento_pesca
		./evento_pesca $(ARCHIVOS)
help: evento_pesca
		./evento_pesca --help
val: evento_pesca
		$(V) $(VFLAGS) ./evento_pesca $(ARCHIVOS)
gdb: evento_pesca
		$(GDB) evento_pesca  $(GFLAGS)
rm:
	$(R) evento_pesca 
clean: rm
	$(R) acuario.txt
error: evento_pesca
	./evento_pesca $(ERROR)
simple: evento_pesca
	./evento_pesca $(SIMPLE)
