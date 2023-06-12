/* GLORIA UT DEUS
 * conatus me
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Validacion.h"
#include"tabla_hash.h"

#define MAX_STRING 30
#define TAM_PLEGAMIENTO 6
#define MITAD_PLEGAMIENTO 3

const int MIN_LEGAJO = 1;
const int MAX_LEGAJO = 999999;

const int INACTIVO = 0;
const int ACTIVO = 1;

const int MIN_OPCION_ARCHIVO = 1;
const int MAX_OPCION_ARCHIVO = 5;

const int MIN_OPCION_PRINCIPAL = 1;
const int MAX_OPCION_PRINCIPAL = 3;

const int MIN_OPCION_HASH = 1;
const int MAX_OPCION_HASH = 3;

typedef struct {

    int legajo;
    char apellido[MAX_STRING];
    char nombres[MAX_STRING];
    char domicilio[MAX_STRING];
    char telefono[MAX_STRING];
    int activo;

} alumno_t;

void cargar_buffer (char buffer[]) {

    for (int i = 0; i < MAX_STRING; i++) {

        buffer[i] = '\0';

    }

}

long int obtener_tamanio_archivo (FILE* archivo) {

    long int tamanio;

    fseek(archivo, 0 ,SEEK_END);

    tamanio = ftell(archivo);

    fseek(archivo, 0, SEEK_SET);

    return tamanio;

}

void poner_en_cero_cadena (char cadena[], int tam_cadena) {

    for (int i = 0; i < tam_cadena; i++) {

        cadena[i] = 0;

    }

}

void informe_de_alumnos(FILE* gestion) {

    alumno_t alumno_aux;

    int tam_lectura = 1;

    while (tam_lectura == fread(&alumno_aux, sizeof(alumno_t), 1, gestion)) {

        if (alumno_aux.activo == ACTIVO) {

            printf("\nACTIVO\n");

        } else {

            printf("\nINACTIVO\n");

        }
        printf("%i\n%s %s\n%s\n%s\n", alumno_aux.legajo, alumno_aux.apellido,
                                      alumno_aux.nombres, alumno_aux.domicilio,
                                      alumno_aux.telefono);

    }

}

int recibir_legajo_consulta (int max_legajo) {

    char cadena_aux[MAX_STRING];
    cargar_buffer(cadena_aux);

    printf("Ingrese el legajo del alumno a mostrar[1-%i]: ", max_legajo);
    scanf("%s", cadena_aux);
    while (getchar() != '\n');

    int legajo_consulta = EntradaEntera(cadena_aux, 1, MIN_LEGAJO, MAX_LEGAJO);

    return legajo_consulta;
}

void mostrar_alumno(FILE* gestion) {

    alumno_t alumno;

    fseek(gestion, sizeof(alumno_t)*(-1), SEEK_END);

    fread(&alumno, sizeof(alumno_t), 1, gestion);

    int max_legajo = alumno.legajo;

    fseek(gestion, 0, SEEK_SET); //Reseteo el cabezal de r/w sin cerrar el archivo.

    int legajo_consulta = recibir_legajo_consulta(max_legajo);

    if((legajo_consulta >= MIN_LEGAJO) && (legajo_consulta <= max_legajo)) {

        int registros_a_saltar = legajo_consulta - 1; //Los legajos comienzan del 1, al primero se accede sin saltar.

        fseek(gestion, sizeof(alumno_t)*registros_a_saltar, SEEK_SET);

        fread(&alumno, sizeof(alumno_t), 1, gestion);

        printf("Legajo: %i\n", alumno.legajo);
        printf("Apellido: %s\n", alumno.apellido);
        printf("Nombres: %s\n", alumno.nombres);
        printf("Domicilio: %s\n", alumno.domicilio);
        printf("Telefono: %s\n", alumno.telefono);

    } else {

        printf("El legajo %i no corresponde con un usuario.\n", legajo_consulta);

    }

}

void recibir_datos_alumno (alumno_t* alumno, int previo_mayor_legajo) {

    //Los legajos se generan automaticamente para poder acceder a ellos ordenadamente con el archivo binario
    alumno->legajo = previo_mayor_legajo + 1;

    printf("\nInicializando alumno con legajo %i.\n\n", alumno->legajo);

    char cadena_aux[MAX_STRING];
    cargar_buffer(cadena_aux);

    printf("Ingrese el apellido del alumno: ");
    scanf("%s", cadena_aux);
    strcpy(alumno->apellido, cadena_aux);
    strcat(alumno->apellido, "\0");

    while (getchar() != '\n');

    printf("Ingrese los nombres del alumno: ");
    scanf("%s", cadena_aux);
    strcpy(alumno->nombres, cadena_aux);
    strcat(alumno->nombres, "\0");

    while (getchar() != '\n');

    printf("Ingrese el domicilio del alumno: ");
    scanf("%s", cadena_aux);
    strcpy(alumno->domicilio, cadena_aux);
    strcat(alumno->domicilio, "\0");

    while (getchar() != '\n');

    printf("Ingrese el telefono del alumno: ");
    scanf("%s", cadena_aux);
    strcpy(alumno->telefono, cadena_aux);
    strcat(alumno->telefono, "\0");

    while (getchar() != '\n');

    alumno->activo = ACTIVO;
}

void alta_alumno (FILE* gestion) { //Todo usuario nuevo tiene un legajo +1 al usuario anterior, el archivo se abre en "a+b".

    alumno_t alumno_nuevo, alumno_aux;

    fseek(gestion, sizeof(alumno_t)*(-1), SEEK_END);

    fread(&alumno_aux, sizeof(alumno_t), 1, gestion);

    int mayor_legajo = alumno_aux.legajo;

    recibir_datos_alumno(&alumno_nuevo, mayor_legajo);

    fwrite(&alumno_nuevo, sizeof(alumno_t), 1, gestion);
}

int recibir_legajo_baja (int max_legajo) {

    char cadena_aux[MAX_STRING];
    cargar_buffer(cadena_aux);

    printf("Ingrese el legajo del alumno a dar de baja[1-%i]: ", max_legajo);
    scanf("%s", cadena_aux);
    while (getchar() != '\n');

    int legajo_baja = EntradaEntera(cadena_aux, 1, MIN_LEGAJO, max_legajo);

    return legajo_baja;
}

void baja_alumno (FILE* gestion) {

    alumno_t alumno;

    fseek(gestion, sizeof(alumno_t)*(-1), SEEK_END);

    fread(&alumno, sizeof(alumno_t), 1, gestion);

    int max_legajo = alumno.legajo;

    fseek(gestion, 0, SEEK_SET); //Reseteo el cabezal de r/w sin cerrar el archivo.

    int legajo_baja = recibir_legajo_baja(max_legajo);

    if((legajo_baja > 0) && (legajo_baja <= max_legajo)) {

        int registros_a_saltar = legajo_baja - 1; //Los legajos comienzan del 1, al primero se accede sin saltar.

        fseek(gestion, sizeof(alumno_t)*registros_a_saltar, SEEK_SET);

        fread(&alumno, sizeof(alumno_t), 1, gestion);

        alumno.activo = INACTIVO;

        fseek(gestion, -sizeof(alumno_t), SEEK_CUR);

        fwrite(&alumno, sizeof(alumno_t), 1, gestion);

    } else {

        printf("El legajo %i no corresponde con un usuario.\n", legajo_baja);

    }

}

int recibir_legajo_modificar (int max_legajo) {

    char cadena_aux[MAX_STRING];
    cargar_buffer(cadena_aux);

    printf("Ingrese el legajo del usuario a modificar[1-%i]: ", max_legajo);
    scanf("%s", cadena_aux);
    while (getchar() != '\n');

    int legajo_modificar = EntradaEntera(cadena_aux, 1, MIN_LEGAJO, max_legajo);

    return legajo_modificar;
}

void recibir_datos_alumno_modificar (alumno_t* alumno) {

    //El legajo no se puede modificar, dado que es la clave de busqueda del archivo de registros.

    char cadena_aux[MAX_STRING];
    cargar_buffer(cadena_aux);

    printf("Ingrese el nuevo apellido del alumno: ");
    scanf("%s", cadena_aux);
    strcpy(alumno->apellido, cadena_aux);
    strcat(alumno->apellido, "\0");

    while (getchar() != '\n');

    printf("Ingrese los nuevos nombres del alumno: ");
    scanf("%s", cadena_aux);
    strcpy(alumno->nombres, cadena_aux);
    strcat(alumno->nombres, "\0");

    while (getchar() != '\n');

    printf("Ingrese el nuevo domicilio del alumno: ");
    scanf("%s", cadena_aux);
    strcpy(alumno->domicilio, cadena_aux);
    strcat(alumno->domicilio, "\0");

    while (getchar() != '\n');

    printf("Ingrese el nuevo telefono del alumno: ");
    scanf("%s", cadena_aux);
    strcpy(alumno->telefono, cadena_aux);
    strcat(alumno->telefono, "\0");

    while (getchar() != '\n');

    alumno->activo = ACTIVO;
}

void modificar_alumno (FILE* gestion) {

    alumno_t alumno;

    fseek(gestion, sizeof(alumno_t)*(-1), SEEK_END);

    fread(&alumno, sizeof(alumno_t), 1, gestion);

    int max_legajo = alumno.legajo;

    fseek(gestion, 0, SEEK_SET); //Reseteo el cabezal de r/w sin cerrar el archivo.

    int legajo_modificar = recibir_legajo_modificar(max_legajo);

    if((legajo_modificar > 0) && (legajo_modificar <= max_legajo)) {

        int registros_a_saltar = legajo_modificar - 1; //Los legajos comienzan del 1, al primero se accede sin saltar.

        fseek(gestion, sizeof(alumno_t)*registros_a_saltar, SEEK_SET);

        fread(&alumno, sizeof(alumno_t), 1, gestion);

        recibir_datos_alumno_modificar(&alumno);

        fseek(gestion, -sizeof(alumno_t), SEEK_CUR);

        fwrite(&alumno, sizeof(alumno_t), 1, gestion);

    } else {

        printf("El legajo %i no corresponde con un usuario.\n", legajo_modificar);

    }

}

void mostrar_menu_archivo () {

    printf("\n\n  OPCIONES ARCHIVO BINARIO \n\n");
    printf("Informe de Alumnos            1\n");
    printf("Altas de Alumnos              2\n");
    printf("Bajas de Alumnos              3\n");
    printf("Modificaciones de Alumnos     4\n");
    printf("Fin                           5\n");

}

int recibir_opcion_archivo () {

    char cadena_aux[MAX_STRING];
    cargar_buffer(cadena_aux);

    mostrar_menu_archivo();

    printf("\nIngrese la acción a realizar[1-5]: ");
    scanf("%s", cadena_aux);
    while(getchar() != '\n');

    int opcion = EntradaEntera(cadena_aux, 1, MIN_OPCION_ARCHIVO, MAX_OPCION_ARCHIVO);

    return opcion;
}

void procesar_menu_archivo (char ruta_gestion[MAX_STRING]) {

    FILE* gestion;

    int opcion = 0;
    opcion = recibir_opcion_archivo();

    while (opcion != MAX_OPCION_ARCHIVO) {

        switch(opcion) {

            case 1:

                gestion = fopen(ruta_gestion, "rb");
                informe_de_alumnos(gestion);
                fclose(gestion);

            break;
            case 2:

                gestion = fopen(ruta_gestion, "a+b");
                alta_alumno(gestion);
                fclose(gestion);

            break;
            case 3:

                gestion = fopen(ruta_gestion, "r+b");
                baja_alumno(gestion);
                fclose(gestion);

            break;
            case 4:

                gestion = fopen(ruta_gestion, "r+b");
                modificar_alumno(gestion);
                fclose(gestion);

            break;
            default:

                printf("Valor de opción no válido\n");

            break;

        }

        opcion = recibir_opcion_archivo();

    }

}

void crear_primer_alumno (FILE* gestion) {

    alumno_t alumno;

    recibir_datos_alumno(&alumno, 0);

    fwrite(&alumno, sizeof(alumno_t), 1, gestion);

}

void interactuar_con_archivo (char ruta_gestion[]) {

    FILE* gestion;
    gestion = fopen(ruta_gestion, "a+b");

    if (obtener_tamanio_archivo(gestion) == 0) {

        printf("El archivo esta vacío.\n");
        printf("Ingrese un alumno para inicializarlo.\n");
        crear_primer_alumno(gestion);

    }

    fclose(gestion);

    procesar_menu_archivo(ruta_gestion);

}

int recibir_legajo_hash (int max_legajo) {

    char cadena_aux[MAX_STRING];
    cargar_buffer(cadena_aux);

    printf("\nIngrese el legajo del usuario a recuperar[1-%i]: ", max_legajo);
    scanf("%s", cadena_aux);
    while (getchar() != '\n');

    int legajo_hash = EntradaEntera(cadena_aux, 1, MIN_LEGAJO, max_legajo);

    return legajo_hash;

}

void mostrar_menu_hash () {

    printf("\n\n       OPCIONES HASH       \n\n");
    printf("Mostrar tabla                 1\n");
    printf("Recuperar y mostrar legajo    2\n");
    printf("Salir                         3\n");

}

int recibir_opcion_hash () {

    char cadena_aux[MAX_STRING];
    cargar_buffer(cadena_aux);

    mostrar_menu_hash();

    printf("\nIngrese la acción a realizar[1-3]: ");
    scanf("%s", cadena_aux);
    while(getchar() != '\n');

    int opcion = EntradaEntera(cadena_aux, 1, MIN_OPCION_HASH, MAX_OPCION_HASH);

    return opcion;

}

void procesar_menu_hash (TablaHash tabla_hash, FILE* gestion) {

    int opcion = 0;
    opcion = recibir_opcion_hash();

    int clave = 0;
    int* legajo;

    while (opcion != MAX_OPCION_HASH) {

        switch(opcion) {

            case 1:

                th_mostrar_solo_ocupados(tabla_hash);

            break;
            case 2:

                //El legajo es la clave, porque al alumno se lo busca en archivo binario mediante su legajo
                clave = recibir_legajo_hash((obtener_tamanio_archivo(gestion)/sizeof(alumno_t)));
                legajo = (int*) th_recuperar(tabla_hash, clave)->valor;
                printf("\nEl legajo guardado en la tabla hash es: %i.\n", *legajo);

            break;
            default:

                printf("Valor de opción no válido\n");

            break;

        }

        opcion = recibir_opcion_hash();

    }

}

void cargar_vector_claves_desde_archivo (int* vector_claves, FILE* gestion) {

    alumno_t alumno_aux;

    int tam_lectura = 1;

    int i = 0;

    while (tam_lectura == fread(&alumno_aux, sizeof(alumno_t), 1, gestion)) {

        if (alumno_aux.activo == ACTIVO) {

            vector_claves[i] = alumno_aux.legajo;
            i++;

        }

    }

}

int funcion_hash_por_plegamiento (int clave) {

    char cadena_plegamiento[TAM_PLEGAMIENTO];
    poner_en_cero_cadena(cadena_plegamiento, 6);
    strcat(cadena_plegamiento, "\0");

    sprintf(cadena_plegamiento, "%i", clave);

    int primera_mitad = (cadena_plegamiento[0]-48)*100 + (cadena_plegamiento[1]-48)*10 + (cadena_plegamiento[2]-48);
    int segunda_mitad = (cadena_plegamiento[3]-48)*100 + (cadena_plegamiento[4]-48)*10 + (cadena_plegamiento[5]-48);

    int posicion_hash = primera_mitad + segunda_mitad;

    return posicion_hash;

}

void procesar_hash (FILE* gestion) {

    int tamanio_hash = funcion_hash_por_plegamiento(MAX_LEGAJO); //MAX_LEGAJO = 999999 -> posicion hash 1998 -> 999999/(1998*5) = 100,5

    TablaHash tabla_hash = th_crear(tamanio_hash*5, (*funcion_hash_por_plegamiento));

    int claves_guardadas = obtener_tamanio_archivo(gestion)/sizeof(alumno_t);

    int* vector_claves;

    vector_claves = (int*) calloc(claves_guardadas, sizeof(int)); //Para guardar claves de acceso, sino void* valor no apuntará a nada en lo guardado en tablas hash.

    if (vector_claves != NULL) {

        cargar_vector_claves_desde_archivo(vector_claves, gestion);

        alumno_t alumno_aux;

        int tam_lectura = 1;

        int i = 0;

        while (tam_lectura == fread(&alumno_aux, sizeof(alumno_t), 1, gestion)) {

            if (alumno_aux.activo == ACTIVO) {

                th_insertar(tabla_hash, te_crear_con_valor(alumno_aux.legajo, &vector_claves[i]));
                i++;

            }

        }

        procesar_menu_hash(tabla_hash, gestion);

        free(vector_claves);

    } else {

        printf("\nMemoria insuficiente.\n");

    }

    free(tabla_hash);

}

void mostrar_menu_principal () {

    printf("\n\n        MENU PRINCIPAL        \n\n");
    printf("Trabajar con archivo           1\n");
    printf("Crear y visualizar tabla hash  2\n");
    printf("Salir                          3\n");

}

int recibir_opcion_principal () {

    char cadena_aux[MAX_STRING];
    cargar_buffer(cadena_aux);

    mostrar_menu_principal();

    printf("\nIngrese la acción a realizar[1-3]: ");
    scanf("%s", cadena_aux);
    while(getchar() != '\n');

    int opcion = EntradaEntera(cadena_aux, 1, MIN_OPCION_PRINCIPAL, MAX_OPCION_PRINCIPAL);

    return opcion;

}

void procesar_menu_principal () {

    char ruta_gestion[MAX_STRING];
    strcpy(ruta_gestion, "gestion.dat");
    FILE* gestion;

    int opcion = 0;
    opcion = recibir_opcion_principal();

    while (opcion != MAX_OPCION_PRINCIPAL) {

        switch(opcion) {

            case 1:

                interactuar_con_archivo(ruta_gestion);

            break;
            case 2:

                gestion = fopen(ruta_gestion, "a+b");

                if (obtener_tamanio_archivo(gestion) == 0) {

                    printf("El archivo está vacío. Seleccione la opción 1.\n");

                } else {

                    fclose(gestion);
                    gestion = fopen(ruta_gestion, "rb");
                    procesar_hash(gestion);
                    fclose(gestion);

                }

            break;
            default:

                printf("Valor de opción no válido\n");

            break;

        }

        opcion = recibir_opcion_principal();

    }

    printf("Ha salido del programa, hasta luego.\n");

}

int main () {

    procesar_menu_principal();

    return 0;
}
