#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "conjuntos.h"
#include "conjuntos_listas.c"

#include "listas_punteros.c"

#include "tipo_elemento.h"
#include "tipo_elemento.c"

#include "Validacion.h"

#define MAX 100

/*
Dados dos conjuntos de números naturales se pide determinar si son iguales sin
importar la posición de sus elementos. Determinar la complejidad algorítmica.
*/

bool ComparandoConjuntos(Conjunto C1, Conjunto C2) {
    int nC1 = cto_cantidad_elementos(C1);
    int nC2 = cto_cantidad_elementos(C2);
    int coincidencias = 0;
    TipoElemento T1, T2;

    for (int i = 1 ; i <= nC1 ; i++) {
        T1 = cto_recuperar(C1, i);

        for (int t = 1 ; t <= nC2 ; t++) {
            T2 = cto_recuperar(C2, t);

            if(T1->clave == T2->clave) coincidencias++;
        }
    }    

    if (coincidencias != nC1) return false;
    else                      return true;
}

void CargandoConjunto (Conjunto CTO, int nX) {
    char filtro[MAX];
    int clave;

    for (int i = 1 ; i <= nX ; i++) {
        printf("\n%d< Ingrese la clave del elemento nro. %d: ", __LINE__, i);
        fgets(filtro, MAX, stdin);
        clave = EntradaEntera(filtro, 0, 999999, 999999);
        cto_agregar(CTO, te_crear(clave));
    }
}

void main() {
    char filtro[MAX];

    Conjunto A = cto_crear();
    Conjunto B = cto_crear();

    printf("\n---- TP NRO. 7: CONJUNTOS - PTO. 8 ----\n");

    printf("\n%d< Ingrese la cardinalidad del conjunto A [1; 100]: ", __LINE__);
    fgets(filtro, MAX, stdin);
    int nA = EntradaEntera(filtro, 0, 1, 100);
    CargandoConjunto(A, nA);
    printf("\n");
    cto_mostrar(A);
    printf("\n< ");
    system("PAUSE");

    printf("\n%d< Ingrese la cardinalidad del conjunto B [1; 100]: ", __LINE__);
    fgets(filtro, MAX, stdin);
    int nB = EntradaEntera(filtro, 0, 1, 100);
    CargandoConjunto(B, nB);
    printf("\n");
    cto_mostrar(B);
    printf("\n< ");
    system("PAUSE");   

    printf("\n/ Comparando conjuntos . . .");

    if (ComparandoConjuntos(A, B)) printf("\n> Los conjuntos son iguales.");
    else                           printf("\n> Los conjuntos no son iguales.");

    printf("\n\n/ Conclusion: la complejidad algoritmica de la solucion es O(n**2), siendo n la cantidad de elementos del uno de los conjuntos si los dos conjuntos son iguales.\n\n");
}