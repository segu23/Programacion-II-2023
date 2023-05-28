#include "arboles_utilidades.h"

#include "listas_punteros.c"

#include <stdio.h>
#include <stdlib.h>

#ifndef ARBOLES_UTILIDADES_C
#define ARBOLES_UTILIDADES_C

void imprimir_espacios(int n) {
    for (int i = 0; i < n; i++) printf(" ");
}

void mostrar_arbol_binario_ascii_recursivo(NodoArbol n, int nivel, char* rama) {
    if (n == NULL) return;

    nivel += 4;
    
    mostrar_arbol_binario_ascii_recursivo(n->hd, nivel, " /");

    printf("\n");
    imprimir_espacios(nivel - 4);
    printf("%s", rama);
    printf("%d\n", n->datos->clave);

    mostrar_arbol_binario_ascii_recursivo(n->hi, nivel, " \\");

    nivel -= 4;
}

void mostrar_arbol_binario_ascii(NodoArbol n) {
    mostrar_arbol_binario_ascii_recursivo(n, 0, "");
}

void ln_mostrarLista (Iterador iter) {
    if (iter == NULL) {
        printf("\n>> Contenido (claves) del arbol: (vacio)\n");
        return;
    }

    struct Nodo *temp = iter->posicionActual;

    printf("\n>> Contenido (claves) del arbol: ");
    while (temp != NULL) {
        if (temp->datos->valor != NULL) printf(" %d", temp->datos->clave);
        else                            printf(" .");
        temp = temp->siguiente;
    }

    printf("\n");
}

void mostrar_arbol_binario (NodoArbol n, enum Recorrido r) {
    if (n == NULL) return;

    bool valido = true;

    switch (r) {
        case PRE_ORDEN : {
            Iterador iter = iterador_pre_orden(n);
            printf("\n>> Recorrido en PRE-ORDEN . . . \n");
            ln_mostrarLista(iter);
            free(iter);
            break;
        }

        case IN_ORDEN : {
            Iterador iter = iterador_in_orden(n);
            printf("\n>> Recorrido en IN-ORDEN . . . \n");
            ln_mostrarLista(iter);
            free(iter);
            break;
        }

        case POST_ORDEN : {
            Iterador iter = iterador_post_orden(n);
            printf("\n>> Recorrido en POST-ORDEN . . . \n");
            ln_mostrarLista(iter);
            free(iter);
            break;
        }

        case BFS : {
            Iterador iter = iterador_bfs(n);
            printf("\n>> Recorrido en BFS . . . \n");
            ln_mostrarLista(iter);
            free(iter);
            break;
        }

        default: printf("\n>! Recorrido invalido...");
        break;
    }
}

void preorden(NodoArbol n, Lista lista) {
    if (n == NULL) l_agregar(lista, te_crear(0));

    else {
        (n->datos)->valor = n;
        l_agregar(lista, n->datos);
        preorden(n->hi, lista);
        preorden(n->hd, lista);
    }
}

Iterador iterador_pre_orden (NodoArbol n) {
    if (n == NULL) return NULL;
    Lista pre_o = l_crear();
    preorden(n, pre_o);
    return iterador(pre_o);
}

void inorden(NodoArbol n, Lista lista) {
    if (n == NULL) l_agregar(lista, te_crear(0));

    else {
        inorden(n->hi, lista);
        (n->datos)->valor = n;
        l_agregar(lista, n->datos);

        inorden(n->hd, lista);
    }
}

Iterador iterador_in_orden (NodoArbol n) {
    if (n == NULL) return NULL;
    Lista in_o = l_crear();
    inorden(n, in_o);
    return iterador(in_o);
}

void postorden(NodoArbol n, Lista lista) {
    if (n == NULL) l_agregar(lista, te_crear(0));

    else {
        postorden(n->hi, lista);
        postorden(n->hd, lista);
        (n->datos)->valor = n;
        l_agregar(lista, n->datos);
    }
}

Iterador iterador_post_orden (NodoArbol n) {
    if (n == NULL) return NULL;
    Lista post_o = l_crear();
    postorden(n, post_o);
    return iterador(post_o);
}

Iterador iterador_bfs (NodoArbol n) {
    if (n == NULL) return NULL;
    
    NodoArbol naux;
    Lista lista = l_crear();
    Lista laux = l_crear();
    l_agregar(laux, te_crear_con_valor(1, n));

    while (!l_es_vacia(laux)) {
        naux = l_recuperar(laux, 1)->valor;
        l_eliminar(laux, 1);

        (naux->datos)->valor = naux;

        if (naux->datos->valor != NULL) l_agregar(lista, naux->datos);

        if (naux->hi != NULL) l_agregar(laux, te_crear_con_valor(1, naux->hi));

        if (naux->hd != NULL) l_agregar(laux, te_crear_con_valor(1, naux->hd));
    }

    free(laux);
    return iterador(lista);
}

#endif