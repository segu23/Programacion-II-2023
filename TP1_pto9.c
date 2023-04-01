#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

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

