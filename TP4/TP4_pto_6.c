/* GLORIA UT DEUS
 * LAUDATA MARIA
 * conatus me
 */

#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
#include"tipo_elemento.h"
#include"listas.h"
#include"pilas.h"
#include"colas.h"
#include"Validacion.h"

#define MAX_BUFFER 101
#define MAX_LONGITUD 100

const int TOTAL_RAND = 10;
const int NIVELADOR_RAND = 5;

typedef struct posiciones {

    int posicion_pila;
    int posicion_cola;

} posiciones_t;

void cargar_buffer (char buffer[]) {

    for (int i = 0; i < MAX_BUFFER; i++) {

        buffer[i] = '\0';

    }

}

int obtener_tamanio_pila () {

    int tamanio = -1;

    char buffer[MAX_BUFFER];
    cargar_buffer(buffer);

    printf("\nIngrese el tamanio de la pila [0, %d]: ", MAX_LONGITUD);
    fgets(buffer, 100, stdin);
    tamanio = EntradaEntera(buffer, 0, 0, MAX_LONGITUD);

    return tamanio;
}

int obtener_tamanio_cola () {

    int tamanio = -1;

    char buffer[MAX_BUFFER];
    cargar_buffer(buffer);

    printf("\nIngrese el tamanio de la cola [0, %d]: ", MAX_LONGITUD);
    fgets(buffer, 100, stdin);
    tamanio = EntradaEntera(buffer, 0, 0, MAX_LONGITUD);

    return tamanio;
}

Pila generar_pila_aleatoria (int tamanio_pila) {

    Pila pila = p_crear();

    if (tamanio_pila > 0) {

        for (int i = 1; i <= tamanio_pila; i++) {

            p_apilar(pila, te_crear((rand()%TOTAL_RAND) - NIVELADOR_RAND));

        }

    }

    return pila;
}

Cola generar_cola_aleatoria (int tamanio_cola) {

    Cola cola = c_crear();

    if (tamanio_cola > 0) {

        for (int i = 1; i <= tamanio_cola; i++) {

            c_encolar(cola, te_crear((rand()%TOTAL_RAND) - NIVELADOR_RAND));

        }

    }

    return cola;
}

int menor (int un_numero, int otro_numero) {

    if (un_numero <= otro_numero) {

        return un_numero;

    }

    return otro_numero;

}

bool elemento_esta (int clave, int claves[MAX_LONGITUD], int tamanio_claves) {

    bool esta = false;

    int i = 0;

    while ((!esta) && (i < tamanio_claves)) {

        if (clave == claves[i]) {

            esta = true;

        }

        i++;

    }

    return esta;

}

posiciones_t* crear_posiciones (int posicion_p, int posicion_c) {

    posiciones_t posiciones;
    posiciones_t* ptr_posiciones = &posiciones;

    posiciones.posicion_pila = posicion_p;
    posiciones.posicion_cola = posicion_c;

    return ptr_posiciones;

}

Lista generar_lista_interseccion (Pila pila, Cola cola,
                                  int tamanio_pila, int tamanio_cola) {

    Lista lista_interseccion = l_crear();

    if ((p_es_vacia(pila)) || (c_es_vacia(cola))) { //Si alguna de las colecciones está vacia, devuelve una lista vacia.

        return lista_interseccion;

    }

    Pila pila_aux = p_crear();
    Cola cola_aux = c_crear();

    int claves[MAX_LONGITUD];

    for (int k = 0; k < MAX_LONGITUD; k++) {

        claves[k] = TOTAL_RAND + 1;

    }

    int tamanio_claves = 1;

    TipoElemento p_elemento;
    TipoElemento c_elemento;

    TipoElemento aux;

    posiciones_t* posiciones;

    int i = 0;
    int j = 0;

    for (i = 1; i <= tamanio_pila; i++) {

        p_elemento = p_desapilar(pila);

        for (j = 1; j <= tamanio_cola; j++) {

            c_elemento = c_desencolar(cola);

            if (p_elemento->clave == c_elemento->clave) {

                if (!elemento_esta(p_elemento->clave, claves, tamanio_claves)) {

                    printf("i %i\n", i);
                    printf("j %i\n", j);

                    aux = te_crear_con_valor(p_elemento->clave, (void*) crear_posiciones(i, j));
                    posiciones = (posiciones_t*) aux->valor;

                    // Esta seccion de codigo prueba que funciona, el problema esta en la lista
                    printf("\n%i %i %i\n", aux->clave, posiciones->posicion_pila, posiciones->posicion_cola);

                    //Luego de guardar el primero, la lista solo guarda basura dentro de los punteros a void
                    //No entiencuentro porque

                    l_insertar(lista_interseccion, aux, 1);

                    aux = l_buscar(lista_interseccion, p_elemento->clave);
                    posiciones = (posiciones_t*) aux->valor;

                    printf("\n%i %i\n", posiciones->posicion_pila, posiciones->posicion_cola);

                    //claves se utiliza para evitar repeticion, ya coteke que no es el problema
                    claves[tamanio_claves-1] = p_elemento->clave;
                    tamanio_claves++;

                }

            }

            c_encolar(cola_aux, c_elemento);

        }

        j = 1;

        while (!c_es_vacia(cola_aux)) {

            c_elemento = c_desencolar(cola_aux);
            c_encolar(cola, c_elemento);

        }

        p_apilar(pila_aux, p_elemento);

    }

    while (!p_es_vacia(pila_aux)) {

        p_elemento = p_desapilar(pila_aux);
        p_apilar(pila, p_elemento);

    }

    while (!c_es_vacia(cola_aux)) {

        c_elemento = c_desencolar(cola_aux);
        c_encolar(cola, c_elemento);

    }

    return lista_interseccion;

}

void mostrar_lista_con_valores (Lista lista) {

    TipoElemento elemento;
    posiciones_t* posiciones;
    Iterador l_iterador = iterador(lista);

    printf("\n");

    while (hay_siguiente(l_iterador)) {

        elemento = siguiente(l_iterador);
        posiciones = (posiciones_t*) elemento->valor;
        printf("%i %i %i, ", elemento->clave, (*posiciones).posicion_pila, (*posiciones).posicion_cola);

    }

    printf("\n");

}

void procesar_algoritmo () {

    int tamanio_pila = obtener_tamanio_pila();
    int tamanio_cola = obtener_tamanio_cola();

    Pila pila = generar_pila_aleatoria(tamanio_pila);
    Cola cola = generar_cola_aleatoria(tamanio_cola);

    printf("\nLa pila aleatoria es: ");
    p_mostrar(pila);
    printf("\nLa cola aleatoria es: ");
    c_mostrar(cola);

    //int tamanio_lista = menor(tamanio_pila, tamanio_cola);

    Lista lista_interseccion = generar_lista_interseccion(pila, cola, tamanio_pila, tamanio_cola);

    printf("\nLa lista resultante es: ");
    if (l_es_vacia(lista_interseccion)) {

        printf("vacía.\n");

    } else {

        mostrar_lista_con_valores(lista_interseccion);

    }

    printf("\nLa pila original queda: ");
    p_mostrar(pila);
    printf("\nLa cola original queda: ");
    c_mostrar(cola);

    free(lista_interseccion);
    free(cola);
    free(pila);

}

void mensaje_bienvenida () {

    printf("\n--TP4-PTO6-CREAR-LISTA-INTERSECCION--\n\n");

}

void mostrar_menu () {

    printf("\n-------MENU-------\n");
    printf("1. Algoritmo\n");
    printf("2. Complejidad\n");
    printf("3. Salir\n");

}

int recibir_opcion () {

    int opcion = 0;

    char buffer[MAX_BUFFER];
    cargar_buffer(buffer);

    printf("\nIngrese su opcion[1, 2 o 3]: ");
    fgets(buffer, 100, stdin);
    opcion = EntradaEntera(buffer, 0, 1, 3);

    return opcion;
}

void mostrar_complejidad () {

    printf("\nLa complejidad algorítmica por tiempo de ejecución es O(n^3)\n");

}

void procesar_menu (int opcion) {

    switch (opcion) {

        case 1:
            procesar_algoritmo();
        break;
        case 2:
            mostrar_complejidad();
        break;
        case 3:
            return;
        break;
        default:
            printf("Opcion ingresada no valida.\n");
        break;

    }

}

void despedida () {

    printf("\n¡Tenga un buen día!\n");

}

int main () {

    srand(time(NULL));

    mensaje_bienvenida();
    mostrar_menu();
    int opcion = recibir_opcion();
    procesar_menu(opcion);
    despedida();

    return 0;
}
