#include <stdio.h>
#include <stdlib.h>
#include "TP1_Validacion.h"

#define MAX 50
#define MIN 1
// Implementación de recursividad - TP Nro. 1 - Punto 10


// Función recursiva directa multiple: calcula los diferentes valores producto de la descomposición de N por B.
int Explosion(int n, int b, int *lista, int pos) {
    if (n <= b) { 
        lista[pos] = n; 
        return pos + 1; 
    }
    int n1 = n / b;
    int n2 = n - n1;
    pos = Explosion(n1, b, lista, pos); 
    pos = Explosion(n2, b, lista, pos); 
    return pos; 
}

void main() {
    int n, b;
    char filtro[100];
    for (int i = 0 ; i < 100 ; i++) filtro[i] = '\0';
    printf("\n < Ingrese el numero a explotar: ");
    fgets(filtro, MAX, stdin);
    n = EntradaEntera(filtro, 1, 0, MAX);
    fflush(stdin);
    printf("\n < Ingrese el valor de la bomba (nro. natural): ");
    fgets(filtro, MAX, stdin);
    for (int i = 0 ; i < 100 ; i++) filtro[i] = '\0';
    b = EntradaEntera(filtro, 1, MIN, MAX);
    fflush(stdin);
    int *lista = (int *) malloc(sizeof(int) * n); 
    int pos = Explosion(n, b, lista, 0); 
    for (int i = 0; i < pos; i++) { 
        printf("%d ", lista[i]);
    }
    printf("\n");
    free(lista); 
}





