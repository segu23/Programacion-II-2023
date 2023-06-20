/* GLORIA UT DEUS
 * conatus me
 */

//No es elegir que operación hacer, se hacen todas.

#include<stdio.h>
#include<stdbool.h>
#include"conjuntos.h"
#include"tipo_elemento.h"
#include"Validacion.h"

#define MAX_BUFFER 101

void cargar_buffer (char buffer[]) {

    for (int i = 0; i < MAX_BUFFER; i++) {

        buffer[i] = '\0';

    }

}

int obtener_tamanio_conjunto_uno () {

    int tam_cto_uno = -1;

    char buffer[MAX_BUFFER];
    cargar_buffer(buffer);

    printf("\nIngrese el tamaño del conjunto uno[0-100]: ");
    fgets(buffer, 100, stdin);
    tam_cto_uno = EntradaEntera(buffer, 0, 0, 100);

    return tam_cto_uno;
}

int obtener_tamanio_conjunto_dos () {

    int tam_cto_dos = -1;

    char buffer[MAX_BUFFER];
    cargar_buffer(buffer);

    printf("\nIngrese el tamaño del conjunto dos[0-100]: ");
    fgets(buffer, 100, stdin);
    tam_cto_dos = EntradaEntera(buffer, 0, 0, 100);

    return tam_cto_dos;

}

void cargar_conjunto (Conjunto un_conjunto, int tam_carga) {

    if(tam_carga != 0) {

        int i = 0;

        int aux = 0;

        char buffer[MAX_BUFFER];
        cargar_buffer(buffer);

        printf("/nA continuación, ingrese %i números válidos[-1000, 1000]:\n", tam_carga);

        while (i < tam_carga) {

            fgets(buffer, 100, stdin);
            aux = EntradaEntera(buffer, 0, -1000, 1000);

            cto_agregar(un_conjunto, te_crear(aux));

            i++;

        }

    }

}

void verificar_union (Conjunto cto_uno, Conjunto cto_dos, int tam_cto_uno, int tam_cto_dos, Conjunto union_uno_dos) {

    bool union_valida = true;

    TipoElemento e_uno_aux;
    TipoElemento e_dos_aux;

    int i = 1;

    while ((i <= tam_cto_uno) && (union_valida)) {

        e_uno_aux = cto_recuperar(cto_uno, i);

        if(!cto_pertenece(union_uno_dos, e_uno_aux->clave)) {

            union_valida = false;

        }

        i++;

    }

    int j = 1;

    while ((j <= tam_cto_dos) && (union_valida)) {

        e_dos_aux = cto_recuperar(cto_dos, j);

        if(!cto_pertenece(union_uno_dos, e_dos_aux->clave)) {

            union_valida = false;

        }

        j++;

    }

    if (union_valida) {

        printf("\nEl conjunto unión es correcto.\n");

    } else {

        printf("\nEl conjunto unión es incorrecto.\n");

    }

}

void verificar_interseccion (Conjunto cto_uno, Conjunto cto_dos, int tam_cto_uno, int tam_cto_dos, Conjunto interseccion) {

    bool interseccion_valida = true;

    TipoElemento e_uno_aux;
    TipoElemento e_dos_aux;

    int i = 1;
    int j = 1;

    while ((i <= tam_cto_uno) && (interseccion_valida)) {

        e_uno_aux = cto_recuperar(cto_uno, i);

        while ((j <= tam_cto_dos) && (interseccion_valida)) {

            e_dos_aux = cto_recuperar(cto_dos, j);

            if (e_uno_aux->clave == e_dos_aux->clave) {

                if(!cto_pertenece(interseccion, e_uno_aux->clave)) {

                    interseccion_valida = false;

                }

            }

        }

        j = 1;

        i++;

    }

    if (interseccion_valida) {

        printf("\nEl conjunto intersección es correcto.\n");

    } else {

        printf("\nEl conjunto intersección es incorrecto.\n");

    }

}

void verificar_diferencia (Conjunto cto_uno, Conjunto cto_dos, int tam_cto_uno, int tam_cto_dos, Conjunto diferencia) {

    bool diferencia_valida = true;

    TipoElemento e_uno_aux;
    TipoElemento e_dos_aux;

    int i = 1;
    int j = 1;

    while ((i <= tam_cto_uno) && (diferencia_valida)) {

        e_uno_aux = cto_recuperar(cto_uno, i);

        while ((j <= tam_cto_dos) && (diferencia_valida)) {

            e_dos_aux = cto_recuperar(cto_dos, j);

            if (e_uno_aux->clave == e_dos_aux->clave) {

                if(cto_pertenece(diferencia, e_uno_aux->clave)) {

                    diferencia_valida = false;

                }

            }

        }

        j = 1;

        i++;

    }

    if (diferencia_valida) {

        printf("\nEl conjunto diferencia es correcto.\n");

    } else {

        printf("\nEl conjunto diferencia es incorrecto.\n");

    }

}

void verificar_pertenencia (Conjunto cto_uno, Conjunto cto_dos, int tam_cto_uno, int tam_cto_dos) {

    bool pertenencia_valida = true;

    TipoElemento e_uno_aux;
    TipoElemento e_dos_aux;

    int i = 1;
    int j = 1;

    int pertenencias = 0;

    while ((i <= tam_cto_uno) && (pertenencia_valida)) {

        e_uno_aux = cto_recuperar(cto_uno, i);

        while ((j <= tam_cto_dos) && (pertenencia_valida)) {

            e_dos_aux = cto_recuperar(cto_dos, j);

            if (e_uno_aux->clave == e_dos_aux->clave) {

                pertenencias++;

            }

        }

        j = 1;

        i++;

    }

    pertenencia_valida = (pertenencias == tam_cto_uno);

    if (pertenencia_valida) {

        printf("\nEl primer conjunto pertenece al segundo.\n");

    } else {

        printf("\nEl primer conjunto no pertenece al segundo.\n");

    }

}

int main () {

    Conjunto conjunto_uno = cto_crear();
    Conjunto conjunto_dos = cto_crear();

    int tam_cto_uno = obtener_tamanio_conjunto_uno();
    int tam_cto_dos = obtener_tamanio_conjunto_dos();

    cargar_conjunto(conjunto_uno, tam_cto_uno);
    cargar_conjunto(conjunto_dos, tam_cto_dos);

    //Mostrar y verificar cada operacion

    Conjunto union_uno_dos = cto_union(conjunto_uno, conjunto_dos);
    printf("\nEl conjunto unión es:\n");
    cto_mostrar(union_uno_dos);

    verificar_union(conjunto_uno, conjunto_dos, tam_cto_uno, tam_cto_dos, union_uno_dos);

    Conjunto interseccion_uno_dos = cto_interseccion(conjunto_uno, conjunto_dos);
    printf("\nEl conjunto intersección es:\n");
    cto_mostrar(interseccion_uno_dos);

    verificar_interseccion(conjunto_uno, conjunto_dos, tam_cto_uno, tam_cto_dos, interseccion_uno_dos);

    Conjunto diferencia_uno_dos = cto_diferencia(conjunto_uno, conjunto_dos);
    printf("El conjunto diferencia entre el primer conjunto y el segundo es:\n");
    cto_mostrar(diferencia_uno_dos);

    verificar_diferencia(conjunto_uno, conjunto_dos, tam_cto_uno, tam_cto_dos, diferencia_uno_dos);

    Conjunto diferencia_dos_uno = cto_diferencia(conjunto_dos, conjunto_uno);
    printf("El conjunto diferencia entre el primer conjunto y el segundo es:\n");
    cto_mostrar(diferencia_dos_uno);

    verificar_diferencia(conjunto_dos, conjunto_uno, tam_cto_dos, tam_cto_uno, diferencia_dos_uno);

    verificar_pertenencia(conjunto_uno, conjunto_dos, tam_cto_uno, tam_cto_dos);

    verificar_pertenencia(conjunto_dos, conjunto_uno, tam_cto_dos, tam_cto_uno);


    //free necesarios

    free(conjunto_uno);
    free(conjunto_dos);
    free(union_uno_dos);
    free(interseccion_uno_dos);
    free(diferencia_uno_dos);
    free(diferencia_dos_uno);

    return 0;
}
