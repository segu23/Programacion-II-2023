#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "TP1_Validacion.h"

/*
Implementación de recursividad - TP Nro. 1 - Punto 8

Definir una función recursiva que dado un conjunto devuelva una lista con los
subconjuntos del mismo tales que la suma de los elementos de cada subconjunto
sumen una cantidad dada. Por ejemplo: Dado el conjunto A = {10, 3, 1, 7, 4, 2}. La
lista de los conjuntos que sumen 7 sería: R = [{3, 4}, {1, 4, 2}, {7}]
Ejemplos:
subconjuntosQueSumanN ({10, 3, 1, 7, 4, 2}, 7) => {{3, 4}, {1, 4, 2}, {7}}
subconjuntosQueSumanN ({10, 3, 1, 7, 4, 2}, 10) => {{10}, {3,7}, {3, 1, 4, 2}, {1, 7, 2}}
*/

void imprimirSubconjuntos(int *subconjunto, int longitud)
{
    int i;
    printf("{");
    for (i = 0; i < longitud; i++)
    {
        printf("%d", subconjunto[i]);
        if (i != longitud - 1)
            printf(", ");
    }
    printf("}\n");
}

void buscarSubconjuntos(int *conjunto, int longitud, int *subconjunto, int longitud_subconjunto, int suma_deseada)
{
    int suma_actual = 0;

    for (int i = 0; i < longitud_subconjunto; i++)
    {
        suma_actual += subconjunto[i];
    }

    // caso base de subconjunto válido
    if (suma_actual == suma_deseada && longitud_subconjunto > 0)
    {
        imprimirSubconjuntos(subconjunto, longitud_subconjunto);
        return;
    }


    if (longitud == 0)
    {
        return;
    }

    subconjunto[longitud_subconjunto] = conjunto[0];
    buscarSubconjuntos(conjunto + 1, longitud - 1, subconjunto, longitud_subconjunto + 1, suma_deseada);

    buscarSubconjuntos(conjunto + 1, longitud - 1, subconjunto, longitud_subconjunto, suma_deseada);
}

void subconjuntosQueSumanN(int *conjunto, int longitud, int suma_deseada)
{
    int *subconjunto = malloc(sizeof(int) * longitud);

    // llamado a la funcion recursiva
    buscarSubconjuntos(conjunto, longitud, subconjunto, 0, suma_deseada);

    free(subconjunto);
}

int main()
{
    char filtro[100];
    printf(" << Por favor, escribe la cantidad de números que quieres ingresar: ");
    fgets(filtro, 100, stdin);
    int longitud = EntradaEntera(filtro, 1, 0, 100);
    fflush(stdin);

    int conjunto[longitud];

    for (int i = 0; i < longitud; i++)
    {
        printf(" << Por favor, escribe el número para la posición %i: ", i);
        fgets(filtro, 100, stdin);
        conjunto[i] = EntradaEntera(filtro, 0, -99999, 99999);
        fflush(stdin);
    }

    int target;

    printf(" << Por favor, escribe el número objetivo: ");
    fgets(filtro, 100, stdin);
    target = EntradaEntera(filtro, 0, -99999, 99999);
    fflush(stdin);

    subconjuntosQueSumanN(conjunto, longitud, target);

    return 0;
}
