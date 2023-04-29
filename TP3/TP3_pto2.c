#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "validacion.h"
#include "tipo_elemento.c"
#include "tipo_elemento.h"
#include "pilas.c"
#include "pilas.h"

#define MAX 100

// Dada una pila cargada con valores al azar realizar los siguientes ejercicios:

Pila cargar_pila (int, int, int);
bool p_existe (Pila, int);
void p_insertar (Pila, TipoElemento, int);
void p_borrar_primero (Pila, int);
void p_intercambiar_posicion (Pila, int, int);
Pila p_duplicar (Pila);
int  p_cantidad (Pila);

// Pila cargar_pila (int cantidad, int inferior, int superior): crea una pila de numeros aleatorios dado una longitud y los extremos de un intervalo de valores posibles
Pila cargar_pila (int longitud, int minimo, int maximo) {
    srand(time(NULL));
    TipoElemento elemento;
    Pila pl = p_crear(); 

    if (longitud != 0) {
        for (int i = 0; i < longitud; i++) {
            elemento = te_crear(minimo + rand() / (RAND_MAX / (maximo - minimo + 1) + 1));
            p_apilar(pl, elemento);
        }
    }

    return pl;
}

// TipoElemento p_existe (Pila pila, int clave): Buscar una clave y determinar si existe en la Pila (sin perder la pila).
bool p_existe (Pila pila, int clave) {
    if (p_es_vacia(pila)) return false;

    bool encontrada = false;
    TipoElemento aux;
    Pila Paux = p_crear();

    while (p_es_vacia(pila) != true) {
        aux = p_desapilar(pila);

        if (aux->clave == clave) encontrada = true;
        p_apilar(Paux, aux);
    }

    while (p_es_vacia(Paux) != true) {
        p_apilar(pila, p_desapilar(Paux));
    }

    free(Paux);
    return encontrada;
}

// void p_insertar (Pila pila, int posicion): Colocar en una posición ordinal determinada, recibida por parámetro, un nuevo elemento (Insertar un elemento nuevo).
void p_insertar (Pila pila, TipoElemento elemento, int posicion) {
    if (p_es_llena(pila))            return;
    if (posicion > p_cantidad(pila)) return;
    int cont = 0;
    Pila Paux = p_crear();

    while (p_es_vacia(pila)) {
        p_apilar(Paux, p_desapilar(pila));
    }
    
    while (p_es_vacia(Paux) != true) {

        if (cont++ == posicion) p_apilar(pila, elemento);
        else                    p_apilar(pila, p_desapilar(Paux)); 
    }

    free(Paux);
}

// void p_borrar_primero (Pila pila, int clave): Eliminar de una pila un elemento dado (primera ocurrencia encontrada por la clave).
void p_borrar_primero (Pila pila, int clave) {
    if (p_es_vacia(pila)) return;

    bool primera = true;
    TipoElemento aux;
    Pila Paux = p_crear();

    while (p_es_vacia(pila) != true) {
        aux = p_desapilar(pila);

        if (aux->clave == clave && primera) primera = false;
        else                               p_apilar(Paux, aux);
    }

    while (p_es_vacia(Paux) != true) {
        p_apilar(pila, p_desapilar(Paux));
    }

    free(Paux);
}

// void p_intercambiar_posicion (Pila pila, int pos1, pos2): Intercambiar los valores de 2 posiciones ordinales de la pila, por ejemplo la 2da con la 4ta.
void p_intercambiar_posicion (Pila pila, int pos1, int pos2) {                                    
    if (p_es_vacia(pila) || pos1 > p_cantidad(pila) || pos2 > p_cantidad(pila) || pos1 == pos2) return;

    int primera;
    int segundo;

    if (pos1 < pos2) {
        primera = pos1;
        segundo = pos2;
    } else {
        primera = pos2;
        segundo = pos1;
    }

    int cont = 0;
    TipoElemento aux;
    TipoElemento TEprimera;
    TipoElemento TEsegunda;
    Pila Paux = p_crear();

    while (p_es_vacia(pila)) {
        cont++;
        aux = p_desapilar(pila);

        if      (cont == (p_cantidad(pila) - primera)) TEsegunda = aux;
        else if (cont == (p_cantidad(pila) - segundo)) TEprimera = aux;

        p_apilar(Paux, aux);
    }
    
    cont = 0;
    while (p_es_vacia(Paux) != true) {
        cont++;

        if      (cont == primera) p_apilar(pila, TEprimera);
        else if (cont == segundo) p_apilar(pila, TEsegunda);
        else                      p_apilar(pila, p_desapilar(Paux));
    }

    free(Paux);
}

// Pila p_duplicar (Pila pila): Duplicar el contenido de una pila.
Pila p_duplicar (Pila pila) {
    if (p_es_vacia(pila)) return p_crear();

    Pila Paux = p_crear();
    Pila Pdup = p_crear();
    TipoElemento aux;

    while (p_es_vacia(pila)) {
        p_apilar(Paux, p_desapilar(pila));
    }
    
    while (p_es_vacia(Paux) != true) {
        aux = p_desapilar(Paux);
        p_apilar(pila, aux);
        p_apilar(Pdup, aux);
    }

    free(Paux);
    return Pdup;
}

// int p_cantidad (Pila pila): Contar los elementos de la pila. 
int p_cantidad (Pila pila) {
    if (p_es_vacia(pila)) return 0;

    Pila Paux = p_crear();
    int cont = 0;

    while (p_es_vacia(pila)) {
        p_apilar(Paux, p_desapilar(pila));
    }
    
    while (p_es_vacia(Paux) != true) {
        cont++;
        p_apilar(pila, p_desapilar(Paux));
    }

    free(Paux);
    return cont;
}

int main () {
    char filtro[MAX];
    bool corriendo = true;
    int accion, posicion, clave;
    Pila pl;

    printf("\n << Generando pila base...");
    printf("\n\n << Ingrese la longitud de la pila [0; MAX]: ");
    fgets(filtro, MAX, stdin);
    int longitud = EntradaEntera(filtro, 0, 0, MAX);

    printf("\n\n << Ingrese el valor minimo de generación aleatoria: ");
    fgets(filtro, MAX, stdin);
    int minimo = EntradaEntera(filtro, 0, 0, 0);

    printf("\n\n << Ingrese el valor maximo de generación aleatoria: ");
    fgets(filtro, MAX, stdin);
    int maximo = EntradaEntera(filtro, 0, 0, 0);

    pl = cargar_pila(longitud, minimo, maximo);
    printf("\n >> Pila base generada: ");
    p_mostrar(pl);

    while(corriendo) {
        printf("\n --> TP NRO. 2: PILAS <-- ");
        printf("\n _ 1 >> Buscar una clave y determinar si existe en la pila");
        printf("\n _ 2 >> Insertar un elemento nuevo en la pila");
        printf("\n _ 3 >> Eliminar de la pila un elemento dado");
        printf("\n _ 4 >> Intercambiar los valores de 2 posiciones ordinales de la pila");
        printf("\n _ 5 >> Duplicar el contenido de una pila");
        printf("\n _ 6 >> Contar los elementos de la pila");
        printf("\n _ 0 >> Terminar programa");
        printf("\n\n << Ingrese accion: ");
        fgets(filtro, MAX, stdin);
        accion = EntradaEntera(filtro, 0, 0, 6);

        switch (accion) {
            case 0: {
                printf("\n >> Terminando programa...");
                corriendo = false;
            } break;

            case 1: {
                printf("\n << Ingrese la clave a buscar en la pila base: ");
                fgets(filtro, MAX, stdin);
                clave = EntradaEntera(filtro, 0, 0, 0);
                bool existe = p_existe(pl, clave);

                if (existe) printf("\n >> El elemento con clave %d existe en la pila base", clave);
                else        printf("\n >> El elemento con clave %d no existe en la pila base", clave);
            } break;
                
            case 2: {
                printf("\n << Ingrese la clave del elemento a insertar en la pila base: ");
                fgets(filtro, MAX, stdin);
                TipoElemento elemento = te_crear(EntradaEntera(filtro, 0, 0, 0));

                printf("\n >> Longitud actual de la pila base: %d", p_cantidad(pl));
                printf("\n << Ingrese la posicion (ordinal) del elemento a insertar en la pila base: ");
                fgets(filtro, MAX, stdin);
                posicion = EntradaEntera(filtro, 1, 1, p_cantidad(pl));
                
                p_insertar(pl, elemento, posicion);
                printf("\n >> Pila base actualizada: ");
                p_mostrar(pl);
            } break;

            case 3: {
                printf("\n << Ingrese la clave a eliminar (primera ocurrencia encontrada) en la pila base: ");
                fgets(filtro, MAX, stdin);
                clave = EntradaEntera(filtro, 0, 0, 0);

                p_borrar_primero(pl, clave);
                printf("\n >> Pila base actualizada: ");
                p_mostrar(pl);
            } break;

            case 4: {
                printf("\n << Ingrese la posicion (ordinal) del primer elemento a intercambiar: ");
                fgets(filtro, MAX, stdin);
                int pos1 = EntradaEntera(filtro, 0, 0, 0);

                printf("\n << Ingrese la posicion (ordinal) del segundo elemento a intercambiar: ");
                fgets(filtro, MAX, stdin);
                int pos2 = EntradaEntera(filtro, 0, 0, 0);

                p_intercambiar_posicion(pl, pos1, pos2);
                printf("\n >> Pila base actualizada: ");
                p_mostrar(pl);
            } break;

            case 5: {
                Pila Pdup = p_duplicar(pl);
                printf("\n >> Pila base: ");
                p_mostrar(pl);
                printf("\n >> Pila duplicada: ");
                p_mostrar(Pdup);
            } break;

            case 6: {
                printf("\n >> Cantidad de elementos de la pila base: %d", p_cantidad(pl));
            } break;

            default: break;
        }
    }
    return 0;
}