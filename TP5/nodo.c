#include "nodo.h"

#include <stdlib.h>
#include <stdio.h>

#ifndef NODO_C
#define NODO_C

// retorna el hijo izquierdo
NodoArbol n_hijoizquierdo(NodoArbol N) {
    if (N == NULL) return NULL;
    else           return N->hi;
}

// retorna el hijo derecho
NodoArbol n_hijoderecho(NodoArbol N) {
    if (N == NULL) return NULL;
    else           return N->hd;
}

// Crea un Nodo y lo retorna
NodoArbol n_crear(TipoElemento te) {
    NodoArbol nuevo_nodo = malloc(sizeof(struct NodoArbolRep));
    nuevo_nodo->datos = te;
    nuevo_nodo->hi = NULL;
    nuevo_nodo->hd = NULL;
    nuevo_nodo->FE = 0;
    return nuevo_nodo;
}

// retorno el tipo elemento de un nodo o NULL si no existe
TipoElemento n_recuperar(NodoArbol N) {
    if (N == NULL) return NULL;
    else           return N->datos;
}

#endif