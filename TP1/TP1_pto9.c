#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "TP1_Validacion.h"

/*
Implementación de recursividad - TP Nro. 1 - Punto 9

Escribir una función recursiva que implemente el método que se describe para saber si
un número es divisible por 7. Se separa la primera cifra de la derecha, se la multiplica
por 2, y se resta este producto de lo que queda a la izquierda y así sucesivamente,
hasta que el resultado obtenido sea un número menor a 70. El número original será
múltiplo de 7 si el resultado da cero o múltiplo de 7.
Ejemplos:
32291 -> 1x2=2.
3229 - 2 =
3227 -> 7x2=14.
322 - 14 =
308 -> 8x2=16
30 - 16 =
14 -> Múltiplo de 7
divisiblePor7 (32291) => verdadero
110 -> 0 x 2 = 0
11 – 0 =
11 -> No múltiplo de 7
divisiblePor7 (110) => falso 
*/

bool divisiblePor7(int numero){
    // caso base
    if(numero < 70){
        return numero % 7 == 0 || numero == 0;
    }else{
        // se obtiene el numero a la derecha de todo utilizando el resto de la división por 10
        int numDerecha = numero%10;
        // se multiplica el numero obtenido por 2
        int resultadoMulti = numDerecha*2;
        // se obtiene todo el numero excepto el digito de la derecha y se le resta el resultado de la multiplicación anterior
        numero = numero/10 - resultadoMulti;
        // se vuelve a realizar el procedimiento con el numero obtenido
        return divisiblePor7(numero);
    }
}

int main(){
    char filtro[100];
    printf("\n << Ingrese el número que quieres comprobar que sea divisible por 7: ");
    fgets(filtro, 100, stdin);
    int numero = EntradaEntera(filtro, 0, 0, 0);
    fflush(stdin);
    if(divisiblePor7(numero)){
        printf(" << El número %i SI es divisible por 7.\n", numero);
    }else{
        printf(" << El número %i NO es divisible por 7.\n", numero);
    }
    return 0;
}

