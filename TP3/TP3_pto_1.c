#include <stdio.h>
#include <stdlib.h>
#include "pilas_arreglos.c"
#include "tipo_elemento.c"

int main(){
    Pila pila = p_crear();

    TipoElemento elem;
    printf("---------------------------------------\n");
    printf("%i\n", p_es_vacia(pila));
    printf("1\n");
    printf("---------------------------------------\n");
    p_mostrar(pila);
    printf("Contenido de la pila: \n");
    printf("---------------------------------------\n");
    elem = te_crear(1);
    p_apilar(pila, elem);
    elem = te_crear(2);
    p_apilar(pila, elem);
    elem = te_crear(3);
    p_apilar(pila, elem);
    p_mostrar(pila);
    printf("Contenido de la pila: 3 2 1\n");
    printf("---------------------------------------\n");
    elem = p_desapilar(pila);
    printf("%i\n", elem->clave);
    printf("3\n");
    printf("---------------------------------------\n");
    p_mostrar(pila);
    printf("Contenido de la pila: 2 1\n");
    printf("---------------------------------------\n");
    printf("%i\n", p_es_vacia(pila));
    printf("0\n");
    printf("---------------------------------------\n");
    printf("%i\n", p_tope(pila)->clave);
    printf("2\n");
    printf("---------------------------------------\n");
    p_mostrar(pila);
    printf("Contenido de la pila: 2 1\n");
    printf("---------------------------------------\n");

    return 0;
}