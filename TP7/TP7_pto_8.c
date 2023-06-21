#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "conjuntos.h"
//#include "conjuntos_listas.c"

//#include "listas_punteros.c"

#include "tipo_elemento.h"
//#include "tipo_elemento.c"

#include "Validacion.h"
//#include "Validacion.c"

#define MAX 100

/*
Dados dos conjuntos de números naturales se pide determinar si son iguales sin
importar la posición de sus elementos. Determinar la complejidad algorítmica.
*/

bool ComparandoConjuntos(Conjunto C1, Conjunto C2) {          // La complejidad de la solución es de orden cuadrático independientemente de la implementación
    int nC1 = cto_cantidad_elementos(C1);
    int nC2 = cto_cantidad_elementos(C2);
    if (nC1 == 0 && nC2 == 0) return true;
    int contador = 0;
    TipoElemento X;

    if (nC1 == nC2) {                                         //                        | Arbol avl                                                | Listas (punteros)
        for (int i = 1 ; i <= nC1 ; i++) {                    // Complejidad de bloque  | O(n * (n + n * log n)) = O(n**2 + n**2 log n) = O(n**2)  | O(n**2)
            X = cto_recuperar(C1, i);                         // Complejidad de función | O(n)                                                     | O(n)
            if (cto_pertenece(C2, X->clave)) contador++;      // Complejidad de función | O(n * log n)                                             | O(n)
        }
    }
    else return false;

    if   (contador == nC1) return true;
    else                   return false;
}

void CargandoConjunto (Conjunto CTO, int nX) {
    char filtro[MAX];
    int clave;
    bool repetido;

    if (nX != 0) {
        for (int i = 1 ; i <= nX ; i++) {
            do {
                repetido = false;
                printf("\n%d< Ingrese la clave del elemento nro. %d: ", __LINE__, i);
                fgets(filtro, MAX, stdin);
                clave = EntradaEntera(filtro, 0, 999999, 999999);

                if (cto_pertenece(CTO, clave)) {
                    repetido = true;
                    printf("\n>! El elemento ya existe en el conjunto, ingrese una clave valida . . .\n");
                }
                else cto_agregar(CTO, te_crear(clave));
            } while (repetido);
        }
    }
}

void main() {
    char filtro[MAX];

    Conjunto A = cto_crear();
    Conjunto B = cto_crear();

    printf("\n---- TP NRO. 7: CONJUNTOS - PTO. 8 ----\n");

    printf("\n/ Aviso: el TAD no admite el uso de multiconjuntos, por favor no ingresar claves repetidas.\n");

    printf("\n%d< Ingrese la cardinalidad del conjunto A [0; 100]: ", __LINE__);
    fgets(filtro, MAX, stdin);
    int nA = EntradaEntera(filtro, 0, 0, 100);
    CargandoConjunto(A, nA);
    printf("\n");
    cto_mostrar(A);
    printf("\n< ");
    system("PAUSE");

    printf("\n%d< Ingrese la cardinalidad del conjunto B [0; 100]: ", __LINE__);
    fgets(filtro, MAX, stdin);
    int nB = EntradaEntera(filtro, 0, 0, 100);
    CargandoConjunto(B, nB);
    printf("\n");
    cto_mostrar(B);
    printf("\n< ");
    system("PAUSE");   

    printf("\n/ Comparando conjuntos . . .");

    if (ComparandoConjuntos(A, B)) printf("\n> Los conjuntos son iguales.");
    else                           printf("\n> Los conjuntos no son iguales.");

    printf("\n\n/ Conclusion: la complejidad algoritmica de la solucion es O(n**2), siendo n la cantidad de elementos del uno de los conjuntos si los dos conjuntos son iguales.\n  La complejidad es de orden cuadratico independientemente de la implementación que se use.\n\n");    
}
