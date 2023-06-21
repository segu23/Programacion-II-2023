#include <stdio.h>
#include <stdlib.h>
//#include <stdbool.h>

#include "conjuntos.h"
//#include "conjuntos_listas.c"

#include "tipo_elemento.h"
//#include "tipo_elemento.c"

#include "Validacion.h"
//#include "Validacion.c"

#define MAX 100

/*
Dados 3 conjuntos determinar si alguno es un subconjunto parcial o total del otro. Se
considera un subconjunto parcial cuando al menos la mitad de los elementos de uno
están en el otro. Determinar la complejidad algorítmica. 
*/

enum Subconjunto {
    TOTAL,
    PARCIAL,
    NM
};

enum Subconjunto BuscandoSubconjuntos(Conjunto C1, Conjunto C2) {       // La complejidad de la solución es de orden cuadrático independientemente de la implementación
    int nC1 = cto_cantidad_elementos(C1);
    int nC2 = cto_cantidad_elementos(C2);
    if (nC1 == 0 && nC2 == 0) return TOTAL;

    int contador = 0;
    TipoElemento X;
    enum Subconjunto Resultado;
                                                                        //                         | Arbol avl                                                | Listas (punteros)
    for (int i = 1 ; i <= nC1 ; i++) {                                  // Complejidad de bloque   | O(n * (n + n * log n)) = O(n**2 + n**2 log n) = O(n**2)  | O(n**2)
        X = cto_recuperar(C1, i);                                       // Complejidad de función  | O(n)                                                     | O(n)
        if (cto_pertenece(C2, X->clave)) contador++;                    // Complejidad de funciión | O(n * log n)                                             | O(n)
    }

    if      (contador == nC1)             Resultado = TOTAL;
    else if (contador >= (double)(nC1/2)) Resultado = PARCIAL;
    else                                  Resultado = NM;

    return Resultado;
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
    Conjunto C = cto_crear();

    printf("\n---- TP NRO. 7: CONJUNTOS - PTO. 7 ----\n");

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

    printf("\n%d< Ingrese la cardinalidad del conjunto C [0; 100]: ", __LINE__);
    fgets(filtro, MAX, stdin);
    int nC = EntradaEntera(filtro, 0, 0, 100);
    CargandoConjunto(C, nC);
    printf("\n");
    cto_mostrar(C);
    printf("\n< ");
    system("PAUSE");

    printf("\n/ Buscando subconjuntos . . .\n");    

    printf("\n/ Subconjuntos entre conjuntos A y B");
    enum Subconjunto AB = BuscandoSubconjuntos(A, B);
    if      (AB == TOTAL)    printf("\n> A es subconjunto TOTAL de B");
    else if (AB == PARCIAL)  printf("\n> A es subconjunto PARCIAL de B");
    else                     printf("\n> A no es subconjunto de B");

    enum Subconjunto BA = BuscandoSubconjuntos(B, C);
    if      (BA == TOTAL)    printf("\n> B es subconjunto TOTAL de A");
    else if (BA == PARCIAL)  printf("\n> B es subconjunto PARCIAL de A");
    else                     printf("\n> B no es subconjunto de A");

    printf("\n\n/ Subconjuntos entre conjuntos A y C");
    enum Subconjunto AC = BuscandoSubconjuntos(A, C);
    if      (AC == TOTAL)    printf("\n> A es subconjunto TOTAL de C");
    else if (AC == PARCIAL)  printf("\n> A es subconjunto PARCIAL de C");
    else                     printf("\n> A no es subconjunto de C");
    
    enum Subconjunto CA = BuscandoSubconjuntos(C, A);
    if      (CA == TOTAL)    printf("\n> C es subconjunto TOTAL de A");
    else if (CA == PARCIAL)  printf("\n> C es subconjunto PARCIAL de A");
    else                     printf("\n> C no es subconjunto de A");

    printf("\n\n/ Subconjuntos entre conjuntos B y C");
    enum Subconjunto BC = BuscandoSubconjuntos(B, C);
    if      (BC == TOTAL)    printf("\n> B es subconjunto TOTAL de C");
    else if (BC == PARCIAL)  printf("\n> B es subconjunto PARCIAL de C");
    else                     printf("\n> B no es subconjunto de C");

    enum Subconjunto CB = BuscandoSubconjuntos(C, B);
    if      (CB == TOTAL)    printf("\n> C es subconjunto TOTAL de B");
    else if (CB == PARCIAL)  printf("\n> C es subconjunto PARCIAL de B");
    else                     printf("\n> C no es subconjunto de B");

    printf("\n\n/ Conclusion: la complejidad algoritmica de la solucion es O(n**2), siendo n la cantidad de elementos del uno de los conjuntos si los dos conjuntos son iguales.\n  La complejidad es de orden cuadratico independientemente de la implementación que se use.\n\n");    
}
