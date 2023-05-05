#include<stdio.h>
#include<stdlib.h>

#include"colas.c"
#include"tipo_elemento.c"
#include"Validacion.h"
/*3. Dadas dos colas, determinar si sus contenidos son iguales tanto en posición como en
datos (solo comparar por la clave), sin destruirlas. Utilizar para la resolución del
problema una sola cola auxiliar. Determinar la complejidad algorítmica del problema.*/
bool compara_colas(Cola a, Cola b);
Cola carga_por_teclado();

int main(){
    printf("complejodad algotirmica de orden(n)-Lineal\n");
    Cola a=c_crear();
    Cola b=c_crear();
    a=carga_por_teclado();
    c_mostrar(a);
    b=carga_por_teclado();
    c_mostrar(b);
    bool cop=compara_colas(a,b);
    if(cop!=true){
        printf("\t\tlas colas son distintas\n");
    }
    else{
        printf("\t\tlas colas son iguales\n");
    }
    c_mostrar(a);
    c_mostrar(b);
    return 0;
}
Cola carga_por_teclado(){
    Cola c=c_crear();
    TipoElemento elemento;
    char filtro[100];
    printf("\t\t¿Cuantos elementos tendra la cola? ");
    fgets(filtro, 100, stdin);
    int longitud=EntradaEntera(filtro,0,0,100);
    if (longitud != 0) {
        for (int i = 0; i < longitud; i++) {
            printf("\t\tClave elemento:");
            fgets(filtro, 100, stdin);
            int clave=EntradaEntera(filtro,0,0,1000);
            elemento = te_crear(clave);
            c_encolar(c, elemento);
        }
    }
    return c;
}
bool compara_colas(Cola a, Cola b){
    int a_i=0;
    int b_i=0;
    Cola c=c_crear();
    bool resultado=false;
    TipoElemento x=malloc(sizeof(TipoElemento));
    int a_clave[100];
    int b_clave[100];
    while(c_es_vacia(a)!=true){
        x=c_desencolar(a);
        a_clave[a_i]=x->clave;
        c_encolar(c,x);
        a_i++;
    }
    while (c_es_vacia(c)!=true){
        x=c_desencolar(c);
        c_encolar(a,x);
    }
    while(c_es_vacia(b)!=true){
        x=c_desencolar(b);
        b_clave[b_i]=x->clave;
        c_encolar(c,x);
        b_i++;
    }
    while (c_es_vacia(c)!=true){
        x=c_desencolar(c);
        c_encolar(b,x);
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