#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arbol_avl.h"
#include "arbol_binario_busqueda.h"
#include "Validacion.h"
#include "tipo_elemento.h"
#include "nodo.h"

//#include "tipo_elemento.c"
//#include "arbol_avl.c"
//#include "arbol_binario_busqueda.c"
//#include "nodo.c"

int arbol_max(int a, int b) {
    return a > b ? a : b;
}

int calcularAlturaArbol(NodoArbol nodo) {
    if (nodo == NULL) {
        return 0;
    }

    int altura_izq = calcularAlturaArbol(nodo->hi);
    int altura_der = calcularAlturaArbol(nodo->hd);

    return arbol_max(altura_izq, altura_der) + 1;
}

int cargarArboles(ArbolAVL arbolAVL, ArbolBinarioBusqueda arbolBB, int cantidadElementos, int numMax, int lastNumber){
    srand(lastNumber);
    int numero;
    for(int i = 0; i < cantidadElementos; i++) {
        numero = rand() % numMax;
        srand(numero);
        avl_insertar(arbolAVL, te_crear(numero));
        abb_insertar(arbolBB, te_crear(numero));
    }
    return numero;
}

int main(){
    char buffer[100];
    printf(" >> Ingrese la cantidad de elementos que serán cargados: ");
    fgets(buffer, 100, stdin);
    int cantidadElementos = EntradaEntera(buffer, 0, 1, 2000);
    printf(" >> Ingrese la cantidad de repeticiones que se harán: ");
    fgets(buffer, 100, stdin);
    int cantidadRepeticiones = EntradaEntera(buffer, 0, 1, 200);
    printf(" >> Ingrese el tope de valor a generar aleatoriamente: ");
    fgets(buffer, 100, stdin);
    int numMax = EntradaEntera(buffer, 0, 0, 100000);

    ArbolAVL arbolAVL = avl_crear();
    ArbolBinarioBusqueda arbolBB = abb_crear();
    int lastNumber = 0;

    int minAVL = 100000;
    int minBB = 100000;
    int maxAVL = -1;
    int maxBB = -1;
    int contAVL = 0;
    int contBB = 0;
    int alturaAVL;
    int alturaBB;

    for(int i = 0; i < cantidadRepeticiones; i++){
        lastNumber = cargarArboles(arbolAVL, arbolBB, cantidadElementos, numMax, lastNumber);
        alturaAVL = calcularAlturaArbol(avl_raiz(arbolAVL));
        printf("Altura Arbol AVL en la repetición %i es de %i\n", i+1, alturaAVL);
        alturaBB = calcularAlturaArbol(abb_raiz(arbolBB));
        printf("Altura Arbol BB en la repetición %i es de %i\n", i+1, alturaBB);

        if(alturaAVL < minAVL) minAVL = alturaAVL;
        if(alturaBB < minBB) minBB = alturaBB;
        if(alturaAVL > maxAVL) maxAVL = alturaAVL;
        if(alturaBB > maxBB) maxBB = alturaBB;
        contAVL += alturaAVL;
        contBB +=alturaBB;
    }

    printf("\n");
    printf(" -- Arbol AVL --\n");
    printf(" > Min: %i\n", minAVL);
    printf(" > Max: %i\n", maxAVL);
    printf(" > Promedio: %i\n", contAVL/cantidadRepeticiones);
    printf("\n");
    printf(" -- Arbol BB --\n");
    printf(" > Min: %i\n", minBB);
    printf(" > Max: %i\n", maxBB);
    printf(" > Promedio: %i\n", contBB/cantidadRepeticiones);
    printf("\n");
    printf(" - En conclusión, el auto-balanceo del arbol AVL es muy significante con respecto al binario de busqueda, \nllegando a reducirse practicamente a la mitad teniendo en cuenta su rama mas larga");
}
