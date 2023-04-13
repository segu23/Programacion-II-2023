#include <stdio.h>
#include<stdlib.h>
#include"listas.h"
#include"tipo_elemento.h"
#include "Validacion.h"
//---------------------------------------------------
// Encabezados
//---------------------------------------------------
int DatoMenor(Lista l);
int CantDatoMayor(Lista l);
float Promedio(Lista L, int i, float suma);
Lista MultiplosDe(Lista L, int m);
//---------------------------------------------------
// MAIN PRINCIPAL
//---------------------------------------------------
int main(){
    int i = 1;
    int j,h;
    char filtro[100];
    TipoElemento X;
    Lista L = l_crear();

    printf("---------- Ejercicio 2 de Listas ----------------!\n");

    // Leno la lista
    printf("cantidad de valores a ingresar:");
    fgets(filtro, 100, stdin);
    j= EntradaEntera(filtro, 1, 1, 100);                  // Verifica que la entrada sea un entero natural que este dentro del intervalo [1; 99999]
    fflush(stdin);
    while (i<=j) {
        printf("valor:");
        fgets(filtro, 100, stdin);
        h= EntradaEntera(filtro, 1, 1, 99999);                  // Verifica que la entrada sea un entero natural que este dentro del intervalo [1; 99999]
        fflush(stdin);
        i++;
        X = te_crear(h);
        l_agregar(L, X);
    }

    // Muestro la lista
    l_mostrarLista(L);

    //Posision del dato menor
    printf("la posicion del dato menor es: %i",DatoMenor(L));
    
    // Muestro la lista
    printf("\n");
    l_mostrarLista(L);

    //Cantidad del dato mayor
    printf("la cantidad de veses que aparese el dato mayor:%i",CantDatoMayor(L));
    
    // Muestro la lista
    printf("\n");
    l_mostrarLista(L);

    //Promedio de la lista
    float prom = Promedio(L, 0, 0.0);
    printf("Promedio de la Lista: %f \n", prom);

    // Muestro la lista
    printf("\n");
    l_mostrarLista(L);

    // Muestro los multiplos de 3 de la lista
    printf("ingrese multiplo:");
    fgets(filtro, 100, stdin);
    int m= EntradaEntera(filtro, 1, 1, 99999);                  // Verifica que la entrada sea un entero natural que este dentro del intervalo [1; 99999]
    fflush(stdin);
    Lista lm3 = MultiplosDe(L, m);
    printf("Multiplos de %i ..... \n",m);
    l_mostrarLista(lm3);

    // Muestro la lista
    printf("\n");
    l_mostrarLista(L);

    return 0;
};
//---------------------------------------------------------------------------------
// Funciones del Ejercicio 2
//---------------------------------------------------------------------------------

//a. Que calcule el menor de los datos e indique la posición ordinal.  
int DatoMenor(Lista l){
    int dm,pos;
    pos=0;
    TipoElemento x=te_crear(0);
    x=l_recuperar(l,1);
    dm=x->clave;
    for(int i=2;i<l_longitud(l);i++){
        x=l_recuperar(l,i);
        if(dm>x->clave){
            dm=x->clave;
            pos=i;
        }
    }
    return pos;
};

//b. Que calcule el dato máximo y cuente la cantidad de veces que se repite. 
int CantDatoMayor(Lista l){
    int dm,cant;
    cant=1;
    TipoElemento x=te_crear(0);
    x=l_recuperar(l,1);
    dm=x->clave;
    for(int i=2;i<=l_longitud(l);i++){
        x=l_recuperar(l,i);
        if(dm<=x->clave){
            if(dm==x->clave){
                cant++;
            }else{
                dm=x->clave;
                cant=1;
            }
        }
    }
    return cant;
};

//c. Que obtenga el promedio de los datos de una lista. El proceso debe ser recursivo.
float Promedio(Lista L, int i, float suma){
    TipoElemento X = te_crear(0);
    if (i >= l_longitud(L)) {
        return (suma/i);
    }
    else {
        i++;
        X = l_recuperar(L,i);
        suma += X->clave;
        Promedio(L, i, suma);   //Recursividad de cola
    }
};

//d. Que retorne otra lista con los números múltiplos de otro número que recibe como parámetro.
Lista MultiplosDe(Lista l, int m){
    TipoElemento x = te_crear(0);
    Lista lm = l_crear();
    Iterador ite = iterador(l);
    // Ahora la recorro
    while (hay_siguiente(ite)) {
        x = siguiente(ite);
        if ((x->clave % m) == 0) {
            l_agregar(lm, x);
        }
    }
    return lm;
};
