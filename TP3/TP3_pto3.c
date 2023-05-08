#include<stdio.h>
#include<stdlib.h>

//#include"pilas_apuntadores.c"
//#include"pilas_arreglos.c"
//#include"tipo_elemento.c"
#include "pilas.h"
#include "tipo_elemento.h"
#include "Validacion.h"
/*3. Dadas dos pilas, determinar si sus contenidos son exactamente iguales (solo por la
clave), sin destruirlas. Utilizar para la resolución del problema una única pila auxiliar.
Determinar la complejidad algorítmica de la solución.*/
bool compara_pilas(Pila a, Pila b);
Pila carga_por_teclado();

int main(){
    printf("Complejidad algoritmica de orden(5n)-Lineal\n");
    Pila a=p_crear();
    Pila b=p_crear();
    a=carga_por_teclado();
    p_mostrar(a);
    b=carga_por_teclado();
    p_mostrar(b);
    bool cop=compara_pilas(a,b);
    if(cop!=true){
        printf("\n\t\tLas pilas son distintas\n\n");
    }
    else{
        printf("\n\t\tLas pilas son iguales\n\n");
    }
    p_mostrar(a);
    p_mostrar(b);
    return 0;
}
Pila carga_por_teclado(){
    Pila p=p_crear();
    TipoElemento elemento;
    char filtro[100];
    printf("\n¿Cuantos elementos tendra la pila? ");
    fgets(filtro, 100, stdin);
    int longitud=EntradaEntera(filtro,0,0,100);
    if (longitud != 0) {
        for (int i = 0; i < longitud; i++) {
            printf("Clave elemento:");
            fgets(filtro, 100, stdin);
            int clave=EntradaEntera(filtro,0,-1000,1000);
            elemento = te_crear(clave);
            p_apilar(p, elemento);
        }
    }
    return p;
}
bool compara_pilas(Pila a, Pila b){
    int a_i=0;
    int b_i=0;
    Pila c=p_crear();
    bool resultado=false;
    TipoElemento x=malloc(sizeof(TipoElemento));
    int a_clave[100];
    int b_clave[100];
    while(p_es_vacia(a)!=true){
        x=p_desapilar(a);
        a_clave[a_i]=x->clave;
        p_apilar(c,x);
        a_i++;
    }
    while (p_es_vacia(c)!=true){
        x=p_desapilar(c);
        p_apilar(a,x);
    }
    while(p_es_vacia(b)!=true){
        x=p_desapilar(b);
        b_clave[b_i]=x->clave;
        p_apilar(c,x);
        b_i++;
    }
    while (p_es_vacia(c)!=true){
        x=p_desapilar(c);
        p_apilar(b,x);
    }
    if(b_i==a_i){
        resultado=true;
        int i=0;
        while(resultado==true && i<a_i){
            if(a_clave[i]!=b_clave[i]){
                resultado=false;
            }
            i++;
        }
    }
    return resultado;
}

