/* GLORIA UT DEUS
 * conatus me
 */

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include"pilas.h"
#include"tipo_elemento.h"
#include"Validacion.h"

#define MAX_BUFFER 101
#define MAX_LONGITUD 100

//IMPORTANTE: La recepción de claves de lista para el testeo está acotada en [-1000, 1000].

const int MAX_CLAVE = 1000;
const int MIN_CLAVE = -1000;

const char SI = 's';
const char NO = 'n';

//La complejidad temporal es O(n^3) (ver funcion obtener vector interseccion)

void cargar_buffer (char buffer[]) {

    for (int i = 0; i < MAX_BUFFER; i++) {

        buffer[i] = '\0';

    }

}

void cargar_pila_solo_claves (Pila pila) {

    int i = 0;

    char buffer[MAX_BUFFER];
    cargar_buffer(buffer);

    char cargar_otro_elemento[2];    //Para cargar el char
    cargar_otro_elemento[0] = SI;
    cargar_otro_elemento[1] = 0;
    cargar_otro_elemento[2] = '\0';

    int clave_a_cargar = 0;

    printf("\n¿Desea cargar un elemento?[s/n]: ");
    fgets(cargar_otro_elemento, 2, stdin);
    while(getchar() != '\n');

    while((cargar_otro_elemento[0] != SI) && (cargar_otro_elemento[0] != NO)) {

        printf("\n¿Desea cargar un elemento?[s/n]: ");
        fgets(cargar_otro_elemento, 2, stdin);
        while(getchar() != '\n');

    }

    while ((i < MAX_LONGITUD) && (cargar_otro_elemento[0] == SI)) {

        printf("\nIngrese una clave para el elemento de la pila[-1000, 1000]: ");
        fgets(buffer, 100, stdin);
        clave_a_cargar = EntradaEntera(buffer, 0, MIN_CLAVE, MAX_CLAVE);
        p_apilar(pila, te_crear(clave_a_cargar));


        printf("\n¿Desea cargar otro elemento más?[s/n]: ");
        fgets(cargar_otro_elemento, 2, stdin);
        while(getchar() != '\n');

        while((cargar_otro_elemento[0] != SI) && (cargar_otro_elemento[0] != NO)) {

            printf("\n¿Desea cargar otro elemento más?[s/n]: ");
            fgets(cargar_otro_elemento, 2, stdin);
            while(getchar() != '\n');

        }

        i++;

    }

}

void cargar_vector_vacio (int vector[MAX_LONGITUD], int limite_carga) {


    //Se carga el nuevo vector con valores de clave no válido
    for (int i = 0; i < limite_carga; i++) {

        vector[i] = MIN_CLAVE-1;

    }

}

//Devuelve la longitud del vector (y de la pila)
int cargar_vector_con_claves_pila (Pila pila, int claves[MAX_LONGITUD]) {

    int longitud = 0;
    TipoElemento aux;
    Pila pila_aux = p_crear();

    //Carga vector
    while ((longitud < MAX_LONGITUD) && !(p_es_vacia(pila))) {

        aux = p_desapilar(pila);
        claves[longitud] = aux->clave;
        p_apilar(pila_aux, aux);
        longitud++;

    }

    //Devuelve pila a su estado original
    for (int i = 0; i < longitud; i++) {

        aux = p_desapilar(pila_aux);
        p_apilar(pila, aux);

    }

    free(pila_aux);

    return longitud;

}

bool esta_en_vector (int vector[MAX_LONGITUD], int l_vector, int buscado) {

    bool encontrado = false;

    int i = 0;

    while ((i < l_vector) && !(encontrado)) {

        if (vector[i] == buscado) {

            encontrado = true;

        }

        i++;

    }

    return encontrado;

}

//Devuelve la longitud del vector interseccion tras cargarlo (sin repeticion)
int obtener_vector_interseccion_sin_repeticion (int vp_1[MAX_LONGITUD], int vp_1_longitud,
                                                int vp_2[MAX_LONGITUD], int vp_2_longitud,
                                                int v_interseccion[MAX_LONGITUD]) {

    int l_interseccion = 0;

    for (int i = 0; i < vp_1_longitud; i++) {

        for (int j = 0; j < vp_2_longitud; j++) {

            if (vp_1[i] == vp_2[j]) {

                if (l_interseccion == 0) {

                    v_interseccion[0] = vp_1[i];

                } else if (!esta_en_vector(v_interseccion, l_interseccion, vp_1[i])) {

                    v_interseccion[l_interseccion] = vp_1[i];

                }

                l_interseccion++;

            }

        }

    }

    return l_interseccion;

}

//Cambia toda coincidencia con la clave a_desactivar por una clave no válida
void desactivar_clave_en_vector (int vector[MAX_LONGITUD], int l_vector, int a_desactivar) {

    for (int i = 0; i < l_vector; i++) {

        if (vector[i] == a_desactivar) {

            vector[i] = MIN_CLAVE-1;

        }

    }

}

void cargar_pila_interseccion (Pila pila_1, int v_interseccion[MAX_LONGITUD],
                               int l_interseccion, Pila pila_interseccion) {

    Pila pila_aux = p_crear();
    TipoElemento aux;
    TipoElemento aux_interseccion;

    while (!p_es_vacia(pila_1)) {

        aux = p_desapilar(pila_1);

        if (esta_en_vector(v_interseccion, l_interseccion, aux->clave)) {

            aux_interseccion = te_crear(aux->clave);
            p_apilar(pila_interseccion, aux_interseccion);
            desactivar_clave_en_vector(v_interseccion, l_interseccion, aux->clave);

        }

        p_apilar(pila_aux, aux);

    }

    while (!p_es_vacia(pila_aux)) {

        aux = p_desapilar(pila_aux);
        p_apilar(pila_1, aux);

    }

    free(pila_aux);

}

Pila obtener_pila_interseccion (Pila pila_1, Pila pila_2) {

    Pila pila_interseccion = p_crear();

    if ((p_es_vacia(pila_1)) || (p_es_vacia(pila_2))) {

        return pila_interseccion; //Si una de las pilas es vacia, las pilas no tienen elementos en comun entre sí
                                  //Lo mismo sucede si ambas son vacias. En ambos casos se devuelve una pila vacia.
    }

    int vp_1[MAX_LONGITUD];
    int vp_2[MAX_LONGITUD];

    cargar_vector_vacio(vp_1, MAX_LONGITUD);
    cargar_vector_vacio(vp_2, MAX_LONGITUD);

    int vp_1_longitud = 0;
    int vp_2_longitud = 0;

    vp_1_longitud = cargar_vector_con_claves_pila(pila_1, vp_1);
    vp_2_longitud = cargar_vector_con_claves_pila(pila_2, vp_2);

    int v_interseccion[MAX_LONGITUD];
    int l_interseccion = obtener_vector_interseccion_sin_repeticion(vp_1, vp_1_longitud,
                                                                             vp_2, vp_2_longitud,
                                                                             v_interseccion);

    cargar_pila_interseccion(pila_1, v_interseccion, l_interseccion, pila_interseccion);

    return pila_interseccion;
}

void procesar_algoritmo () {

    Pila pila_1 = p_crear();
    Pila pila_2 = p_crear();
    Pila pila_interseccion;

    printf("\n--CARGUE LA PRIMERA PILA--\n\n");
    cargar_pila_solo_claves(pila_1);
    p_mostrar(pila_1);

    printf("\n--CARGUE LA SEGUNDA PILA--\n\n");
    cargar_pila_solo_claves(pila_2);
    p_mostrar(pila_2);

    pila_interseccion = obtener_pila_interseccion(pila_1, pila_2);
    printf("\nA continuación, la pila resultante:\n");
    p_mostrar(pila_interseccion);

    printf("\n\nPila 1 resulta:\n");
    p_mostrar(pila_1);

    printf("\n\nPila 2 resulta:\n");
    p_mostrar(pila_2);

    free(pila_1);
    free(pila_2);
    free(pila_interseccion);

}

void mensaje_bienvenida () {

    printf("\n--TP3-PTO7-INTERSECTAR-PILAS--\n\n");
    printf("\nLa complejidad algorítmica por tiempo de ejecución es O(n^3)\n");
    printf("\nRecuerde que si una de las pilas está vacia,\n");
    printf("El resultado será una pila vacía.\n");

}

void mostrar_menu () {

    printf("\n-------MENU-------\n");
    printf("1. Iniciar programa\n");
    printf("2. Salir\n");

}

int recibir_opcion () {

    int opcion = 0;

    char buffer[MAX_BUFFER];
    cargar_buffer(buffer);

    printf("\nIngrese su opcion[1 o 2]: ");
    fgets(buffer, 100, stdin);
    opcion = EntradaEntera(buffer, 0, 1, 2);

    return opcion;
}

void mostrar_complejidad () {



}

void procesar_menu (int opcion) {

    switch (opcion) {

        case 1:
            procesar_algoritmo();
        break;
        case 2:
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

    mensaje_bienvenida();
    mostrar_menu();
    int opcion = recibir_opcion();
    procesar_menu(opcion);
    despedida();

    return 0;

}
