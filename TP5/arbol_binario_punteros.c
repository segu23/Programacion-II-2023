#include "arbol_binario.h"

#include <stdio.h>
#include <stdlib.h>

static const int TAMANIO_MAXIMO = 100;                                              

#ifndef ARBOL_BINARIO_PUNTEROS_C
#define ARBOL_BINARIO_PUNTEROS_C

struct ArbolBinarioRep {
    NodoArbol raiz;
    int cant_nodos;
};

ArbolBinario a_crear() {
    ArbolBinario nuevo_arbol = (ArbolBinario) malloc(sizeof(struct ArbolBinarioRep));
    nuevo_arbol->raiz = NULL;
    nuevo_arbol->cant_nodos = 0;
    return nuevo_arbol;
}

bool a_es_vacio(ArbolBinario a) {
    return a->raiz == NULL;
}

bool a_es_lleno(ArbolBinario a) {
    return a->cant_nodos == TAMANIO_MAXIMO;
}

int a_cantidad_elementos(ArbolBinario a) {
    return a->cant_nodos;
}

bool a_es_rama_nula(NodoArbol pa) {
    return pa == NULL;
}

NodoArbol a_raiz(ArbolBinario a) {
    return a->raiz;
}

NodoArbol a_establecer_raiz(ArbolBinario a, TipoElemento te) {
    if (a->raiz != NULL) return a->raiz;
    a->raiz = n_crear(te);
    a->cant_nodos++;
    return a->raiz;  
}

NodoArbol a_conectar_hi(ArbolBinario a, NodoArbol pa, TipoElemento te) {
    if (a == NULL || pa == NULL) return NULL;
    pa->hi = n_crear(te);
    a->cant_nodos++;
    return pa->hi;    
}

NodoArbol a_conectar_hd(ArbolBinario a, NodoArbol pa, TipoElemento te) {
    if (a == NULL || pa == NULL) return NULL;
    pa->hd = n_crear(te);
    a->cant_nodos++;
    return pa->hd;  
}

bool n_buscar_eliminar(NodoArbol padre, NodoArbol hijo, bool eliminado) {
    if (padre == NULL) return eliminado;

    else if (padre->hi != NULL || padre->hd != NULL) {
    
        if (padre->hi == hijo) {
            if      (hijo->hi != NULL) padre->hi = hijo->hi;
            else if (hijo->hd != NULL) padre->hi = hijo->hd;
            eliminado = true; 
        }

        else if (padre->hd == hijo) {
            if      (hijo->hi != NULL) padre->hd = hijo->hi;
            else if (hijo->hd != NULL) padre->hd = hijo->hd;  
            eliminado = true;             
        }
    }

    else if (!eliminado) {
        n_buscar_eliminar(n_hijoizquierdo(padre), hijo, eliminado);
        n_buscar_eliminar(n_hijoderecho(padre),   hijo, eliminado);
    }
    
    return eliminado;
}

void eliminar_nodo(ArbolBinario a, NodoArbol n) {
    if (a == NULL || n == NULL || (n->hi != NULL && n->hd != NULL)) return;

    else if (a->raiz != NULL && a->cant_nodos = 1 && a->raiz == n) {
        free(a->raiz);
        a->raiz == NULL;
        a->cant_nodos--;
    }

    else if (n_buscar_eliminar(a->raiz, n, false)) {
        free(n);
        a->cant_nodos--;
    }
    

}

#endif