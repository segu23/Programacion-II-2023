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
Desarrollar un algoritmo que dado tres conjuntos puedan demostrar la propiedad de la
transitividad: “si A es subconjunto de B y B a su vez es subconjunto de C, entonces A
es subconjunto de C”.
*/

bool BuscandoSubconjuntos(Conjunto C1, Conjunto C2) {     
    int nC1 = cto_cantidad_elementos(C1);
    int nC2 = cto_cantidad_elementos(C2);
    if (nC1 == 0 && nC2 == 0) return true;

    int contador = 0;
    TipoElemento X;

    for (int i = 1 ; i <= nC1 ; i++) {
        X = cto_recuperar(C1, i);
        if (cto_pertenece(C2, X->clave)) contador++;
    }

    if    (contador == nC1) return true;
    else                    return false;
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
                clave = EntradaEntera(filtro, 0, -999999, 999999);

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

    printf("\n---- TP NRO. 7: CONJUNTOS - PTO. 4 ----\n");

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

    printf("\n/ Verificando propiedad de la transitividad . . .\n");

    bool AB = BuscandoSubconjuntos(A, B);
    bool BC = BuscandoSubconjuntos(B, C);
    bool AC = BuscandoSubconjuntos(A, C);

    if (AB) printf("\n> A es subconjunto de B");
    else    printf("\n> A no es subconjunto de B");

    if (BC) printf("\n> B es subconjunto de C");
    else    printf("\n> B no es subconjunto de C");

    if (AC) printf("\n> A es subconjunto de C");
    else    printf("\n> A no es subconjunto de B");    

    if (AB && BC && AC) printf("\n\n/ Conclusion: se verifica la propiedad de la transitividad . . .\n\n");
    else                printf("\n\n/ Conclusion: no se verifica la propiedad de la transistividad . . .\n\n");
}
