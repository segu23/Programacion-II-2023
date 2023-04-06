#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef TP1_Validacion
#define TP1_Validacion

/*
Instrucciones de uso de la función "EntradaEntera": esta función emite un aviso de reentrada por cada caso de no validación:
    - Si la entrada es decimal (opcional).
    - Si la entrada contiene caracteres alfabeticos.
    - Si la entrada no es natural (opcional).
    - Si la entrada se halla fuera de rango (opcional).

La función retornara un nro. entero válido según si se requiera que sea natural o que se halle dentro de un rango como si no.

1er parámetro (char buffer[]): la instrucción requiere que toda ingreso por teclado a verificar sea proveido dentro de un "char vector[]".
todos los espacios del vector deben estar inicializados con el carácter "\0" antes de asignarle el input.

2do parámetro (int nroNat): parámetro de uso opcional, funciona como un booleano (1 = verdadero, 0 = falso). 
Si se desea que la entrada solo admita nros. naturales se debe poner este parámetro en 1, e.g. "EntradaEntera(entrada, 1, 0, 0)". 
en caso contrario, ponga 0, e.g. "EntradaEntera(entrada, 1, 0, 0)". También determina la funcionalidad de verificar la presencia de comas
"," o ".", si la nroNat es "1" entonces saldra el mensaje de error para reingreso.

3er parámetro y 4to parámetro (int LimInferior, int LimSuperior): Si se desea, la función puede verificar que la entrada se encuentre 
dentro de un rango dado incluyendo los extremos,  e.g. "EntradaEntera(entrada, 1, 1, 5)". Para inhabilitar esta funcionalidad se debe poner 
ambos limites con un mismo valor, e.g. "EntradaEntera(entrada, 1, 0, 0)". 
*/

int EntradaEntera(char buffer[], int nroNat, int LimInferior, int LimSuperior) {
    int valido, numero;
    do {
        buffer[strcspn(buffer, "\n")] = '\0';
        valido = 1;
        if (nroNat == 1 && strchr(buffer, ',') != NULL || strchr(buffer, '.') != NULL) {
            valido = 0;
            printf("\n <! Entrada invalida (decimal); ingrese un valor entero: ");

        }       
        if (sscanf(buffer, "%d", &numero) != 1) {
            valido = 0;
            printf("\n <! Entrada invalida (alfabetico); ingrese un valor entero: ");
        } else {
            if (nroNat == 1 && numero <= 0) {
                valido = 0;
                printf("\n <! Entrada invalida (valor no natural); ingrese un valor entero: ");
            }
            if (nroNat == 1 && numero > LimSuperior && LimSuperior != LimInferior) {
                valido = 0;
                printf("\n <! Entrada invalida (valor fuera de rango); ingrese un valor entero: ");
            }
            if (nroNat == 1 && numero < LimInferior && LimSuperior != LimInferior) {
                valido = 0;
                printf("\n <! Entrada invalida (valor fuera de rango); ingrese un valor entero: ");
            }
        }
        if (valido == 0) fgets(buffer, 100, stdin);
    } while (valido == 0);
    fflush(stdin);
    return numero;
}

/*
Instrucciones de uso de la función "CadenaValida": esta función retorna un int como booleano (1 = V, 0 = F) dado una cadena de caracteres que se desea verficar 
y otra cadena con los caracteres permitidos (en mayúscula) por el programador, e.g. CadenaValida(entrada, {'a', 'b', 'c', '\0'})
*/
int CadenaValida(char entrada[],  char permitidos[]) {
    int valido = 1 , i;
    entrada[strcspn(entrada, "\n")] = '\0';
    for (i = 0; entrada[i] != '\0' && valido != 0; i++) {
           entrada[i] = toupper(entrada[i]);
           if (strrchr(permitidos,  entrada[i]) == NULL) {
               printf(" !! Cadena invalida...... ¡¡\n");
               valido = 0;
            }
    }   
    return valido;
}

#endif