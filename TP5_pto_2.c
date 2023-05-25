/*2. Dado un árbol binario no vacío determinar:
a. Retornar una lista con todos los nodos terminales u hojas.
b. Retornar en una estructura todos los nodos interiores (los que no son ni hojas
ni raíz)
c. Buscar todas las ocurrencias de una clave dentro del árbol. Retornar la
posición de cada ocurrencia (puntero al nodo).
d. Determinar la complejidad algorítmica de los puntos “a”, “b”, “c”.*/

#include "arbol_binario.h"
#include "nodo.h"
#include "arboles_utilidades.h"
#include "listas.h"
#include "Validacion.h"
#include <stdio.h>
#include <stdlib.h>
Lista hojas(ArbolBinario a);
Lista interiores(ArbolBinario a);
Lista BuscarNodos(ArbolBinario a,NodoArbol n);
void mostrar_pocisiones(Lista L);

/*Función que solicita el ingreso de un número entero o de "." como representación de nulo. La misma 
devuelve verdadero en el primer caso y falso en el segundo.*/
int ingresoEntero(int* n){
    char s[10];
    int resultado =0;
    *n=0;
    printf("Ingrese una clave numérica o '.' para nulo: ");
    scanf("%s", s);
    if (s[0]=='.'){
        resultado = 1;
    }else{
        for (int i = 0; s[i] != '\0'; i++) {
            if ((s[i]>='0')&&(s[i]<='9')){
                *n = *n * 10 + (s[i] - 48);}
            else{
                resultado=2;
            }
        }
    }
    return resultado;
}

/*Función que carga un (sub)árbol en preorden a partir del nodo padre N recursivamente.
El entero sa indica cómo se enlazará el nuevo valor:
0: El nuevo nodo (con su TE) se asignará a la raíz de A. En este caso N no es utilizado.
-1: El nuevo nodo (con su TE) se enlazará como hijo izquierdo de N.
1: El nuevo nodo (con su TE) se enlazará como hijo derecho de N.*/
void Cargar_SubArbol(ArbolBinario A, NodoArbol N, int sa){
    TipoElemento X;
    NodoArbol N1;
    int n;
    int b;
    if(!a_es_lleno(A)){
        b= ingresoEntero(&n);
        if (b=0){
            X= te_crear(n);
            
            if(sa == -1) N1 = a_conectar_hi(A, N, X);
            else if(sa == 1) N1 = a_conectar_hd(A, N, X);
            else N1 = a_establecer_raiz(A, X);

            Cargar_SubArbol(A, N1, -1);
            Cargar_SubArbol(A, N1, 1);
        }else{
            printf("valor no valido\n");
        }
    }    
}

/*Función que recibe el árbol a ser cargado y llama a la función recursiva que realiza
la carga nodo por nodo*/
void cargar_arbol_binario(ArbolBinario A){
    Cargar_SubArbol(A, NULL, 0);
}
void main(){
    ArbolBinario A,B;
    NodoArbol n;
    int c;
    TipoElemento x;
    Lista L;
    char filtro[100];
    L=l_crear();
    A=a_crear();
    printf("--------------------Carga arbol--------------------\n");
    cargar_arbol_binario(A);
    printf("--------------------Hojas del arbol--------------------\n");
    L=hojas(A);
    l_mostrarLista(L);
    printf("--------------------Nodos interiores del arbol--------------------\n");
    L=interiores(A);
    l_mostrarLista(L);
    printf("nodo a buscar:");
    c=EntradaEntera(filtro,0,-100,100);
    x=te_crear(c);
    n=n_crear(x);
    printf("--------------------Pocision de los nodos con la clave buscada--------------------\n");
    L=BuscarNodos(A,n);   
    mostrar_pocisiones(L);
}
//Retornar una lista con todos los nodos terminales u hojas.
Lista hojaslista(NodoArbol N){
    Lista ret;
    TipoElemento x;
    ret=l_crear();
    if (N!=NULL){
        if ((n_hijoizquierdo(N)==NULL)&&(n_hijoderecho(N)==NULL)){
            x=n_recuperar(N);
            l_agregar(ret,x);
        }else{
            hojaslista(n_hijoizquierdo(N));
            hojaslista(n_hijoderecho(N));
        }
    }
    return ret;
}
Lista hojas(ArbolBinario a){
    Lista ret;
    hojaslista(a_raiz(a));
    return ret;
}

//Retornar en una estructura todos los nodos interiores (los que no son ni hojas ni raíz)
Lista interioreslista(NodoArbol N,NodoArbol R){
    Lista Ret;
    TipoElemento X;
    Ret=l_crear();
    if (N!=NULL){
        if ((n_hijoizquierdo(N)!=NULL)&&(n_hijoderecho(N)!=NULL)&&(N!=R)){
            X=n_recuperar(N);
            l_agregar(Ret,X);
        }else{
            interioreslista(n_hijoizquierdo(N),R);
            interioreslista(n_hijoderecho(N),R);
        }
    }
    return Ret;
}
Lista interiores(ArbolBinario a){
    Lista Ret;
    Ret=l_crear();
    Ret= interioreslista(a_raiz(a),a_raiz(a));
    return Ret;
}

//Buscar todas las ocurrencias de una clave dentro del árbol. Retornar la posición de cada ocurrencia (puntero al nodo).
Lista BuscarNodoslista(NodoArbol N, NodoArbol A){
    Lista Ret;
    TipoElemento X;
    int i=0;
    Ret=l_crear();
    if (N!=NULL){
        if ((N==A)){//cambiar
            X=te_crear_con_valor(i,N);//cambiar
            l_agregar(Ret,X);//cambiar
            i++;
        }else{
            BuscarNodoslista(n_hijoizquierdo(N),A);
            BuscarNodoslista(n_hijoderecho(N),A);
        }
    }
    return Ret;
}
Lista BuscarNodos(ArbolBinario a,NodoArbol n){
    Lista Ret;
    Ret=l_crear();
    Ret=BuscarNodoslista(a_raiz(a),n);
    return Ret;
}


void mostrar_pocisiones(Lista L){
    Iterador i;
    TipoElemento x;
    i=iterador(L);
    while(hay_siguiente(i)){
        x=siguiente(i);
        printf("pocision:%p\n",x->valor);
    }
}
