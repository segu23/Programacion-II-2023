#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "tipo_elemento.h"
#include "tipo_elemento.c"
#include "pilas.h"
#include "pilas.c"
#include "Validacion.h"

#define MAX 100

/*
Invertir el contenido de una pila sin destruir la pila original. Se debe retornar la nueva
pila invertida y la original no se debe perder. Determinar la complejidad algorítmica
de la solución.

// Pila cargar_pila (int cantidad, int inferior, int superior): crea una pila de numeros aleatorios dado una longitud y los extremos de un intervalo de valores posibles
/*
Pila cargar_pila (int longitud, int minimo, int maximo) { <---------------------------------------// Función descartada
    srand(time(NULL));
    TipoElemento elemento;
    Pila pl = p_crear();

    if (longitud != 0) {
        for (int i = 0; i < longitud; i++) {
            elemento = te_crear(minimo + rand() / (RAND_MAX / (maximo - minimo + 1) + 1));
            p_apilar(pl, elemento);
        }
    }

    return pl;
}
*/ 

// Pila p_invertir (Pila pila): crea una pila con la secuencia invertida de elementos de otra pila
Pila p_invertir (Pila pila) {
    if (p_es_vacia(pila)) return pila;

    Pila Paux = p_crear();
    Pila Pinv = p_crear();
    TipoElemento aux;

    while (!p_es_vacia(pila)) {
        aux = p_desapilar(pila);

        p_apilar(Paux, aux);
        p_apilar(Pinv, aux);
    }

    while (!p_es_vacia(Paux)) {
        p_apilar(pila, p_desapilar(Paux));
    }

    free(Paux);
    return Pinv;
}

int main () {
    char filtro[MAX];
    Pila pl = p_crear();
    Pila Pinv;
    TipoElemento elemento;
    int  clave;

    printf("\n --> TP NRO. 2: PILAS <-- ");
    printf("\n << Generando pila...");
    printf("\n << Ingrese la longitud de la pila [0; 100]: ");
    fgets(filtro, MAX, stdin);
    int longitud = EntradaEntera(filtro, 0, 0, 100);

    for (int i = 0; i < longitud; i++) {
        printf("\n << Ingrese la clave nro. %d a la pila: ", i + 1);
        fgets(filtro, MAX, stdin);
        elemento = te_crear(EntradaEntera(filtro, 0, -1000, 1000));
        p_apilar(pl, elemento);
    }
    /*
    printf("\n << Ingrese el valor minimo de generación aleatoria: ");
    fgets(filtro, MAX, stdin);
    int minimo = EntradaEntera(filtro, 0, 0, 0);

    printf("\n << Ingrese el valor maximo de generación aleatoria: ");
    fgets(filtro, 100, stdin);
    int maximo = EntradaEntera(filtro, 0, 0, 0);

    pl = cargar_pila(longitud, minimo, maximo);   <-----------------------------------------// Función descartada
    */
    printf("\n >> Pila generada... \n ");
    p_mostrar(pl);

    Pinv = p_invertir(pl);
    printf("\n >> Pila invertida... \n ");
    p_mostrar(Pinv);

    printf("\n Complejidad algorítmica: la solución p_invertir(Pila) esta condicionado por el tamaño del problema dado por la longitud de la pila.");
    printf("\n La función cuenta con dos ciclos condicionados por el tamaño del problema, la complejidad de estas estructuras es la misma para ambas siendo de O(n).");
    printf("\n En el primer ciclo se vuelca el contenido de la pila original a una auxiliar y por copia a la pila invertida. El segundo ciclo vuelca el contenido");
    printf("\n de la pila auxiliar a la original logrando así conservar la pila original. En conclusión, sumando las complejidades de ambos ciclos y absorbiendo");
    printf("\n las complejidades constantes, la complejidad de la solución es O(2n) (lineal).");

    printf("\n\n >> ");
    system("pause");
    return 0;
}
