#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "Validacion.h"

#include "listas_arreglos.c"
#include "tipo_elemento.c"

void mostrar_funcion(Lista funcion){
    Iterador iter = iterador(funcion);
    TipoElemento coeficiente;
    printf("f(x) = ");
    while(hay_siguiente(iter)){
        coeficiente = siguiente(iter);
        if(coeficiente->clave == funcion->cantidad-1 && (int) coeficiente->valor < 0){
            printf("-");
        }else if(coeficiente->clave < funcion->cantidad-1){
            if((int) coeficiente->valor > 0){
                printf("+ ");
            }else if((int) coeficiente->valor < 0){
                printf("- ");
            }
        }
        if(coeficiente->valor > 0){
            if((int) coeficiente->valor > 1 || coeficiente->clave == 0){
                printf("%i", abs((int) coeficiente->valor));
            }
        }else{
            continue;
        }
        if(coeficiente->clave > 0){
            printf("x");
        }
        if(coeficiente->clave > 1){
            printf("^%i", coeficiente->clave);
        }
        printf(" ");
    }
}

void calcular_funcion(Lista funcion, double x){
    printf("f(%.1f) = ", x);
    double total = 0;

    Iterador iter = iterador(funcion);
    TipoElemento coeficiente;
    while(hay_siguiente(iter)){
        coeficiente = siguiente(iter);
        total += ((int) coeficiente->valor) * pow(x, coeficiente->clave);
    }
    printf("%.2f\n", total);
}

void calcular_funcion_en_intervalo(Lista funcion, int comienzoIntervalo, int finIntervalo){
    double x = comienzoIntervalo;
    while(x <= finIntervalo){
        calcular_funcion(funcion, x);
        x += 0.5;
    }
}

int main(){
    char filtro[100];
    Lista funcion = l_crear();
    printf(" << Ingrese el grado de la función: ");
    fgets(filtro, 100, stdin);
    int grado = EntradaEntera(filtro, 0, 0, 0);
    fflush(stdin);

    for(int i = grado; i >= 0; i--){
        TipoElemento coeficiente;
        if(i == 0){
            printf(" << Ingrese el termino independiente de la función: ");
        }else{
            printf(" << Ingrese el coeficiente de x para x^%i: ", i);
        }
        fgets(filtro, 100, stdin);
        int coeficiente_ingresado[1];
        coeficiente_ingresado[0] = EntradaEntera(filtro, 0, 0, 0);
        fflush(stdin);
        coeficiente = te_crear_con_valor(i, (void *) coeficiente_ingresado[0]);
        l_agregar(funcion, coeficiente);
    }

    printf("\n");

    mostrar_funcion(funcion);

    printf("\n\n");

    printf(" << Ingrese el comienzo del intervalo a calcular: ");
    fgets(filtro, 100, stdin);
    int comienzoIntervalo = EntradaEntera(filtro, 0, 0, 0);
    fflush(stdin);
    printf(" << Ingrese el fin del intervalo a calcular: ");
    fgets(filtro, 100, stdin);
    int finIntervalo = EntradaEntera(filtro, 0, comienzoIntervalo, 9999999);
    fflush(stdin);

    calcular_funcion_en_intervalo(funcion, comienzoIntervalo, finIntervalo);

    return 0;
}