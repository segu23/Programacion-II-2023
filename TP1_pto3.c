#include <stdio.h>
#include "TP1_Validacion.h"

#define MAX 100

// Implementación de recursividad - TP Nro. 1 - Punto 3

// Función recursiva multiple: calcula el k-ésimo número de la serie de Fibonacci.
int SerieDeFibonacci (int pos) {
    if (pos < 2) return pos;
    else return (SerieDeFibonacci(pos - 1) + SerieDeFibonacci(pos - 2)); 
}

void main () {
    char filtro[MAX];
    int numero;
    memset(filtro, MAX, '\0');
    printf("\n // Implementación de recursividad - TP Nro. 1 - Punto 3");
    scanf("\n << Ingrese el nro. de termino (menor a 40) de la serie de Fibonacci que desea calcular: ");
    fgets(filtro, MAX, stdin);
    SerieDeFibonacci(EntradaEntera(filtro, 1, 0, 40));
}
