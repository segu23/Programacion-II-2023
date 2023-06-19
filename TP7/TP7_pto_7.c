#include <stdio.h>
#include <stdlib.h>
//#include <stdbool.h>

#include "conjuntos.h"
#include "conjuntos_listas.c"

#include "listas_punteros.c"

#include "tipo_elemento.h"
#include "tipo_elemento.c"

#include "Validacion.h"

#define MAX 100

/*
Dados 3 conjuntos determinar si alguno es un subconjunto parcial o total del otro. Se
considera un subconjunto parcial cuando al menos la mitad de los elementos de uno
están en el otro. Determinar la complejidad algorítmica. 
*/

int ContandoElementosDeSubconjuntos(Conjunto C1, Conjunto C2) {
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

    return coincidencias;
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
    Conjunto C = cto_crear();

    printf("\n---- TP NRO. 7: CONJUNTOS - PTO. 7 ----\n");

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

    printf("\n%d< Ingrese la cardinalidad del conjunto C [1; 100]: ", __LINE__);
    fgets(filtro, MAX, stdin);
    int nC = EntradaEntera(filtro, 0, 1, 100);
    CargandoConjunto(C, nC);
    printf("\n");
    cto_mostrar(C);
    printf("\n< ");
    system("PAUSE");

    printf("\n/ Calculando intersecciones . . .\n");    

    int AB = ContandoElementosDeSubconjuntos(A, B);
    int AC = ContandoElementosDeSubconjuntos(A, C);
    int BC = ContandoElementosDeSubconjuntos(B, C);

    printf("\n/ Interseccion entre conjuntos A y B: ");
    if      (AB == nA && nA == nB)                         printf("\n> Los conjuntos A y B son iguales\n");
    else if (AB == nA && (AB > (double)(nB/2) && AB < nB)) printf("\n> El conjunto A es subconjunto parcial del conjunto B.");
    else if (AB == nB && (AB > (double)(nA/2) && AB < nA)) printf("\n> El conjunto B es subconjunto parcial del conjunto A.");
    else                                                   printf("\n> No existen subconjuntos entre los conjuntos A y B.");

    printf("\n/ Interseccion entre conjuntos A y C: ");
    if      (AC == nA && nA == nC)                         printf("\n> Los conjuntos A y C son iguales\n");
    else if (AC == nA && (AC > (double)(nC/2) && AC < nC)) printf("\n> El conjunto A es subconjunto parcial del conjunto C.");
    else if (AC == nC && (AC > (double)(nA/2) && AC < nA)) printf("\n> El conjunto C es subconjunto parcial del conjunto A.");
    else                                                   printf("\n> No existen subconjuntos entre los conjuntos A y C.");

    printf("\n/ Interseccion entre conjuntos B y C: ");
    if      (BC == nB && nB == nC)                         printf("\n> Los conjuntos A y C son iguales");
    else if (BC == nB && (BC > (double)(nC/2) && BC < nC)) printf("\n> El conjunto B es subconjunto parcial del conjunto C.");
    else if (BC == nC && (BC > (double)(nB/2) && BC < nB)) printf("\n> El conjunto C es subconjunto parcial del conjunto B.");
    else                                                   printf("\n> No existen subconjuntos entre los conjuntos B y C.");    

    printf("\n\n/ Conclusion: la complejidad algoritmica de la solucion es O(n**2), siendo n la cantidad de elementos del uno de los conjuntos si los dos conjuntos son iguales.\n\n");
}