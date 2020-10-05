#include <stdio.h>
#include <stdlib.h>

int main(){
	int elemento;
	int* estatico = &elemento;
	int* dinamico = malloc(sizeof(int));

	printf("Memoria estatatica: %x \nMemoria dinámica: %x \n", *estatico, *dinamico);

	free(dinamico);
}
