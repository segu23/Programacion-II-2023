#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdlib.h>

#include "arbol_binario_punteros.c"
#include "tipo_elemento.c"
#include "nodo.c"
void nodos_arbol(NodoArbol N, NodoArbol aux){
    TipoElemento x;
        x = n_recuperar(N);
        if (n_hijoderecho(aux) != NULL && n_hijoizquierdo(aux) != NULL ){
            {
                printf(" %d", x->clave);
                nodos_arbol(n_hijoizquierdo(N),aux);
                nodos_arbol(n_hijoderecho(N),aux);
            }

        }
        else{
            
        }
    }


void alturaarlbol(NodoArbol Q,  ArbolBinario a, int *n, int acum){
    int aux;
    TipoElemento X;
    if (Q != NULL) {
        X= n_recuperar(Q);
            aux = nivel_nodo(a,X->clave);
           if (aux > acum){
                acum = aux;
                *n = acum;
           }
            alturaarlbol(n_hijoizquierdo(Q), a, n, acum);
            alturaarlbol(n_hijoderecho(Q), a,n, acum);
        }
    }


int alt_arbolaux(ArbolBinario A){
    int n,acum = 0;
    alturaarlbol(a_raiz(A), A,&n, acum);
    return n;
}
void nivelint(NodoArbol Q, int Cbuscada, int *h, int c){
    TipoElemento X;
    if (Q != NULL) {
        X= n_recuperar(Q);
        if (X->clave == Cbuscada) {
            *h = c;
        }
        else{
            nivelint(n_hijoizquierdo(Q), Cbuscada, h, c+1);
            nivelint(n_hijoderecho(Q), Cbuscada, h, c);
        }
    }
}

int nivel_nodo(ArbolBinario A, int N){
    int nivel = -1;
    nivelint(a_raiz(A), N, &nivel, 0);
    return nivel;
}
bool ingresoEntero(int* n){
    char s[10];
    bool resultado = true;
    *n=0;
    printf("Ingrese una clave numérica o '.' para nulo: ");
    scanf("%s", s);
    if (s[0]=='.'){
        resultado = false;
    }else{
        for (int i = 0; s[i] != '\0'; i++) {
            if ((s[i]>='0')&&(s[i]<='9')){
                *n = *n * 10 + (s[i] - 48);}
        }
    }
    return resultado;
}
void Cargar_SubArbol(ArbolBinario A, NodoArbol N, int sa){
    TipoElemento X;
    NodoArbol N1;
    int n;
    bool b;
    if(!a_es_lleno(A)){
        b= ingresoEntero(&n);
        if (b){
            X= te_crear(n);
            
            if(sa == -1) N1 = a_conectar_hi(A, N, X);
            else if(sa == 1) N1 = a_conectar_hd(A, N, X);
            else N1 = a_establecer_raiz(A, X);

            Cargar_SubArbol(A, N1, -1);
            Cargar_SubArbol(A, N1, 1);
        }
    }    
}

void cargar_arbol_binario(ArbolBinario A){
    Cargar_SubArbol(A, NULL, 0);
}

void pre_orden(NodoArbol N){
    TipoElemento x;
    if (N == NULL) {
        printf(".");
    }
    else {
        x = n_recuperar(N);
        printf(" %d", x->clave);
        pre_orden(n_hijoizquierdo(N));
        pre_orden(n_hijoderecho(N));
    }
}
int main(){
    int n, nivel;
    NodoArbol N;
    ArbolBinario A1;
    A1 = a_crear();
    cargar_arbol_binario(A1);
    printf("--------------------------------------------------------\n");
    printf("pre order desde la raiz ");
    pre_orden(a_raiz(A1));
    printf("\nLa altura del arbol es:\n");
    printf("\n%d\n",alt_arbolaux(A1) + 1);
    printf("Ingrese el nodo del que quiere saber el nivel\n");
    scanf("%d",&n);
    nivel = nivel_nodo(A1, n);
    if (nivel == -1){
        printf("La clave no se encuentra en el arbol\n");
    }
    else{
        printf("La clave %d se encuentra en el nivel %d del arbol\n",n,nivel);
    }
    printf("Los nodos internos del arbol son:");
    //no anda
    nodos_arbol(a_raiz(A1),a_raiz(A1));
    system("pause");

}
