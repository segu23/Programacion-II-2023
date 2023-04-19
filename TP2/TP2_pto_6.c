#include <stdio.h>
#include <stdlib.h>
#include "Listas.h"
#include "tipo_elemento.h"
#include <string.h>

int Sublista(Lista Lis ,Lista Lis2)
{
    int B =1;       //  B me devuelve el resultado <<B = 1: La lista 2 es sublista de la lista 1>>
    TipoElemento X; //                           <<B = 2: La lista 1 es sublista de la lista 2>>
    TipoElemento Z; //                           <<B = 3: Las listas son sublistas entre si>>
                    //                           <<B = 0: No se encontraron sublistas>>
    
    Iterador I1;
    Iterador I2;

        if (l_longitud(Lis) >= l_longitud(Lis2)){       //  Si la lista 1 es mayor a la lista 2, verifico si la lista 2 es sub lista de la lista 1.
            I2= iterador(Lis2);                         //  Se ingresa tambien para comprobar si las listas son iguales.
            X = l_recuperar(Lis2, 1);                     
            while(B==1 && hay_siguiente(I2)){
                Z = l_buscar(Lis, X->clave);
                if (Z == NULL){
                B = 0;  
                }
                X= siguiente(I2);
            }
                
            if (l_longitud(Lis)==l_longitud(Lis2) && B == 1){               //<--Comprueba si las lista son iguales.
                B= 3;
            }
            
        }else if (l_longitud(Lis) < l_longitud(Lis2)){      //Si la lista 2 es mayor a la lista 1, verifico si la lista 1 es sub lista de la lista 2.
            B= 2;
            I1= iterador(Lis);
            X = l_recuperar(Lis, 1);   
            while(B==2 && hay_siguiente(I1)){
                Z = l_buscar(Lis2, X->clave);
                if (Z == NULL){
                    B = 0;  
                }
                X= siguiente(I1);
            }   
        }
        
    
    return B;
}

void main()
{
    int i, Cant , Resultado;
    int Valor;
    Lista L;
    Lista LL;
    TipoElemento H;

    L = l_crear();
    LL = l_crear();

    printf("\n Ingrese el tamanio de la lista 1:");
    if (scanf("%d",&Cant)== 0){
        printf("\n Error, ingrese numeros");
        return;
    }
    if (Cant < 0 || Cant > 100){
        printf("\n El tamanio de la lista debe ser positivo y menor o igual que 100");
        return;
    }
    fflush( stdin );
    i = 1;
    while (i <= Cant) {
        printf("\n Ingrese el entero %d para la lista 1:", i);
        
        if (scanf("%d",&Valor)== 0){
            printf("\n Error, ingrese enteros");
            fflush( stdin );
        }else{
            H= l_buscar(L,Valor);
            if (H != NULL){
                printf("\n Error, Valor repetido");
            }else{
                H = te_crear(Valor);
                l_agregar(L, H);
                i = i + 1;
            }    
        }
    }

    printf("\n Ingrese el tamanio de la lista 2:");
    if (scanf("%d",&Cant)== 0){
        printf("\n Error, ingrese numeros");
        return;
    }
     if (Cant < 0 || Cant > 100){
        printf("\n El tamanio de la lista debe ser positivo y menor o igual que 100");
        return;
    }
    fflush( stdin );
    i = 1;
    while (i <= Cant) {
        printf("\n Ingrese el entero %d para la lista 2:", i);
        
        if (scanf("%d",&Valor)== 0){
            printf("\n Error, ingrese enteros");
            fflush( stdin );
        }else{
            
            H= l_buscar(LL,Valor);
            if (H != NULL){
                printf("\n Error, Valor repetido");
            }else{
                H = te_crear(Valor);
                l_agregar(LL, H);
                i = i +1;
            }
        }
    }
    printf("\n ---------------------------------\n");
    l_mostrarLista(L);
    l_mostrarLista(LL);
    printf("\n ---------------------------------\n");
    
    Resultado = (Sublista(L,LL));
    if (Resultado == 1){
        printf("\n La lista 2 es sublista de la lista 1");
    }else if (Resultado == 2){
        printf("\n La lista 1 es sublista de la lista 2");

    }else if(Resultado==3){
        printf("\n Las listas son iguales, por lo tanto cada una es sublista de la otra");
    
    }else if(Resultado == 0){
        printf("\n No se encontraron sublistas");
    }
    
    free(L);
    free(LL);
}

// La complejidad algoritmica de la funcion sublista es de algo de O(n^2) orden cuadratico, ya que para saber si alguna de las listas es sublista de otra, recorro la
// lista mas corta y por cada elemento de esta uso l_buscar en la otra lista que tambien la recorre, entonces teenemos N*N*O(1)= O(n^2)