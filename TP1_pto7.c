#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX 100

// Implementación de recursividad - TP Nro. 1 - Punto 7

// Función recursiva de cola: grafíca la onda a base de valores bivaluados, High ('H') o Low ('L').
void OndaDigital(char onda[]) {
    static int i = 0;
    if (onda[i] != '\0') {
        if (i != 0 && onda[i - 1] == 'L' && onda[i] == 'H') {
            printf("|¯¯");
        }
        else if (i != 0 && onda[i - 1] == 'H' && onda[i] == 'L') {
            printf("|_");
        }
        else if (onda[i] == 'L') {
            printf("_");
        }
        else printf("¯¯");
        i++;
        OndaDigital(onda);
    }
}

void copiar_cadena_desde_x_hasta_y (char* destino, char* origen, int x, int y) {

    int i = 0;

    for (int j = x; i < y; j++) {

        destino[i] = origen[j];
        i++;

    }

}

bool es_onda_valida (char* cadena) {

    bool cadena_valida = true;

    int i = 0;

    while ((i < strlen(cadena)) && (cadena_valida)) {

        if ((cadena[i] != 'L') && (cadena[i] != 'H')) {

            cadena_valida = false;

        }

        i++;

    }

    return cadena_valida;

}

void main () {
   
    char onda[MAX];
    
    for (int i = 0; i <= MAX; i++) onda[i] = '\0';
    
    printf(" << Ingrese los valores de la onda (H/L) en mayuscula: ");
    fgets(onda, MAX, stdin);
    
    char* onda_aux; // Desde aquí hasta línea 114 es para quitar el \n obtenido por fgets.

    onda_aux = (char*) calloc (strlen(onda)+1, sizeof(char));   //Uso calloc porque no conozco strlen(onda), ya que depende del usuario.
                                                                //+1 espacio para \0

    if (onda_aux != NULL) {

        copiar_cadena_desde_x_hasta_y(onda_aux, onda, 0, strlen(onda)-1); //Elimina el \n obtenido con fgets;

        strcpy(onda, onda_aux);  //Finalmente, regresa el contenido limpio a onda.

        free(onda_aux);

    } else {

        printf("Memoria insuficiente.\n");

    }
    
    if (es_onda_valida(onda)) {

        printf("\n");
        OndaDigital(onda);
        printf("\n");

    } else {

        printf("La cadena ingresada no es una onda válida.\n");

    }

}