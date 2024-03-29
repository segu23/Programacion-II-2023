#include <stdio.h>
#include <stdlib.h>
//#include <stdbool.h>

#include "conjuntos.h"
//#include "conjuntos_listas.c"

//#include "listas_punteros.c"

#include "tipo_elemento.h"
//#include "tipo_elemento.c"

#include "Validacion.h"
//#include "Validacion.c"

#define MAX 100

/*
Desarrollar un algoritmo capaz de resolver la diferencia simétrica (por la clave) entre
dos conjuntos. La diferencia simétrica es una operación entre dos conjuntos donde el
conjunto resultante está conformado por los elementos no comunes a los dos
conjuntos.
*/

Conjunto DiferenciaSimetrica(Conjunto C1, Conjunto C2) {     
    int nC1 = cto_cantidad_elementos(C1);
    int nC2 = cto_cantidad_elementos(C2);
    Conjunto CDS = cto_crear();
    if (nC1 == 0 && nC2 == 0) return CDS;

    int contador = 0;
    TipoElemento X;

    for (int i = 1 ; i <= nC1 ; i++) {
        X = cto_recuperar(C1, i);
        if (!cto_pertenece(C2, X->clave)) cto_agregar(CDS, X);
    }

    for (int t = 1 ; t <= nC2 ; t++) {
        X = cto_recuperar(C2, t);
        if (!cto_pertenece(C1, X->clave)) cto_agregar(CDS, X);
    }

    return CDS;
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

    printf("\n---- TP NRO. 7: CONJUNTOS - PTO. 5 ----\n");

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

    printf("\n/ Calculando diferencia simetrica entre A y B . . .\n");

    Conjunto CDS = DiferenciaSimetrica(A, B);

    printf("\n> Conjunto resultante: ");
    cto_mostrar(CDS);
    printf("\n");
}
