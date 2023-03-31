#include <stdio.h>
#include <string.h>
#include <ctype.h>

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

char *CadenaValida (char entrada[], int largo, char permitidos[]) {                     
    int valido, i, CharValido;
    do {
        entrada[strcspn(entrada, "\n")] = '\0';
        valido = 1;
        CharValido = 0;
        for (i = 0; i < largo ; i++) {
            for (int t = 0 ; t < strlen(permitidos) ; t++){
                entrada[i] = toupper(entrada[i]);
                printf("%c", entrada[i]);
                if (entrada[i] != permitidos[t] && entrada[i] != '\0') {
                    CharValido++;
                }
                if (CharValido == strlen(permitidos)) {
                    printf("\n <! Entrada invalida. Ingrese una secuencia valida: ");
                    valido = 0;
                    break;
                }
            }    
            if (valido == 0) {
                break;
            }
        }
        if (valido == 0) {
            fgets(entrada, largo, stdin);
        }
    } while (valido == 1);
    return entrada;
}

void main () {
    int cantidad, bandera;
    char estados[3] = "LH ";
    char onda[MAX];
    for (int i = 0; i <= cantidad; i++) onda[i] = '\0';
    printf(" << Ingrese los valores de la onda (H/L) en mayuscula: ");
    fgets(onda, MAX, stdin);
    OndaDigital(CadenaValida(onda, MAX, estados));                      // La función recursiva funciona correctamente, falta terminar la función de validación
}