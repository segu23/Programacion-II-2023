#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "validacion.h"
#include "tipo_elemento.c"
//#include "tipo_elemento.h"
#include "pilas.c"
//#include "pilas.h"

#define MAX 100

// Dada una pila cargada con valores al azar realizar los siguientes ejercicios:

//Pila cargar_pila (int, int, int);
bool p_existe (Pila, int);
void p_insertar (Pila, TipoElemento, int);
void p_borrar_primero (Pila, int);
void p_intercambiar_posicion (Pila, int, int);
Pila p_duplicar (Pila);
int  p_cantidad (Pila);

// Pila cargar_pila (int cantidad, int inferior, int superior): crea una pila de numeros aleatorios dado una longitud y los extremos de un intervalo de valores posibles
/*
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
*/// Función descartada

// TipoElemento p_existe (Pila pila, int clave): Buscar una clave y determinar si existe en la Pila (sin perder la pila)
bool p_existe (Pila pila, int clave) {
    if (p_es_vacia(pila)) return false;

    bool encontrada = false;
    TipoElemento aux;
    Pila Paux = p_crear();

    while (!p_es_vacia(pila)) {
        aux = p_desapilar(pila);

        if (aux->clave == clave) encontrada = true;
        p_apilar(Paux, aux);
    }

    while (!p_es_vacia(Paux)) {
        p_apilar(pila, p_desapilar(Paux));
    }

    free(Paux);
    return encontrada;
}

// void p_insertar (Pila pila, int posicion): Colocar en una posición ordinal determinada, recibida por parámetro, un nuevo elemento (Insertar un elemento nuevo)
void p_insertar (Pila pila, TipoElemento elemento, int posicion) {
    if (p_es_llena(pila) || posicion > p_cantidad(pila) + 1) return;

    int cont = 0;
    Pila Paux = p_crear();

    while (!p_es_vacia(pila)) {
        cont++;

        if (cont == posicion) p_apilar(Paux, elemento);
        else                  p_apilar(Paux, p_desapilar(pila));
    }

    if (posicion == p_cantidad(Paux) + 1) {
        p_apilar(pila, elemento);
        while  (!p_es_vacia(Paux)) p_apilar(pila, p_desapilar(Paux));
    } 
    
    else while (!p_es_vacia(Paux)) p_apilar(pila, p_desapilar(Paux));

    free(Paux);
}

// void p_borrar_primero (Pila pila, int clave): Eliminar de una pila un elemento dado (primera ocurrencia encontrada por la clave)
void p_borrar_primero (Pila pila, int clave) {
    if (p_es_vacia(pila)) return;

    bool primera = true;
    TipoElemento aux;
    Pila Paux = p_crear();

    while (!p_es_vacia(pila) && primera == true) {
        aux = p_desapilar(pila);

        if (aux->clave == clave && primera) primera = false; 
        else                                p_apilar(Paux, aux);
    }

    while (!p_es_vacia(Paux)) {
        p_apilar(pila, p_desapilar(Paux));
    }

    free(Paux);
}

// void p_intercambiar_posicion (Pila pila, int pos1, pos2): Intercambiar los valores de 2 posiciones ordinales de la pila, por ejemplo la 2da con la 4ta
void p_intercambiar_posicion (Pila pila, int pos1, int pos2) {
    if (p_es_vacia(pila) || pos1 > p_cantidad(pila) || pos2 > p_cantidad(pila) || pos1 == pos2) return;

    int primero;
    int segundo;

    if (pos1 < pos2) {
        primero = pos1;
        segundo = pos2;
    } else {
        primero = pos2;
        segundo = pos1;
    }

    int cont = 0;
    int longitud = p_cantidad(pila) + 1;
    TipoElemento aux;
    TipoElemento TEprimero;
    TipoElemento TEsegundo;
    Pila Paux = p_crear();

    while (!p_es_vacia(pila)) {
        cont++;
        aux = p_desapilar(pila);

        if      (cont == segundo) TEsegundo = aux;
        else if (cont == primero) TEprimero = aux;

        p_apilar(Paux, aux);
    }

    cont = 0;
    while (!p_es_vacia(Paux)) {
        cont++;
        aux = p_desapilar(Paux);

        if      (cont == longitud - primero) p_apilar(pila, TEsegundo);
        else if (cont == longitud - segundo) p_apilar(pila, TEprimero);
        else                                 p_apilar(pila, aux);
    }

    free(Paux);
}

// Pila p_duplicar (Pila pila): Duplicar el contenido de una pila
Pila p_duplicar (Pila pila) {
    if (p_es_vacia(pila)) return p_crear();

    Pila Paux = p_crear();
    Pila Pdup = p_crear();
    TipoElemento aux;

    while (!p_es_vacia(pila)) {
        p_apilar(Paux, p_desapilar(pila));
    }

    while (!p_es_vacia(Paux)) {
        aux = p_desapilar(Paux);
        p_apilar(pila, aux);
        p_apilar(Pdup, aux);
    }

    free(Paux);
    return Pdup;
}

// int p_cantidad (Pila pila): Contar los elementos de la pila
int p_cantidad (Pila pila) {
    if (p_es_vacia(pila)) return 0;

    Pila Paux = p_crear();
    int cont = 0;

    while (!p_es_vacia(pila)) {
        p_apilar(Paux, p_desapilar(pila));
    }

    while (!p_es_vacia(Paux)) {
        cont++;
        p_apilar(pila, p_desapilar(Paux));
    }

    free(Paux);
    return cont;
}

int main () {
    char filtro[MAX];
    bool corriendo = true;
    TipoElemento elemento;
    int accion, posicion, clave;
    Pila pl = p_crear();

    printf("\n // Generando pila . . . ");
    printf("\n << Ingrese la longitud de la pila [0; 100]: ");
    fgets(filtro, MAX, stdin);
    int longitud = EntradaEntera(filtro, 0, 0, MAX);

    if (longitud != 0) {
        for (int i = longitud; i > 0; i--) {
            printf("\n << Ingrese la clave (pos: %d) a la pila: ", i);
            fgets(filtro, MAX, stdin);
            elemento = te_crear(EntradaEntera(filtro, 0, 0, 0));
            p_apilar(pl, elemento);
        } 
    }
    /*
    printf("\n << Ingrese el valor minimo de generacion aleatoria: ");
    fgets(filtro, MAX, stdin);
    int minimo = EntradaEntera(filtro, 0, 0, 1000);

    printf("\n << Ingrese el valor maximo de generacion aleatoria: ");
    fgets(filtro, MAX, stdin);
    int maximo = EntradaEntera(filtro, 0, minimo, 1000);

    pl = cargar_pila(longitud, minimo, maximo); <-------------------------------------------// Función descartada
    */
    printf("\n // Pila generada . . . \n >> ");
    if (p_es_vacia(pl)) printf("Contenido de la pila: (vacio)");
    else p_mostrar(pl);
    

    printf("\n >> ");
    system("pause");

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
                printf("\n // Terminando programa . . . ");
                corriendo = false;
            } break;

            case 1: {
                if (!p_es_vacia(pl)) {
                    printf("\n << Ingrese la clave a buscar en la pila: ");
                    fgets(filtro, MAX, stdin);
                    clave = EntradaEntera(filtro, 0, 0, 0);
                    bool existe = p_existe(pl, clave);

                    if (existe) printf("\n >> El elemento con clave %d existe en la pila . . . ", clave);
                    else        printf("\n >> El elemento con clave %d no existe en la pila . . . ", clave);
                }
                else printf("\n >! Pila vacia. Imposible buscar . . .  \n");

                printf("\n << ");
                system("pause");
            } break;

            case 2: {
                if (!p_es_vacia(pl)) {
                    printf("\n // Longitud actual de la pila: %d \n", p_cantidad(pl));
                    printf("\n << Ingrese la posicion (ordinal) del elemento a insertar en la pila: ");
                    fgets(filtro, MAX, stdin);
                    posicion = EntradaEntera(filtro, 0, 1, p_cantidad(pl) + 1);

                    printf("\n << Ingrese la clave del elemento a insertar en la pila: ");
                    fgets(filtro, MAX, stdin);
                    TipoElemento elemento = te_crear(EntradaEntera(filtro, 0, 0, 0));

                    p_insertar(pl, elemento, posicion);
                    printf("\n // Pila actualizada . . . \n >> ");
                    p_mostrar(pl);
                }
                else printf("\n >! Pila vacia. Imposible insertar . . .  \n");

                printf("\n << ");
                system("pause");
            } break;

            case 3: {
                if (!p_es_vacia(pl)) {
                    printf("\n // Pila original: \n >> ");
                    p_mostrar(pl);

                    printf("\n << Ingrese la clave a eliminar (primera ocurrencia encontrada) en la pila: ");
                    fgets(filtro, MAX, stdin);
                    clave = EntradaEntera(filtro, 0, 0, 0);

                    p_borrar_primero(pl, clave);
                    printf("\n // Pila actualizada . . . \n >> ");
                    p_mostrar(pl);
                }
                else printf("\n >! Pila vacia. Imposible eliminar . . . \n");

                printf("\n << ");
                system("pause");
            } break;

            case 4: {
                if (!p_es_vacia(pl)) {
                    printf("\n << Ingrese la posicion (ordinal) del primer elemento a intercambiar: ");
                    fgets(filtro, MAX, stdin);
                    int pos1 = EntradaEntera(filtro, 0, 1, p_cantidad(pl));

                    printf("\n << Ingrese la posicion (ordinal) del segundo elemento a intercambiar: ");
                    fgets(filtro, MAX, stdin);
                    int pos2 = EntradaEntera(filtro, 0, 1, p_cantidad(pl));

                    printf("\n // Pila original: \n >> ");
                    p_mostrar(pl);

                    p_intercambiar_posicion(pl, pos1, pos2);
                    printf("\n // Pila actualizada . . . \n >> ");
                    p_mostrar(pl);
                }
                else printf("\n >! Pila vacia. Imposible intercambiar . . .  \n");

                printf("\n << ");
                system("pause");
            } break;

            case 5: {
                Pila Pdup = p_duplicar(pl);
                printf("\n // Pila original: \n >> ");
                if (p_es_vacia(pl)) printf("Contenido de la pila: (vacio)");
                else p_mostrar(pl);

                printf("\n // Nueva pila: \n >> ");
                if (p_es_vacia(pl)) printf("Contenido de la pila: (vacio)");
                else p_mostrar(pl);

                printf("\n << ");
                system("pause");
            } break;

            case 6: {
                printf("\n >> Cantidad de elementos de la pila: %d \n << ", p_cantidad(pl));
                system("pause");
            } break;

            default: break;
        }
    }
    printf("\n ----------------------------------------------------------");
    return 0;
}