#include <stdio.h>
#include "TP1_Validacion.h"

#define MAX 100

// Implementación de recursividad - TP Nro. 1 - Punto 3

// Función recursiva multiple: calcula el k-ésimo número de la serie de Fibonacci.
long SerieDeFibonacci (int pos) {
    if (pos < 2) return pos;
    else return (SerieDeFibonacci(pos - 1) + SerieDeFibonacci(pos - 2)); 
}

void main () {
    char filtro[MAX];
    int numero, termino;
    memset(filtro, MAX, '\0');
    printf("\n // Implementación de recursividad - TP Nro. 1 - Punto 3");
    printf("\n << Ingrese el nro. de termino (menor a 40) de la serie de Fibonacci que desea calcular: ");
    fgets(filtro, MAX, stdin);
    termino = EntradaEntera(filtro, 0, 0, 40);                                      // Verifica que la entrada se encuentre en el intervalo [1; 40]
    numero = SerieDeFibonacci(termino);
    printf("\n >> Valor del termino %d: %d", termino, numero);
}
