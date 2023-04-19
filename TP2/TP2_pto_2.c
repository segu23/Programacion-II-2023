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
float Promedio(Lista L, int i, int suma);
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

    printf("!---------------- Ejercicio 2 de Listas ----------------!\n");

    // Leno la lista
    printf(" << Cantidad de valores a ingresar: ");
    fgets(filtro, 100, stdin);
    j= EntradaEntera(filtro, 1, 1, 100);                  // Verifica que la entrada sea un entero natural que este dentro del intervalo [1; 99999]
    fflush(stdin);
    while (i<=j) {
        printf(" << Valor: ");
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
    printf(" << La posicion del dato menor es: %i",DatoMenor(L));
    
    printf("\n");

    //Cantidad del dato mayor
    printf(" << La cantidad de veces que aparece el dato mayor: %i",CantDatoMayor(L));
    
    printf("\n");

    //Promedio de la lista
    Promedio(L, 0, 0);

    printf("\n");

    // Muestro los multiplos de 3 de la lista
    printf(" << Ingrese multiplo: ");
    fgets(filtro, 100, stdin);
    int m= EntradaEntera(filtro, 1, 1, 99999);                  // Verifica que la entrada sea un entero natural que este dentro del intervalo [1; 99999]
    fflush(stdin);
    Lista lm3 = MultiplosDe(L, m);
    printf(" << Los multiplos de %i son: \n",m);
    l_mostrarLista(lm3);

    printf("\n");

    return 0;
};
//---------------------------------------------------------------------------------
// Funciones del Ejercicio 2
//---------------------------------------------------------------------------------

//a. Que calcule el menor de los datos e indique la posición ordinal.  
int DatoMenor(Lista l){
    int dm,pos;
    pos=1;
    TipoElemento X = l_recuperar(l,1);
    dm = X->clave;
    for(int i = 2; i <= l_longitud(l); i++){
        X = l_recuperar(l,i);
        if((int) X->clave < dm){
            dm = X->clave;
            pos = i;
        }
    }
    printf(" << El dato menor es: %i\n", dm);
    return pos;
};

//b. Que calcule el dato máximo y cuente la cantidad de veces que se repite. 
int CantDatoMayor(Lista l){
    int dm,cant;
    cant = 1;
    TipoElemento X = l_recuperar(l,1);
    dm = X->clave;
    for(int i = 2; i <= l_longitud(l); i++){
        X = l_recuperar(l,i);
        if(X->clave >= dm){
            if(dm == X->clave){
                cant++;
            }else{
                dm = X->clave;
                cant = 1;
            }
        }
    }
    printf(" << El dato mayor es: %i\n", dm);
    return cant;
};

//c. Que obtenga el promedio de los datos de una lista. El proceso debe ser recursivo.
float Promedio(Lista L, int i, int suma){
    if (i == l_longitud(L)) {
        if (i == 0) { // verifica si la lista está vacía
            printf("La lista está vacía\n");
            return 0;
        }
        float resultado = (float) suma/i;
        printf(" << Promedio de la Lista: %.2lf\n", resultado);
        return (float) resultado;
    }
    else {
        i++;
        TipoElemento X = l_recuperar(L,i);
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
