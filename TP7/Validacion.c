#include "Validacion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int EntradaEntera(char buffer[], int nroNat, int LimInferior, int LimSuperior) {
    int valido, numero, i;
    int nneg;
    char numeros[11] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-'};

    do {
        i = 0; nneg = 0;
        buffer[strcspn(buffer, "\n")] = '\0';
        valido = 1;
        if (strchr(buffer, ',') != NULL || strchr(buffer, '.') != NULL) {
            valido = 0;
            printf("\n <! Entrada invalida (decimal)");
        }

        do {
            if (strchr(numeros, buffer[i]) == NULL) {
                valido = 0;
                printf("\n <! Entrada invalida (alfabetico)");
            }
            i++;
        } while (buffer[i] != '\0' && valido == 1);
        
        if (strchr(buffer, '-') != NULL) nneg = 1;

        //printf("\n >! Contenido del buffer: %s", buffer);
        
        sscanf(buffer, "%d", &numero);

        //printf("\n >! Valor en transito: %d", numero);
        if (valido == 1) {
            if (nroNat == 1 && numero <= 0) {
                valido = 0;
                printf("\n <! Entrada invalida (valor no natural)");
            }
            else if (numero > LimSuperior && LimSuperior != LimInferior) {
                valido = 0;
                printf("\n <! Entrada invalida (valor fuera de rango)");
            }
            else if (numero < LimInferior && LimSuperior != LimInferior) {
                valido = 0;
                printf("\n <! Entrada invalida (valor fuera de rango)");
            }
        }

        if (valido == 0) {
            printf("\n << Ingrese un valor valido: ");
            fgets(buffer, 100, stdin);
        }
    } while (valido == 0);

    fflush(stdin);
    return numero;
}

int CadenaValida(char entrada[],  char permitidos[]) {
    int valido = 1 , i;
    entrada[strcspn(entrada, "\n")] = '\0';
    for (i = 0; entrada[i] != '\0' && valido != 0; i++) {
           entrada[i] = toupper(entrada[i]);
           if (strrchr(permitidos,  entrada[i]) == NULL) {
               printf(" >! Cadena invalida . . .\n");
               valido = 0;
            }
    }   
    return valido;
}