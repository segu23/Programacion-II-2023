/*7. Determinar si dos árboles binarios son equivalentes.*/
#include "arbol_binario.h"
#include "nodo.h"
#include "tipo_elemento.h"

#include <stdio.h>
#include <stdlib.h>
bool Equibool(NodoArbol AB1,NodoArbol AB2){
    bool ret=true;
    TipoElemento x1,x2;
    if ((AB1 != NULL)&&(AB2 != NULL)){
        x1=n_recuperar(AB1);
        x2=n_recuperar(AB2);
        if(x1->clave!=x2->clave){
            ret=false;
            return ret;
        }
        ret=Equibool(n_hijoizquierdo(AB1),n_hijoizquierdo(AB2));
        ret=Equibool(n_hijoderecho(AB1),n_hijoderecho(AB2));
    }else if (((AB1 == NULL)&&(AB2 != NULL))||((AB1 != NULL)&&(AB2 == NULL))){
        ret=false;
        return ret;
        }
    return ret;
}
bool Equi(ArbolBinario a, ArbolBinario b){
    bool x;
    x=Equibool(a_raiz(a),a_raiz(b));
    return x;
}

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
    A=a_crear();
    B=a_crear();
    printf("--------------------Carga primer arbol--------------------\n");
    cargar_arbol_binario(A);
    printf("--------------------Carga segundo arbol--------------------\n");
    cargar_arbol_binario(B);
    if(Equi(A,B)){printf("--------------------LOS ARBOLES SON EQUIVALENTES--------------------\n");}
    else{printf("--------------------LOS ARBOLES NO SON EQUIVALENTES--------------------\n");}
}
