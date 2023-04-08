#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "TP1_Validacion.h"

// Implementación de recursividad - TP Nro. 1 - Punto 6

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

    // caso base
    if(index == cantidadDeChinos){
        printf("%s\n", chinos);
    }else{
        return mostrarChinos(chinos, cantidadDeChinos, index);
    }
}

int main(){
    char filtro[100];
    char *chinos;
    printf(" << Ingrese el nivel de formación de los Chinos: ");
    fgets(filtro, 100, stdin);
    int nivel = EntradaEntera(filtro, 1, 0, 0);
    fflush(stdin);
    printf(" << Vista frontal de la delegación:\n\n");
    mostrarChinos(chinos, nivel, 0);
    return 0;
}
