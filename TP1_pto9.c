#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

/*
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
    if(numero < 70){
        return numero % 7 == 0 || numero == 0;
    }else{
        int numDerecha = numero%10;
        int resultadoMulti = numDerecha*2;
        numero = numero/10 - resultadoMulti;
        return divisiblePor7(numero);
    }
}

int main(){
    int numero;
    printf("Por favor, escribe el número que quieres comprobar que sea divisible por 7: \n");
    bool valido = false;
    while(!valido) {
        printf("Ingrese un número: ");
        fflush(stdin);
        if(scanf("%d", &numero) == 1 && numero >= 0) {
            valido = true;
        } else {
            printf("Entrada inválida. Intente de nuevo.\n");
        }
    }

    if(divisiblePor7(numero)){
        printf("El número %i SI es divisible por 7.\n", numero);
    }else{
        printf("El número %i NO es divisible por 7.\n", numero);
    }
    return 0;
}
