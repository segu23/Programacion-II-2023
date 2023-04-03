
#include <stdio.h>
#include "TP1_Validacion.h"

#define MAX 100

// Implementación de recursividad - TP Nro. 1 - Punto 7

// Función recursiva de cola: grafíca la onda a base de valores bivaluados, High ('H') o Low ('L').
void OndaDigital(char onda[], int i) {
    if (onda[i] != '\0') {
        if (onda[i] != ' ') {
            if      (i != 0 && onda[i - 1] != 'H' && onda[i] == 'H') printf("|¯¯");
            else if (i != 0 && onda[i - 1] != 'L' && onda[i] == 'L') printf("|_");
            else if (onda[i] == 'L') printf("_");
            else if (onda[i] == 'H') printf("¯¯");  
        }  
        OndaDigital(onda, ++i);
    }
}

void main () {
    char permitidos[3] = {'L', 'H', '\0'};
    char onda[MAX];
    for (int i = 0; i < MAX; i++) onda[i] = '\0';
    //memset(onda, '\0', MAX);
    do {
         printf("\n << Ingrese los valores de la onda (H/L): ");
         fgets(onda, MAX, stdin);
    }while(!CadenaValida(onda,  permitidos));
    OndaDigital(onda, 0);                                                          // La función recursiva funciona correctamente, falta terminar la función de validación
    printf("\n");
}
