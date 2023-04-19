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
    nueva_lista->cursor = calloc(TAMANIO_MAXIMO, sizeof(struct Nodo));   
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
    int cont = 1, inicio = lista->inicio;
    struct Nodo temp2 = lista->cursor[inicio];
    while (cont != pos) {
        temp2 = lista->cursor[temp2.siguiente];
        cont++;
    } 
    return temp2.datos;
}

void l_agregar (Lista lista, TipoElemento elemento) {
    if (l_es_llena(lista)) return;                                                  //Controlo la lista llena
    int pos;
    pos = lista->libre;                                                               // Tomo el primer libre
    lista->libre = lista->cursor[pos].siguiente;
    lista->cursor[pos].datos = elemento;
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
    if (l_es_vacia(lista)) return;
    int* ptr_actual = &lista->inicio;                                               // Puntero al puntero del nodo actual
    int actual = lista->inicio;
    while (actual != NULO) {
        if (lista->cursor[actual].datos->clave == clave) {                          // Encontrar el nodo para borrar
            *ptr_actual = lista->cursor[actual].siguiente;                           // Actualizar el puntero del nodo anterior
            lista->cursor[actual].siguiente = lista->libre;                          // Agregar el nodo eliminado a la lista libre
            lista->libre = actual;
            lista->cantidad--;
            actual = *ptr_actual;                                                    // Continuar con el siguiente nodo
        } else {
            ptr_actual = &lista->cursor[actual].siguiente;                           // Actualizar el puntero del nodo anterior
            actual = lista->cursor[actual].siguiente;                                // Continuar con el siguiente nodo
        }
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
    if (l_es_vacia(lista) == true) return;
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
    int inicio = lista->inicio;
    struct Nodo actual = lista->cursor[inicio];
    while (actual.siguiente != NULO) {
        if (actual.datos->clave == clave) {
            return actual.datos;
        }
        actual = lista->cursor[actual.siguiente];
    }
    return NULL;
}

void l_mostrarLista (Lista lista) {
    int inicio = lista->inicio;
    struct Nodo temp2 = lista->cursor[inicio];
    printf("Contenido de la lista: ");
    if(l_es_vacia(lista)){
        return;
    }
    if(temp2.siguiente == NULO){
        printf("%d ", temp2.datos->clave);
    }
    while (temp2.siguiente != NULO) {
        printf("%d ", temp2.datos->clave);
        temp2 = lista->cursor[temp2.siguiente];
        if(temp2.siguiente == NULO){
            printf("%d ", temp2.datos->clave);
        }
    }
    printf("\n");
}

Iterador iterador (Lista lista) {
    Iterador iter = (Iterador) malloc(sizeof(struct IteradorRep));
    iter->posicionActual = lista->inicio;
    iter->lista = lista;
    return iter;
}

bool hay_siguiente (Iterador iterador) {
    return (iterador->posicionActual != NULO);
}

TipoElemento siguiente (Iterador iterador) {
    int posActual = iterador->posicionActual;
    TipoElemento actual = iterador->lista->cursor[posActual].datos;
    iterador->posicionActual = iterador->lista->cursor[posActual].siguiente;            // %
    return actual;
}
/*
%:  la estructuctura "iterador" referencia por dirección "lista" a campo "cursor" perteneciente a "ListaRep" que almacena la 
    dirección primera del espacio de memoria "cursor", con "posiciónActual" se puede indexar al "Nodo" correspondiente que almacena 
    la posición "siguiente" del siguiente nodo. 
*/

#endif