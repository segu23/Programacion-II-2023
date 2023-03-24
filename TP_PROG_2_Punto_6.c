#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void mostrarChinos(char * chinos, int cantidadDeChinos, int index){
    int cantidadDeCaracteres = (cantidadDeChinos*6)-1;
    if(index == 0){
        chinos = malloc(sizeof(char)*(cantidadDeCaracteres+1));
        for (int i = 0; i < cantidadDeCaracteres; i++) {
            chinos[i] = ' ';
        }
        chinos[cantidadDeCaracteres] = '\0';
    }
    
    int baseIzquierda = ((cantidadDeCaracteres+1)/2)-3*index-1;
    int baseDerecha = ((cantidadDeCaracteres+1)/2)+3*index-1;

    chinos[baseIzquierda] = '.';
    chinos[baseIzquierda-1] = '-';
    chinos[baseIzquierda-2] = '(';
    chinos[baseDerecha] = '.';
    chinos[baseDerecha+1] = '-';
    chinos[baseDerecha+2] = ')';
    index++;


    if(index == cantidadDeChinos){
        printf("%s\n", chinos);
    }else{
        return mostrarChinos(chinos, cantidadDeChinos, index);
    }
}

int main(){
    char *chinos;
    int numero;
    printf("Por favor, escribe el nivel de formación de los Chinos: \n");
    bool valido = false;
    while(!valido) {
        printf("Ingrese un número: ");
        fflush(stdin);
        if(scanf("%d", &numero) == 1 && numero > 0) {
            valido = true;
        } else {
            printf("Entrada inválida. Intente de nuevo.\n");
        }
    }
    mostrarChinos(chinos, numero, 0);
    return 0;
}