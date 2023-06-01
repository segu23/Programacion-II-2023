#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdlib.h>

#include "arbol_binario.h"
#include "tipo_elemento.h"
#include "nodo.h"
#include "Validacion.h"

void nodos_arbol(NodoArbol N, bool *NoHay){
    TipoElemento x;
    
        x = n_recuperar(N);
        if (n_hijoizquierdo(N) != NULL ){
            {
                *NoHay = false;
                printf(" %d", x->clave);
                nodos_arbol(n_hijoizquierdo(N), NoHay);
                if (n_hijoderecho(N) != NULL ){
                    nodos_arbol(n_hijoderecho(N), NoHay);
                }
            }

        }else if (n_hijoderecho(N) != NULL ){
                    nodos_arbol(n_hijoderecho(N), NoHay);
                }
        
    }

void Nodos_Internos(ArbolBinario(A)){
    bool NoHay = true;
    printf("Nodos internos del arbol:\n");
    nodos_arbol((n_hijoizquierdo(a_raiz(A))), &NoHay);
    if(NoHay){printf("No hay nodos internos\n");}
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
    if(a_es_vacio(A)){
        return -1;
    }else if(a_cantidad_elementos(A) == 1){
        return 0;
    }else{
        alturaarlbol(a_raiz(A), A,&n, acum);
        return n;
    }
}

bool Hojas(NodoArbol N, ArbolBinario A, int *Nivel){ 
    
    if (n_hijoderecho(N) != NULL){
        if (Hojas(n_hijoderecho(N), A, Nivel) == false){
            return false;
        }
    }
    if (n_hijoizquierdo(N) == NULL){
        if (*Nivel == 0){
            *Nivel = nivel_nodo(A , (n_recuperar(N))->clave);
        }else{
            if (nivel_nodo(A , (n_recuperar(N))->clave) != *Nivel){
                return false;
            }
        }

    }else {
        if (Hojas(n_hijoizquierdo(N), A, Nivel) == false){
            return false;
        }  
    }
    return true;
}


bool NivelHojas(ArbolBinario A){
    int Nivel = 0;
    return Hojas(a_raiz(A), A, &Nivel);
 }


bool ingresoEntero(int* n, bool *letra){
    char s[10];
    *letra = false;
    bool resultado = true;
    *n=0;
    printf("Ingrese una clave numerica o '.' para nulo: ");
    scanf("%s", s);
    fflush(stdin);
    if (s[0]=='.'){
        resultado = false;
    }else{
        for (int i = 0; s[i] != '\0'; i++) {
            if ((s[i]>='0')&&(s[i]<='9')){
                *n = *n * 10 + (s[i] - 48);
            }else{*letra = true;}
        }
    }
    return resultado;
}

bool ComprobarRepetidos(ArbolBinario A, NodoArbol N, int n){
    bool b = false;
    if(!a_es_vacio(A) ){
        if(n_recuperar(N)->clave == n){
            b = true;
            return b;
        }else{
            if(n_hijoderecho(N) != NULL){b = ComprobarRepetidos(A,n_hijoderecho(N), n);}
            if(b == false){    
                if(n_hijoizquierdo(N) != NULL){b = ComprobarRepetidos(A,n_hijoizquierdo(N), n);}
            }
            return b;
        }
    }
}

void Cargar_SubArbol(ArbolBinario A, NodoArbol N, int sa){
    TipoElemento X;
    NodoArbol N1;
    int n;
    bool b, letra;
    letra = false;
    if(!a_es_lleno(A)){
        b= ingresoEntero(&n, &letra);
        while((ComprobarRepetidos(A ,a_raiz(A), n) && b) || letra ){
            if (letra){
                printf("Valor invalido, ingrese un numero.\n");
            }else{printf("El valor ingresado ya se encuentra en el arbol, ingrese otro.\n");}
            b= ingresoEntero(&n, &letra);
        }

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

//Funcion para la carga del arbol
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
    int n, nivel, altura;
    char filtro[100];
    NodoArbol N;
    ArbolBinario A1;
    TipoElemento X;
    
    system("cls");
    A1 = a_crear();
    cargar_arbol_binario(A1);
    
    if(a_es_vacio(A1)){
        printf("\nEl arbol esta vacio\n");    
    }else{
        printf("--------------------------------------------------------\n");
        printf("pre order desde la raiz ");
        pre_orden(a_raiz(A1));
        
        altura = alt_arbolaux(A1);
        if(altura == -1){
            printf("\nEl arbol esta vacio\n");    
        }else{
            printf("\nLa altura del arbol es: %d\n", altura + 1);
        }
        printf("Ingrese el nodo del que quiere saber el nivel\n");
        fgets(filtro, 100, stdin);
        n = EntradaEntera(filtro, 0, 0, 0);
        nivel = nivel_nodo(A1, n);
        if (nivel == -1){
            printf("La clave no se encuentra en el arbol\n");
        }
        else{
            printf("La clave %d se encuentra en el nivel %d del arbol\n",n,nivel);
        }
        
        
        Nodos_Internos(A1);
        printf("\n");

        if(a_es_vacio(A1)|| a_cantidad_elementos(A1) == 1){
            printf("No hay hojas, el arbol solo tiene raiz\n");
        }else{  
            if(NivelHojas(A1)){
                printf("Todas las hojas estan al mismo nivel\n");
            }else{
                printf("Las hojas no estan al mismo nivel\n");
            }
        }
    }
    system("pause");
}
