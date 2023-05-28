#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbol_binario.h"
#include "Listas_Arreglos.c"
#include "colas_punteros.c"
#include "tipo_elemento.h"
#include "Validacion.h"
//Item A
Lista AnchuraEneario(ArbolBinario A){ 
    Lista Rsta;
    Cola C;
    TipoElemento X, XD;
    NodoArbol N;
    Rsta = l_crear();
    C = c_crear();
    if(!a_es_vacio(A)){
        N = a_raiz(A);
        X= te_crear_con_valor((n_recuperar(N))->clave ,N);
        c_encolar(C, X);
        while(!c_es_vacia(C)){
            X = c_desencolar(C);
            N = (NodoArbol) X->valor;
            l_agregar(Rsta,X);
            if(!a_es_rama_nula(n_hijoizquierdo(N))){
                X = te_crear_con_valor((n_recuperar(n_hijoizquierdo(N)))->clave ,n_hijoizquierdo(N));
                c_encolar(C, X);
            }
            while(!a_es_rama_nula(n_hijoderecho(N))){
                XD = te_crear_con_valor((n_recuperar(n_hijoderecho(N)))->clave ,n_hijoderecho(N));
                l_agregar(Rsta,XD);
                if(!a_es_rama_nula(n_hijoizquierdo((NodoArbol) XD->valor))){
                    X = te_crear_con_valor((n_recuperar(n_hijoizquierdo((NodoArbol) XD->valor)))->clave ,n_hijoizquierdo((NodoArbol) XD->valor));
                    c_encolar(C,X); 
                }
                N = (NodoArbol) XD->valor;
            }
        }
    }
    return Rsta;
}    

//Item B
void Hojas(NodoArbol N, int *h){ 
    if (n_hijoderecho(N) != NULL){
        Hojas(n_hijoderecho(N),h);
    }
    if (n_hijoizquierdo(N) == NULL){
        *h = *h + 1;
    }else {
        Hojas(n_hijoizquierdo(N),h); 
    }
}
int B_CantHojas(ArbolBinario A){
    int hojas = 0;
    if(!a_es_vacio(A) && a_cantidad_elementos(A) > 1){
        Hojas(a_raiz(A), &hojas);
    }
    return hojas;
}


 //Item C
void Comparar(NodoArbol N, NodoArbol N2, bool *Resultado){
    if(n_hijoderecho(N) != NULL && n_hijoderecho(N2) != NULL){
        Comparar(n_hijoderecho(N),n_hijoderecho(N2), Resultado);
    }else if((n_hijoderecho(N) == NULL && n_hijoderecho(N2) != NULL)||(n_hijoderecho(N) != NULL && n_hijoderecho(N2) == NULL)){
        *Resultado = false;
    }

    if(n_hijoizquierdo(N) != NULL && n_hijoizquierdo(N2) != NULL){
        Comparar(n_hijoizquierdo(N),n_hijoizquierdo(N2), Resultado);
    }else if((n_hijoizquierdo(N) == NULL && n_hijoizquierdo(N2) != NULL)||(n_hijoizquierdo(N) != NULL && n_hijoizquierdo(N2) == NULL)){
        *Resultado = false;
    }
}
bool CompararEstructura(ArbolBinario A, ArbolBinario A2){
    bool Resultado = true;
    NodoArbol N, N2;
    N = a_raiz(A);
    N2 = a_raiz(A2);

    Comparar(N, N2, &Resultado);

    return Resultado;
}


//Item D
int BusquedaPadre(int Padre, NodoArbol N, int ValorABuscar, int *Encontro){ 
    int respuesta;
    TipoElemento X;
    X = n_recuperar(N);
    if(X->clave == ValorABuscar){
        *Encontro = 1;
        return Padre;
    }else{
        if(n_hijoderecho(N) != NULL){
            respuesta = BusquedaPadre(Padre, n_hijoderecho(N),ValorABuscar, Encontro);
            if (*Encontro == 1){
                return respuesta;
            }
        }
        if(n_hijoizquierdo(N) != NULL){
            X = n_recuperar(N); 
            Padre = X->clave;
            respuesta = BusquedaPadre(Padre, n_hijoizquierdo(N),ValorABuscar, Encontro);
            if (*Encontro == 1){
                return respuesta;
            }  
        }   
    }

}
TipoElemento D_Padre(ArbolBinario A, int ValorABuscar){                         
    TipoElemento Padre;
    int Encontro = 0;
    if (a_cantidad_elementos(A) == 1 || a_es_vacio(A)){
        return NULL;
    }else{
        Padre = n_recuperar(a_raiz(A));
        Encontro = BusquedaPadre(Padre->clave, a_raiz(A), ValorABuscar, &Encontro);
        if (Encontro == 0){
            return NULL;
        }else{
            Padre = te_crear(Encontro);
            return Padre;
        }
    }
}


//Item E
void BuscarHermanos(NodoArbol N, Lista *Her, int H, int *Termino){
    int i;
    if(n_hijoderecho(N) != NULL){
        if(n_recuperar(N)->clave == H){
            *Termino = 1;   
            BuscarHermanos(n_hijoderecho(N),Her,H , Termino);
        }else{
            l_agregar(*Her, n_recuperar(N));
            BuscarHermanos(n_hijoderecho(N),Her,H , Termino);
        }
    }else if(n_recuperar(N)->clave == H){
            *Termino = 1; 
        }else{l_agregar(*Her, n_recuperar(N));}
       
    if(*Termino == 1){
        return;
    }
    if(n_hijoizquierdo(N) != NULL){
        i = l_longitud(*Her);
        while (!l_es_vacia(*Her))
        {
            l_eliminar(*Her,i);
            i--;
        }
        BuscarHermanos(n_hijoizquierdo(N),Her,H , Termino);    
    }
}
Lista Hermanos(ArbolBinario A, int H){
    int Termino = 0;
    TipoElemento X;
    Lista Her;
    Her = l_crear();
    NodoArbol N;
    N = a_raiz(A);
    BuscarHermanos(N, &Her, H, &Termino);

    return Her;    
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

void main(){
    ArbolBinario A, A2;
    TipoElemento X;
    NodoArbol N;
    Lista Pto_E;

    char tecla;
    bool menu = true;
    char filtro[100];
    int i, BusquedaPuntoD, BusquedaHermanoE;
    int Valor;
   
    printf("Cargue de arbol n-ario representado como binario utilizando la transformacion de Knuth(El arbol se carga en pre-Orden):\n");
    A= a_crear();
    cargar_arbol_binario(A);
    fflush(stdin);
    

    system("cls");

    while(menu){
        printf("El arbol ingresado es Mostrado (en Pre-Orden):\n");
        pre_orden(a_raiz(A)); 

        printf("     \n~~~~~~~~~~~~~~~~~~~~~~~MENU~~~~~~~~~~~~~~~~~~~~~~~     \n");  
        printf("1- A) Mostrar anchura del arbol\n");
        printf("2- B) Mosrar cantidad de hojas del arbol\n");
        printf("3- C) Comparar estructura de arboles\n");
        printf("4- D) Buscar padre de un nodo\n");
        printf("5- E) Buscar hermanos de un nodo\n");
        printf("0- SALIR\n");

        printf("Presione un nuero para elejir una opcion\n");
            scanf("%c", &tecla);
            fflush(stdin);
        if(tecla >= '0' && tecla <= '5'){
            if(tecla == '1'){
                system("cls");
                printf("El arbol ingresado es Mostrado (en Pre-Orden):\n");
                pre_orden(a_raiz(A));
                if(!l_es_vacia(AnchuraEneario(A))){
                    printf("\nLa anchura del arbol es:\n");
                    l_mostrarLista(AnchuraEneario(A));
                    printf("presione enter para volver al menu\n");
                    scanf("%c", &tecla);
                    fflush(stdin);
                }else{
                    printf("\nEl arbol esta vacio\n");
                    printf("presione enter para volver al menu\n");
                    scanf("%c", &tecla);
                    fflush(stdin);
                }
            }else if(tecla == '2'){
                system("cls");
                printf("El arbol ingresado es Mostrado (en Pre-Orden):\n");
                pre_orden(a_raiz(A));
                if(B_CantHojas(A) != 0){
                    printf("\nEl arbol tiene %d hojas\n",B_CantHojas(A));
                }else{printf("\nEl arbol solo tiene Raiz o esta vacio\n");}
                
                printf("Presione enter para volver al menu\n");
                scanf("%c", &tecla);

            }else if(tecla == '3'){
                system("cls");
                printf("Cargue un segudo arbol n-ario para compararlo con el primero:\n");
                A2= a_crear();
                cargar_arbol_binario(A2);
                fflush(stdin);

                system("cls");
                printf("Arbol Principal Mostrado en Pre-Orden:\n");
                pre_orden(a_raiz(A));

                printf("\nArbol 2 Mostrado en Pre-Orden:\n");
                pre_orden(a_raiz(A2)); 

                if(CompararEstructura(A,A2)){
                    printf("\nLa estructura de los aboles es igual\n");
                }else{printf("\nLos arboles no tienen la misma estructura\n");}
                printf("Presione enter para volver al menu\n");
                scanf("%c", &tecla);
            
            }else if(tecla == '4'){
                system("cls");
                printf("El arbol ingresado es Mostrado (en Pre-Orden):\n");
                pre_orden(a_raiz(A));
                
                if(a_es_vacio(A)){ printf("\nEl arbol esta vacio\n");}else{
                    printf("\nIngrese el nodo para buscar a su padre:\n");
                    fgets(filtro, 100, stdin);
                    BusquedaPuntoD = EntradaEntera(filtro, 0, 0, 0);
                    X = D_Padre(A, BusquedaPuntoD);
                    if(X == NULL){
                        printf("No se encontro el nodo solicitado en el arbol o el nodo solicitado es la Raiz(No tiene padre)\n");
                    }else if(X->clave == BusquedaPuntoD){
                        printf("El nodo ingresado es la Raiz\n");
                    }else{printf("El Padre del nodo ingresado es %d \n", X->clave);}
                }
                printf("Presione enter para volver al menu\n");
                scanf("%c", &tecla);

            }else if(tecla == '5'){
                system("cls");
                printf("El arbol ingresado es Mostrado (en Pre-Orden):\n");
                pre_orden(a_raiz(A));

                if(a_es_vacio(A)){ printf("\nEl arbol esta vacio\n");}else{

                    printf("\nIngrese el nodo para buscar sus hermanos:\n");
                    fgets(filtro, 100, stdin);
                    BusquedaHermanoE = EntradaEntera(filtro, 0, 0, 0);
                    
                    Pto_E = Hermanos(A, BusquedaHermanoE);
                    if(l_es_vacia(Pto_E)){
                        printf("El nodo no tiene hermanos o es la raiz\n");
                    }else{
                        printf("La lista de los hermanos de %d es:\n", BusquedaHermanoE);
                        l_mostrarLista(Pto_E);
                    }
                }
                printf("Presione enter para volver al menu\n");
                scanf("%c", &tecla);
            }else if(tecla == '0'){menu = false;}
            
        }
        tecla = ' '; 
        fflush(stdin);
        system("cls");

    }
}