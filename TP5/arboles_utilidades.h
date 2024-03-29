#ifndef UTILIDADES_H
#define UTILIDADES_H

#include "listas.h"
#include "nodo.h"

enum Recorrido {
    PRE_ORDEN,
    IN_ORDEN,
    POST_ORDEN,
    BFS
};

void mostrar_arbol_binario_ascii (NodoArbol);

void mostrar_arbol_binario (NodoArbol, enum Recorrido);

Iterador iterador_pre_orden (NodoArbol);

Iterador iterador_in_orden (NodoArbol);

Iterador iterador_post_orden (NodoArbol);

Iterador iterador_bfs (NodoArbol);

#endif // UTILIDADES_H