#include "listas.h"
#include <stdlib.h>
#include <stdio.h>

static const int TAMANIO_MAXIMO = 100;
static const int NULO = -1;

#ifndef TP2_Listas_Cursores
#define TP2_Listas_Cursores

struct Nodo {
    TipoElemento datos;
    int siguiente;                                                                 
};

struct ListaRep {
    struct Nodo *cursor;                                                            // Apuntador al Arreglo de Nodos
    int inicio;
    int libre;                                                                      // Contendrá los nodos libres o disponibles
    int cantidad;
};

struct IteradorRep {
    Lista lista;
    int posicionActual;
};

Lista l_crear () {
    Lista nueva_lista = (Lista) malloc(sizeof(struct ListaRep));
    nueva_lista->cursor = (Lista) calloc(TAMANIO_MAXIMO, sizeof(struct Nodo));   
    nueva_lista->cantidad = 0;
    nueva_lista->inicio = NULO;
    for (int i = 0; i < TAMANIO_MAXIMO - 2; i++) {                                  // Encadeno todos los libres
        nueva_lista->cursor[i].siguiente = i + 1;
    }
    nueva_lista->libre = 0;                                                         // Toma todos los nodos como libres
    nueva_lista->inicio = NULO;
    nueva_lista->cursor[TAMANIO_MAXIMO-1].siguiente = NULO;
    return nueva_lista;                                                             // retorno la lista creada
}

bool l_es_vacia (Lista lista) {
    return lista->cantidad == 0; 
}

bool l_es_llena (Lista lista) {
    return lista->cantidad == TAMANIO_MAXIMO; 
}

int l_longitud (Lista lista) {
    return lista->cantidad; 
}

TipoElemento l_recuperar (Lista lista, int pos) {
    struct Nodo *temp2 = lista->inicio;
    for (int i = 0; i < pos - 1; i++) {
        temp2 = temp2->siguiente;
    }
    return temp2->datos;
}

void l_agregar (Lista lista, TipoElemento elemento) {
    if (l_es_llena(lista)) return;                                                  //Controlo la lista llena
    int pos;
    pos = lista->libre;                                                               // Tomo el primer libre
    lista->libre = lista->cursor[pos].siguiente;
    lista->cursor[pos].datos = elemento;                                              // Asigno el dato
    lista->cursor[pos].siguiente = NULO;
    if (lista->inicio == NULO) {                                                    // Controlo que no sea el primero de la lista
        lista->inicio = pos;
    } 
    else {
        int q = lista->inicio;                                                      // lo ubico al final
        while (lista->cursor[q].siguiente != NULO) {
            q = lista->cursor[q].siguiente;
        }
        lista->cursor[q].siguiente = pos;                                             // Lo conecto con el ultimo
    }
    lista->cantidad++;
}

void l_borrar (Lista lista, int clave) {
    if (l_es_vacia(lista)) return;                                                  // Controlo la lista vacia
    int q; 
    int p = lista->inicio;
    while ((p != NULO) && (lista->cursor[p].datos->clave == clave)) {               // borro las claves que coinciden con el inicio
        q = p;
        lista->inicio = lista->cursor[p].siguiente;
        lista->cursor[q].siguiente = lista->libre;                                  // recupero el nodo en el libre para no perderlo
        lista->libre = q;
        lista->cantidad--;                                                          // Descuento 1 y arranco de nuevo desde el inicio
        p = lista->inicio;                                                          // Vuelvo a intentar desde el inicio
    }
    p = lista->inicio;                                                              // Borro las claves en el resto de la lista
    struct Nodo actual = lista->cursor[p];
    struct Nodo temp;
    while ((p != NULO) && (lista->cursor[p].siguiente != NULO)) {                   // Similar a punteros, solo no olvidar encadenar el libre
        if (lista->cursor[actual.siguiente].datos->clave == clave) {
            temp = lista->cursor[actual.siguiente];
            lista->cursor[p].siguiente = lista->cursor[temp.siguiente].siguiente;   // Punto de control; posible error de lógica
            lista->cantidad--;
        }
        else actual = lista->cursor[actual.siguiente];
    }
}

void l_insertar (Lista lista, TipoElemento elemento, int pos) {
    if (l_es_llena(lista)) return;                                                  // Control de lista llena
    int p = lista->libre;                                                           // Toma la primer posición libre
    lista->libre = lista->cursor[p].siguiente;
    lista->cursor[p].datos = elemento;
    lista->cursor[p].siguiente = NULO;
    if (pos == 1) {                                                                 // Controla si cambia el INICIO
        lista->cursor[p].siguiente = lista->inicio;
        lista->inicio = p;
    } 
    else {
        int temp = lista->inicio;                                                   // Busca la posición del resto de la lista
        for (int i = 0; i < pos - 2; i++) {
            temp = lista->cursor[temp].siguiente;
        }
        lista->cursor[p].siguiente = lista->cursor[temp].siguiente;
        lista->cursor[temp].siguiente = p;
    }
    lista->cantidad++;
}

void l_eliminar(Lista lista, int pos) {
    int p;
    int actual = lista->inicio;
    if (l_es_vacia == true) return;
    if (1 <= pos && pos <= l_longitud(lista)) {
        if (pos == 1) {
            p = actual;
            lista->inicio = lista->cursor[actual].siguiente;
            lista->cursor[p].siguiente = lista->libre;
            lista->libre = p;
        } 
        else {
            for (int i = 0; i < pos - 2; i++) {
                actual = lista->cursor[actual].siguiente;                           // actual apunta al nodo en posición (pos - 1)
            }
            p = lista->cursor[actual].siguiente;                                    // nodo en pos
            lista->cursor[actual].siguiente = lista->cursor[p].siguiente;           // nodo en pos + 1
            lista->cursor[lista->libre].siguiente = p;
            lista->libre = p;
        }
        lista->cantidad--;
    }
}

TipoElemento l_buscar (Lista lista, int clave) {
    struct Nodo *actual = lista->inicio;
    while (actual != NULL) {
        if (actual->datos->clave == clave) {
            return actual->datos;
        }
        actual = actual->siguiente;
    }
    return NULL;
}

void l_mostrarLista (Lista lista) {
    struct Nodo *temp2 = lista->inicio;
    printf("Contenido de la lista: ");
    while (temp2 != NULL) {
        printf("%d ", temp2->datos->clave);
        temp2 = temp2->siguiente;
    }
    printf("\n");
}

Iterador iterador (Lista lista) {
    Iterador iter = (Iterador) malloc(sizeof(struct IteradorRep));
    iter->posicionActual = lista->inicio;
    return iter;
}

bool hay_siguiente (Iterador iterador) {
    return (iterador->posicionActual != NULO); 
}

TipoElemento siguiente (Iterador iterador) {
    TipoElemento actual = l_recuperar(iterador->lista, (iterador->posicionActual)+1); 
    int posActual = iterador->posicionActual;
    iterador->posicionActual = iterador->lista->cursor[posActual].siguiente;            // %
    return actual;
}
/*
%:  la estructuctura "iterador" referencia por dirección "lista" a campo "cursor" perteneciente a "ListaRep" que almacena la 
    dirección primera del espacio de memoria "cursor", con "posiciónActual" se puede indexar al "Nodo" correspondiente que almacena 
    la posición "siguiente" del siguiente nodo. 
*/

#endif