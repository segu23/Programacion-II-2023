#include <stdlib.h>
#include "pilas.h"
#include "tipo_elemento.h"
#include "Validacion.h"

#define MAX 100

/*
Dada una pila con valores al azar eliminar todas las ocurrencias de un determinado
ítem sin perder la pila original. Deberá retornar una nueva pila sin el ítem en
consideración. Resolver iterativamente y recursivamente. Determinar la complejidad
algorítmica de ambas soluciones.
Ejemplo: si “P” contiene (1, 5, 7, 1, 3, 1, 8) y el ítem a eliminar es “1” entonces la pila
resultante sería (5, 7, 3, 8).
*/

/**
 * Funcion que permite eliminar de manera iterativa todos los elementos de una pila
 * que coincidan con la clave ingresada por parametro
 * La complejidad de este algoritmo es de O(2n)
 * 
 * @param pila Pila a procesar
 * @param clave Clave a eliminar de la pila
 * @return Pila Pila que resulta de la eliminación de los elementos con la clave
 */
Pila eliminarOcurrenciasIterativamente(Pila pila, int clave){
    Pila resultado = p_crear();
    Pila aux = p_crear();
    while(!p_es_vacia(pila)){
        TipoElemento te = p_desapilar(pila);
        if(te->clave != clave) p_apilar(resultado, te);
        p_apilar(aux, te);
    }
    while(!p_es_vacia(aux)){
        p_apilar(pila, p_desapilar(aux));
    }

    return resultado;
}

/**
 * Funcion que permite eliminar de manera iterativa todos los elementos de una pila
 * que coincidan con la clave ingresada por parametro
 * La complejidad de este algoritmo es de O(2n)
 * 
 * @param pila Pila a procesar
 * @param clave Clave a eliminar de la pila
 * @param aux Pila auxiliar que permite no perder los datos de la pila original
 * @param resultado Pila que irá acumulando la pila final
 * @param iteracion Parametro acumulador que indica la iteración actual
 * @return Pila Pila que resulta de la eliminación de los elementos con la clave
 */
Pila eliminarOcurrenciasRecursivamente(Pila pila, int clave, Pila aux, Pila resultado, int iteracion, int longitud){
    if(iteracion == longitud){
        while(!p_es_vacia(aux)){
            p_apilar(pila, p_desapilar(aux));
        }
        return resultado;
    }else{
        TipoElemento te = p_desapilar(pila);
        if(te->clave != clave) p_apilar(resultado, te);
        p_apilar(aux, te);
        return eliminarOcurrenciasRecursivamente(pila, clave, aux, resultado, iteracion+1, longitud);
    }
}

Pila p_invertir (Pila pila) {
    if (p_es_vacia(pila)) return pila;

    Pila Paux = p_crear();
    Pila Pinv = p_crear();
    TipoElemento aux;

    while (!p_es_vacia(pila)) {
        aux = p_desapilar(pila);

        p_apilar(Paux, aux);
        p_apilar(Pinv, aux);
    }

    while (!p_es_vacia(Paux)) {
        p_apilar(pila, p_desapilar(Paux));
    }

    free(Paux);
    return Pinv;
}

int main(){
    Pila pila = p_crear();
    char filtro[100];
    system("cls");
    printf("<< Ingrese la longitud de la pila [1; 100]: ");
    fgets(filtro, MAX, stdin);
    int longitud = EntradaEntera(filtro, 0, 1, MAX);

    for(int i = 0; i < longitud; i++){
        printf("\n\n << Ingrese un número: ");
        fgets(filtro, MAX, stdin);
        p_apilar(pila, te_crear(EntradaEntera(filtro, 0, -1000, 1000)));
    }

    p_mostrar(pila);
    
    printf("\n\n << Ingrese el número a eliminar: ");
    fgets(filtro, MAX, stdin);
    int numeroObjetivo = EntradaEntera(filtro, 0, 0, 0);

    printf("\n\n << Ingrese la modalidad a utilizar: ");
    printf("\n   << RECURSIVAMENTE (1) La complejidad de este algoritmo es de O(2n)");
    printf("\n   << ITERATIVAMENTE (2) La complejidad de este algoritmo es de O(2n)\n");
    fgets(filtro, MAX, stdin);
    int modalidad = EntradaEntera(filtro, 0, 1, 2);

    printf("\n");
    Pila resultado;
    if(modalidad){
        resultado = eliminarOcurrenciasRecursivamente(pila, numeroObjetivo, p_crear(), p_crear(), 0, longitud);
    }else{
        resultado = p_invertir(eliminarOcurrenciasIterativamente(pila, 1));
    }
    printf("\n >> Resultado\n");
    p_mostrar(resultado);
}
