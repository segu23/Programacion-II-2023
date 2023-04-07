#include <stdio.h>
#include "TP1_Validacion.h"

// Implementación de recursividad - TP Nro. 1 - Punto 2

// Función recursiva directa simple: realiza un producto contemplando los casos posibles de signos.
int Producto(int m, int n) {
    if (m == 0 || n == 0) {             // Caso base: el producto de cualquier número por 0 es 0
        return 0;
    } else if (m < 0 && n < 0) {        // Ambos números son negativos
        return Producto(-m, -n);
    } else if (m < 0) {                 // El primer número es negativo
        return -Producto(-m, n);
    } else if (n < 0) {                 // El segundo número es negativo
        return -Producto(m, -n);
    } else {                            // Ambos números son positivos
        return m + Producto(m, n-1);
    }
}

void main () {
    char filtro[100];
    int numero, factor;
    for (int i = 0 ; i < 100 ; i++) filtro[i] = '\0';
    printf("\n // Implementación de recursividad - TP Nro. 1 - Punto 2");
    printf("\n << Ingrese un numero entero: ");
    fgets(filtro, 100, stdin);
    numero = EntradaEntera(filtro, 0, 0, 0);
    fflush(stdin);
    printf(" << Ingrese el factor para realizar la multiplicación: ");
    for (int i = 0 ; i < 100 ; i++) filtro[i] = '\0';
    fgets(filtro, 100, stdin);
    factor = EntradaEntera(filtro, 0, 0, 0);
    fflush(stdin);
    printf(" >> Producto: %d\n", Producto(factor, numero));
}