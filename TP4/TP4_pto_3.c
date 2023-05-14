#include <stdio.h>
#include <stdlib.h>
#include "colas.h"
#include "tipo_elemento.h"
#include "Validacion.h"
#include "colas_punteros.c"
#include "tipo_elemento.c"

/*3. Dadas dos colas, determinar si sus contenidos son iguales tanto en posición como en
datos (solo comparar por la clave), sin destruirlas. Utilizar para la resolución del
problema una sola cola auxiliar. Determinar la complejidad algorítmica del problema.*/
bool compara_colas(Cola a, Cola b);
Cola carga_por_teclado(int* maximoLongitud);
int c_cantidad(Cola cola);

int main(){
    printf("Complejidad algoritmica de O(2n) - Lineal\n");
    
    Cola a=c_crear();
    Cola b=c_crear();
    int longitudTotal = 100;
    int *longitudTotalP = &longitudTotal;
    
    a=carga_por_teclado(longitudTotalP);
    c_mostrar(a);
    b=carga_por_teclado(longitudTotalP);
    c_mostrar(b);
    bool cop=compara_colas(a,b);
    
    printf("\t\t\tRESULTADO\n");
    
    if(cop!=true){
        printf("\t\t>> Las colas son DISTINTAS <<\n");
    }
    else{
        printf("\t\t>> Las colas son IGUALES <<\n");
    }
    
    c_mostrar(a);
    c_mostrar(b);
    return 0;
}

Cola carga_por_teclado(int* maximoLongitud){
    Cola c=c_crear();
    TipoElemento elemento;
    char filtro[100];
    printf("\t\t¿Cuantos elementos tendra la cola? ");
    fgets(filtro, 100, stdin);
    int longitud = EntradaEntera(filtro, 0, 0, *maximoLongitud);
    *maximoLongitud = *maximoLongitud-longitud;
    for (int i = 0; i < longitud; i++) {
        printf("\t\tClave elemento:");
        fgets(filtro, 100, stdin);
        int clave=EntradaEntera(filtro,0,0,1000);
        elemento = te_crear(clave);
        c_encolar(c, elemento);
    }
    return c;
}

bool compara_colas(Cola a, Cola b){
    Cola cAux=c_crear();
    bool resultado = true;

    int aLongitud = c_cantidad(a);
    int bLongitud = c_cantidad(b);

    if(aLongitud != bLongitud) return false;

    TipoElemento aTe;
    TipoElemento bTe;

    while(!c_es_vacia(a)){
        aTe = c_desencolar(a);
        bTe = c_desencolar(b);

        c_encolar(cAux, aTe);
        c_encolar(cAux, bTe);

        if(aTe->clave != bTe->clave) {
            resultado = false;
        }
    }

    while(!c_es_vacia(cAux)){
        c_encolar(a, c_desencolar(cAux));
        c_encolar(b, c_desencolar(cAux));
    }

    return resultado;
}

int c_cantidad (Cola cola) {
    if (c_es_vacia(cola)) return 0;

    TipoElemento aux;
    Cola Caux = c_crear();
    int cont = 0;

    while (!c_es_vacia(cola)) {
        c_encolar(Caux, c_desencolar(cola));
        cont++;
    }

    while (!c_es_vacia(Caux)) {
        c_encolar(cola, c_desencolar(Caux));
    }

    free(Caux);
    return cont;
}