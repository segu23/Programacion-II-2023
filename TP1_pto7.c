#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Implementación de recursividad - TP Nro. 1 - Punto 7

// Función recursiva de cola: grafíca la onda a base de valores bivaluados, High ('H') o Low ('L').
void OndaDigital(char onda[]) {
    static int i = 0;
    if (onda[i] != '\0') {
        if (i != 0 && onda[i - 1] == 'L' && onda[i] == 'H') {
            printf("|¯ ");
        }
        else if (i != 0 && onda[i - 1] == 'H' && onda[i] == 'L') {
            printf("|_");
        }
        else if (onda[i] == 'L') {
            printf("_");
        }
        else printf("¯ ");
        i++;
        OndaDigital(onda);
    }
}

void main () {
    int cantidad, bandera;
    char onda[100];
    for (int i = 0; i <= cantidad; i++) onda[i] = '\0';
    printf(" << Ingrese los valores de la onda (H/L) en mayuscula: ");
    fgets(onda, 100, stdin);
    do {
        bandera = 0;
        for(int i = 0; i < 100; i++){
            if (onda[i] != 'L' || onda[i] != 'H' || onda[i] != ' ') {                    
                bandera = 1;
                printf("\n <! Entrada invalida. Ingrese una secuencia valida: ");
                fgets(onda, 100, stdin);
            }
            else onda[i] = toupper(onda[i]);
        } 
    } while (bandera = 0);  
    OndaDigital(onda);
}