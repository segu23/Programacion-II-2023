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
/*
#include "arbol_binario_punteros.c"
#include "nodo.c"
#include "arboles_utilidades.c"
#include "listas_punteros.c"
*/
#include "tipo_elemento.h"
//#include "tipo_elemento.c"

#include <stdio.h>
#include <stdlib.h>
Lista hojas(ArbolBinario a);
Lista interiores(ArbolBinario a);
Lista BuscarNodos(ArbolBinario a,int b);
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
            else{resultado=2;}
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
        if (b==0){
            X= te_crear(n);
            
            if(sa == -1) N1 = a_conectar_hi(A, N, X);
            else if(sa == 1) N1 = a_conectar_hd(A, N, X);
            else N1 = a_establecer_raiz(A, X);

            Cargar_SubArbol(A, N1, -1);
            Cargar_SubArbol(A, N1, 1);
        }else if(b==2){
            printf("<! Entrada invalida (valor fuera de rango)\n");
            Cargar_SubArbol(A, N,sa);
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
    Lista L;
    char filtro[100];
    L=l_crear();
    A=a_crear();
    printf("--------------------Carga arbol--------------------\n");
    printf(">! Aviso: el ingreso se realiza en pre-orden, para terminar la carga se le tiene que asignar NULL o '.' a todasa las hojas\n");
    cargar_arbol_binario(A);

    printf("\n--------------------Hojas del arbol--------------------\n");
    L=hojas(A);
    l_mostrarLista(L);
    printf("\n// Complejidad algoritmica: se puede considerar que la complejidad es lineal,\n   ya que en cada nodo se realiza una verificación para determinar si es una hoja o no.\n   Por lo tanto, la complejidad algorítmica es O(N), donde N es el número de nodos en el árbol");
    printf("\n// Nota: no se considera la complejidad algoritmica causada por operaciones del TAD.");

    printf("\n--------------------Nodos interiores del arbol--------------------\n");
    L=interiores(A);
    l_mostrarLista(L);
   
    printf("\n// Complejidad algoritmica: también se considera que la complejidad es lineal.\n   En cada nodo, se realiza una verificación para determinar si es un nodo interno (es decir, tiene al menos un hijo o es la raiz) o no.\n   Por lo tanto, la complejidad algorítmica es O(N), donde N es el número de nodos en el árbol.");
    printf("\n// Nota: no se considera la complejidad algoritmica causada por operaciones del TAD.\n");

    printf("\n--------------------Pocision de los nodos con la clave buscada--------------------\n");
    printf("<<Nodo a buscar: ");
    fgets(filtro,100,stdin);
    c=EntradaEntera(filtro,0,0,1000);
    L=BuscarNodos(A,c);
    printf("\n");
    mostrar_pocisiones(L);
    printf("\n// Complejidad algoritmica: la búsqueda de todas las ocurrencias requerirá recorrer todos los nodos del árbol.\n   En el peor caso, si todas las ocurrencias de la clave están presentes en el árbol,\n   se necesitará visitar todos los nodos para encontrarlas todas.\n   Por lo tanto, la complejidad algorítmica para buscar todas las ocurrencias de una clave en un árbol binario completo\n   y retornar la posición de cada ocurrencia es O(N), donde N es el número total de nodos en el árbol.");
    printf("\n// Nota: no se considera la complejidad algoritmica causada por operaciones del TAD.");
}
//Retornar una lista con todos los nodos terminales u hojas.
Lista hojaslista(NodoArbol N,Lista ret){
    TipoElemento x;
    if (N!=NULL){
        if ((n_hijoizquierdo(N)==NULL)&&(n_hijoderecho(N)==NULL)){
            x=n_recuperar(N);
            l_agregar(ret,x);
        }
        hojaslista(n_hijoizquierdo(N),ret);
        hojaslista(n_hijoderecho(N),ret);
    }
    return ret;
}
Lista hojas(ArbolBinario a){
    Lista ret;
    ret=l_crear();
    ret=hojaslista(a_raiz(a),ret);
    return ret;
}

//Retornar en una estructura todos los nodos interiores (los que no son ni hojas ni raíz)
Lista interioreslista(NodoArbol N,int R,Lista Ret){
    TipoElemento X,n;
    if (N!=NULL){
        n=n_recuperar(N);
        if (((n_hijoizquierdo(N)!=NULL)||(n_hijoderecho(N)!=NULL))&&(n->clave!=R)){
            X=n_recuperar(N);
            l_agregar(Ret,X);
        }
        interioreslista(n_hijoizquierdo(N),R,Ret);
        interioreslista(n_hijoderecho(N),R,Ret);
    }
    return Ret;
}
Lista interiores(ArbolBinario a){
    Lista Ret;
    TipoElemento r;
    r=n_recuperar(a_raiz(a));
    Ret=l_crear();
    Ret= interioreslista(a_raiz(a),r->clave,Ret);
    return Ret;
}

//Buscar todas las ocurrencias de una clave dentro del árbol. Retornar la posición de cada ocurrencia (puntero al nodo).
Lista BuscarNodoslista(NodoArbol N,int A,Lista Ret){
    TipoElemento X,n;
    if (N!=NULL){
        n=n_recuperar(N);
        if ((n->clave==A)){
            X=te_crear_con_valor(0,N);
            l_agregar(Ret,X);
        }
        BuscarNodoslista(n_hijoizquierdo(N),A,Ret);
        BuscarNodoslista(n_hijoderecho(N),A,Ret);
    }
    return Ret;
}
Lista BuscarNodos(ArbolBinario a,int b){
    Lista Ret;
    Ret=l_crear();
    Ret=BuscarNodoslista(a_raiz(a),b,Ret);
    return Ret;
}


void mostrar_pocisiones(Lista L){
    Iterador i;
    TipoElemento x;
    i=iterador(L);
    while(hay_siguiente(i)){
        x=siguiente(i);
        printf("pocision: %p\n",x->valor);
    }
}
