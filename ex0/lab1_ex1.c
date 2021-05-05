#include <stdio.h>

int main() {
	int numero;
	int resultado;
	
	printf("Insira um numero\n");
	scanf("%d", &numero);

	resultado = numero * 3;
    
	printf("Numero = %d <> Numero x 3 = %d", numero, resultado);

	return 0;
}