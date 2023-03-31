#include <stdio.h>
#include "TP1_Validacion.h"

#define MAX 100

// Implementación de recursividad - TP Nro. 1 - Punto 8

typedef struct Subconjunto {
    int *sub;
} Subconjunto;

// Función recursiva por backtracking: suma los elementos, compara con el valor objetivo y produce un vector dado una dirección de memoria 
void SubconjuntosQueSumanN (int *conjunto, int n, int const cantidad, int pos, int i, int *acum, Subconjunto vector[]) {
    if (pos < cantidad && i < cantidad) {
        if (i == 0) {
            vector[i].sub = (int *) calloc(cantidad, sizeof(int));
            SubconjuntosQueSumanN(conjunto, n, cantidad, pos, i, acum, vector);
        }
        else if (*acum < n && pos + i < cantidad) {
            *acum += *(conjunto + pos + i);
            vector[i].sub[pos] = *(conjunto + pos + i);
            pos++;
            SubconjuntosQueSumanN(conjunto, n, cantidad, pos, i, acum, vector);
        }
        else if (*acum > n && pos + i < cantidad) {
            free(vector[i].sub);
            pos = 0;
            *acum = 0;
            SubconjuntosQueSumanN(conjunto, n, cantidad, pos, i, acum, vector);
        }
        else if (*acum == n) {
            vector[i].sub[pos + 1] = -749;
            pos = 0;
            if (i < cantidad) i++;
            SubconjuntosQueSumanN(conjunto, n, cantidad, pos, i, acum, vector);
        }
    }
}

void main() {
    char filtro[100];
    int t;
    int conjunto[] = {2, 5, 7, 3, 9};
    int n = 10;
    int cantidad = (int) (sizeof(conjunto)/sizeof(int));
    //int cantidad = 0;
    int pos = 0;
    int i = 0;
    int acum = 0;
    int *subconjunto = NULL;
    int primeravez = 1;
    Subconjunto vector[cantidad];
    for (t = 0 ; t < cantidad ; t++) vector[t].sub = NULL;
    /*
    for (t = 0 ; t < 100 ; t++) filtro[t] = '\0';
    printf(" << Ingrese el valor objetivo a acumular por subconjunto: ");
    fgets(filtro, 100, stdin);
    n = EntradaEntera(filtro, 1, 0, 0);
    printf(" << Ingrese al conjunto un nro. entero por vez (para terminar de ingresar escriba -t-): ");
    t = 0;
    do {
        fgets(filtro, MAX, stdin);
        if (strchr(filtro, 't') != NULL) conjunto[t] = EntradaEntera(filtro, 0, 0, 0);
        t++;
        if (t == MAX) {
            printf(" !! Sobrecarga de buffer: reinicie el ingreso ¡¡\n");
            for (t = 0 ; t < 100 ; t++) conjunto[t] = 0;
            t = 0;
        }
    } while (n != 0 && t <= MAX);
    */
    SubconjuntosQueSumanN(conjunto, n, cantidad, pos, i, &acum, vector);
    i = 0;
    t = 0;
    while (vector[i].sub != NULL) {
        while (vector[i].sub[t] != -749 || t < 100) {
            printf(" %d,", vector[i].sub[t]);                                   // Incompleto
        }
    }
}