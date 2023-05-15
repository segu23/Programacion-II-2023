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

const int TOTAL_RAND = 20;
const int NIVELADOR_RAND = 10;

//Se utiliza para guardar las posiciones, de los elementos en las colecciones, en los punteros a void de lista
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

Pila generar_pila_aleatoria (int tamanio_pila) {

    Pila pila = p_crear();

    if (tamanio_pila > 0) {

        int claves[MAX_LONGITUD];

        for (int i = 0; i < MAX_LONGITUD; i++) {

            claves[i] = TOTAL_RAND + 1;

        }

        int tamanio_claves = 0;

        int clave = 0;

        int cargados = 0;

        while (cargados < tamanio_pila) {

            clave = (rand()%TOTAL_RAND) - NIVELADOR_RAND;

            if (!elemento_esta(clave, claves, tamanio_claves)) {

                p_apilar(pila, te_crear(clave));

                claves[cargados] = clave;
                tamanio_claves++;

                cargados++;
            }

        }

    }

    return pila;
}

Cola generar_cola_aleatoria (int tamanio_cola) {

    Cola cola = c_crear();

    if (tamanio_cola > 0) {

        int claves[MAX_LONGITUD];

        for (int i = 0; i < MAX_LONGITUD; i++) {

            claves[i] = TOTAL_RAND + 1;

        }

        int tamanio_claves = 0;

        int clave = 0;

        int cargados = 0;

        while (cargados < tamanio_cola) {

            clave = (rand()%TOTAL_RAND) - NIVELADOR_RAND;

            if (!elemento_esta(clave, claves, tamanio_claves)) {

                c_encolar(cola, te_crear(clave));

                claves[cargados] = clave;
                tamanio_claves++;

                cargados++;
            }

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

    posiciones_t posiciones[MAX_LONGITUD];

    int i = 0;
    int j = 0;

    for (i = 1; i <= tamanio_pila; i++) {

        p_elemento = p_desapilar(pila);

        for (j = 1; j <= tamanio_cola; j++) {

            c_elemento = c_desencolar(cola);

            if (p_elemento->clave == c_elemento->clave) {

                if (!elemento_esta(p_elemento->clave, claves, tamanio_claves)) {

                    posiciones[tamanio_claves-1].posicion_pila = i;
                    posiciones[tamanio_claves-1].posicion_cola = j;

                    l_agregar(lista_interseccion, te_crear_con_valor(p_elemento->clave, &posiciones[tamanio_claves-1]));

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
