#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

void copiar_cadena_desde_x_hasta_y (char* destino, char* origen, int x, int y) {

    int i = 0;

    for (int j = x; i < y; j++) {

        destino[i] = origen[j];
        i++;

    }

}

bool es_palindromo (char* cadena) {

    bool palindromo = false;

    if (strlen(cadena) == 1) {

        palindromo = true;

    } else if (strlen(cadena) == 2) {

        palindromo = (cadena[0] == cadena[1]);

    } else if (cadena[0] == cadena[strlen(cadena)-1]) {

        char* cadena_menor;

        cadena_menor = (char*) calloc(strlen(cadena)-2, sizeof(char));

        copiar_cadena_desde_x_hasta_y(cadena_menor, cadena, 1, strlen(cadena)-2);

        strcat(cadena_menor, "\0");

        palindromo = es_palindromo(cadena_menor);

        free(cadena_menor);

    } else {

        palindromo = false;

    }

    return palindromo;

}

int main () {

    char* palabra;

    int tam_cadena = 200; //obtener_tam_cadena();

    palabra = (char*) calloc(tam_cadena, sizeof(char)); //Uso calloc porque inicializa los espacios de memoria en 0

    if (palabra != NULL) {

        printf("\nIngrese la palabra a procesar[1-%i caracteres]: ", tam_cadena);
        scanf("%s", palabra);
        
        while(getchar() != '\n'); 
        strcat(palabra,"\0");

        if (es_palindromo(palabra)) {

            printf("\nLa palabra %s es un palindromo.\n", palabra);

        } else {

            printf("\nLa palabra %s no es un palindromo.\n", palabra);

        }

        free(palabra);

    } else {

        printf("\nMemoria insuficiente.\n");

    }

    return 0;
}