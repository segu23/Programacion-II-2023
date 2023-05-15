#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "validacion.h"
#include "tipo_elemento.c"
//#include "tipo_elemento.h"
//#include "colas.h"
#include "colas_punteros.c"

#define MAX 100
#define MAXV 1000
#define MINV -1000

// Dada una pila cargada con valores al azar realizar los siguientes ejercicios:
/*
Resolver los siguientes puntos:
    a. Informar si un elemento dado se encuentra en la cola.
    b. Agregar un nuevo elemento en una posición dada (colarse).
    c. Dado un elemento sacarlo de la cola todas las veces que aparezca.
    d. Contar los elementos de la cola.
    e. Realizar una función que realice una copia de una cola.
    f. Invertir del contenido de una cola sin destruir la cola original.    
*/

bool c_existe (Cola, int);
void c_insertar (Cola, TipoElemento, int);
void c_borrar (Cola, int);
Cola c_duplicar (Cola);
int  c_cantidad (Cola);
Cola c_invertir (Cola);

// bool c_existe (Cola cola, int clave): Informar si un elemento dado se encuentra en la cola
bool c_existe (Cola cola, int clave) {
    if(c_es_vacia(cola)) return false;

    TipoElemento aux;
    bool salida = false;
    int cantidad = c_cantidad(cola);

    for (int i = 0; i < cantidad; i++) {
        aux = c_desencolar(cola);
        if (aux->clave == clave) {
            salida = true;
        }
        c_encolar(cola, aux);
    }

    return salida;
}

// void c_insertar (Cola cola, TipoElemento elemento, int posicion): Agregar un nuevo elemento en una posición dada (colarse)
void c_insertar (Cola cola, TipoElemento elemento, int posicion) {
    if (c_es_llena(cola) || posicion > c_cantidad(cola) + 1) return;
    
    TipoElemento aux;
    Cola Caux = c_crear();
    int longitud = c_cantidad(cola);
    int cont = 1;

    if (posicion != longitud + 1) {
        while (!c_es_vacia(cola)) {
            aux = c_desencolar(cola);

            if (cont == posicion) c_encolar(Caux, elemento);
            c_encolar(Caux, aux);

            cont++;
        }
        while (!c_es_vacia(Caux)) c_encolar(cola, c_desencolar(Caux));
    }
    else c_encolar(cola, elemento);

    free(Caux);
}

// void c_borrar (Cola cola, int clave): Dado un elemento sacarlo de la cola todas las veces que aparezca
void c_borrar (Cola cola, int clave) {
    if (c_es_vacia(cola)) return;
    
    TipoElemento aux;
    Cola caux = c_crear();

    while (!c_es_vacia(cola)) {
        aux = c_desencolar(cola);
        if (aux->clave != clave) c_encolar(caux, aux); 
    }

    while (!c_es_vacia(caux)) c_encolar(cola, c_desencolar(caux));

    free(caux);
}

// Cola c_duplicar (Cola cola): Duplicar el contenido de una cola
Cola c_duplicar (Cola cola) {
    if (c_es_vacia(cola)) return c_crear();
    
    TipoElemento aux;
    Cola Cdup = c_crear();
    int cantidad = c_cantidad(cola);

    for (int i = 0; i < cantidad; i++) {
        aux = c_desencolar(cola);
        c_encolar(Cdup, aux);
        c_encolar(cola, aux);
    }

    return Cdup;
}

// int c_cantidad (Cola cola): Contar los elementos de la cola.
int c_cantidad (Cola cola) {
    if (c_es_vacia(cola)) return 0;
    
    TipoElemento aux;
    Cola Caux = c_crear();
    int cont = 0;

    while (!c_es_vacia(cola)) {
        c_encolar(Caux, c_desencolar(cola));
        cont++;
    }

    while (!c_es_vacia(Caux)) c_encolar(cola, c_desencolar(Caux));

    free(Caux);
    return cont;
}

// Cola c_invertir (Cola cola): Invertir del contenido de una cola sin destruir la cola original
Cola c_invertir (Cola cola) {
    if (c_es_vacia(cola)) return c_crear();

    int longitud = c_cantidad(cola);
    TipoElemento claves[longitud];
    TipoElemento aux;
    Cola Cinv = c_crear();

    for (int i = 0; i < longitud; i++) {
        aux = c_desencolar(cola);
        claves[i] = aux;
        c_encolar(cola, aux);
    }

    for (int t = longitud - 1; t >= 0; t--) {
        c_encolar(Cinv, claves[t]);
    }

    return Cinv;
}

int main () {
    char filtro[MAX];
    bool corriendo = true;
    TipoElemento elemento;
    int accion;
    int posicion, clave;
    Cola cl = c_crear();

    printf("\n// Generando cola . . . ");
    printf("\n<< Ingrese la longitud de la cola [0; 100]: ");
    fgets(filtro, MAX, stdin);
    int longitud = EntradaEntera(filtro, 0, 0, MAX);

    if (longitud != 0) {
        for (int i = longitud; i > 0; i--) {
            printf("\n<< Ingrese la clave (pos: %d) a la cola: ", i);
            fgets(filtro, MAX, stdin);
            elemento = te_crear(EntradaEntera(filtro, 0, MINV, MAXV));
            c_encolar(cl, elemento);
        } 
    }

    printf("\n// Pila generada . . . \n");
    c_mostrar(cl);
    
    printf(">> ");
    system("pause");

    while(corriendo) {
        printf("\n--> TP NRO. 5: COLAS <-- ");
        printf("\n_ 1 >> Buscar una clave y determinar si existe en la cola");
        printf("\n_ 2 >> Insertar un elemento nuevo en la cola");
        printf("\n_ 3 >> Eliminar de la cola todos los elementos dada una clave");
        printf("\n_ 4 >> Contar los elementos de la cola");
        printf("\n_ 5 >> Copiar el contenido de la cola");
        printf("\n_ 6 >> Invertir del contenido de una cola");
        printf("\n_ 0 >> Terminar programa");
        printf("\n\n<< Ingrese accion: ");
        fgets(filtro, MAX, stdin);
        accion = EntradaEntera(filtro, 0, 0, 6);

        switch (accion) {
            case 0 : {
                printf("\n// Terminando programa . . . ");
                corriendo = false;
            } break;

            case 1 : {
                if (!c_es_vacia(cl)) {
                    printf("\n<< Ingrese la clave a buscar en la cola: ");
                    fgets(filtro, MAX, stdin);
                    clave = EntradaEntera(filtro, 0, MINV, MAXV);
                    bool existe = c_existe(cl, clave);

                    if (existe) printf("\n>> El elemento con clave %d existe en la cola . . . \n", clave);
                    else        printf("\n>> El elemento con clave %d no existe en la cola . . . \n", clave);
                }
                else printf("\n>! Pila vacia. Imposible buscar . . . \n");

                printf("\n<< ");
                system("pause");
            } break;

            case 2 : {
                if (!c_es_llena(cl)) {
                    printf("\n// Longitud actual de la cola: %d \n", c_cantidad(cl));
                    printf("\n<< Ingrese la posicion (ordinal) del elemento a insertar en la cola: ");
                    fgets(filtro, MAX, stdin);
                    posicion = EntradaEntera(filtro, 1, 0, c_cantidad(cl) + 1);

                    printf("\n<< Ingrese la clave del elemento a insertar en la cola: ");
                    fgets(filtro, MAX, stdin);
                    TipoElemento elemento = te_crear(EntradaEntera(filtro, 0, MINV, MAXV));

                    c_insertar(cl, elemento, posicion);
                    printf("\n// Pila actualizada . . . \n");
                    c_mostrar(cl);
                }
                else printf("\n>! Cola llena. Imposible insertar . . .  \n");

                printf("<< ");
                system("pause");
            } break;

            case 3 : {
                if (!c_es_vacia(cl)) {
                    printf("\n// Cola original: \n");
                    c_mostrar(cl);

                    printf("\n<< Ingrese la clave a eliminar de la cola: ");
                    fgets(filtro, MAX, stdin);
                    clave = EntradaEntera(filtro, 0, MINV, MAXV);

                    c_borrar(cl, clave);
                    printf("\n// Cola actualizada . . . \n");
                    c_mostrar(cl);
                }
                else printf("\n>! Cola vacia. Imposible eliminar . . . \n");

                printf("<< ");
                system("pause");
            } break;

            case 4 : {
                printf("\n>> Cantidad de elementos de la cola: %d", c_cantidad(cl));

                printf("\n<< ");
                system("pause");
            } break;

            case 5 : {
                Cola Cdup = c_duplicar(cl);
                printf("\n// Cola original: \n");
                c_mostrar(cl);

                printf("\n// Nueva cola: \n");
                c_mostrar(Cdup);

                printf("<< ");
                system("pause");
            } break;

            case 6 : {
                Cola Cinv = c_invertir(cl);
                printf("\n// Cola original: \n");
                c_mostrar(cl);

                printf("\n// Cola invertida: \n");
                c_mostrar(Cinv);

                printf("<< ");
                system("pause");
            } break;

            default: break;
        }
    }
    printf("\n ----------------------------------------------------------");
    return 0;
}