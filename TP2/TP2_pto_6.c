#include <stdio.h>
#include <stdlib.h>
#include "Listas.h"
#include "tipo_elemento.h"
#include <string.h>

int Sublista(Lista Lis ,Lista Lis2)
{
    int i =1;
    int B =1;       //  B me devuelve el resultado <<B = 1: La lista 2 es sublista de la lista 1>>
    TipoElemento X; //                           <<B = 2: La lista 1 es sublista de la lista 2>>
    TipoElemento Z; //                           <<B = 3: Las listas son iguales>>
                    //                           <<B = 0: No se encontraron sublistas>>
    
    Iterador I1;
    Iterador I2;

        if (l_longitud(Lis) >= l_longitud(Lis2)){       //  Si la lista 1 es mayor a la lista 2, verifico si la lista 2 es sub lista de la lista 1.
            I2= iterador(Lis2);                         //  Se ingresa tambien para comprobar si las listas son iguales.
            while(B==1 && hay_siguiente(I2)){
                X = l_recuperar(Lis2, i);
                Z = l_buscar(Lis, X->clave);
                if (Z == NULL){
                B = 0;  
                }
                X= siguiente(I2);
                i++;
            }
                
            if (l_longitud(Lis)==l_longitud(Lis2) && B == 1){               //<--Comprueba si las listason iguales.
                B= 3;
            }
            
        }else if (l_longitud(Lis) < l_longitud(Lis2)){      //Si la lista 2 es mayor a la lista 1, verifico si la lista 1 es sub lista de la lista 2.
            B= 2;
            I1= iterador(Lis);
                
            while(B==2 && hay_siguiente(I1)){
                X = l_recuperar(Lis, i);
                Z = l_buscar(Lis2, X->clave);
                if (Z == NULL){
                    B = 0;  
                }
                X= siguiente(I1);
                i++;
            }   
        }
        
    
    return B;
}

void main()
{
    int i, Cant , Resultado;
    char Valor[20];
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
    fflush( stdin );
    i = 1;
    while (i <= Cant) {
        printf("\n Ingrese un valor %d para la lista 1:", i);
        fgets(Valor, 3, stdin);
		Valor[strcspn(Valor, "\n")] = '\0';
        fflush( stdin );
        H= l_buscar(L,Valor[0]);
        if (H != NULL){
            printf("Error, Valor repetido");
        }else{
            H = te_crear(Valor[0]);
            l_agregar(L, H);
            i = i + 1;
        }    
    }

    printf("\n Ingrese el tamanio de la lista 2:");
    if (scanf("%d",&Cant)== 0){
        printf("\n Error, ingrese numeros");
        return;
    }
    fflush( stdin );
    i = 1;
    while (i <= Cant) {
        printf("\n Ingrese un valor %d para la lista 2:", i);
        fgets(Valor, 3, stdin);
		Valor[strcspn(Valor, "\n")] = '\0';
        fflush( stdin );
        H= l_buscar(LL,Valor[0]);
        if (H != NULL){
            printf("Error, Valor repetido");
        }else{
            H = te_crear(Valor[0]);
            l_agregar(LL, H);
            i = i +1;
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
        printf("\n Las listas son iguales");
    
    }else if(Resultado == 0){
        printf("\n No se encontraron sublistas");
    }
}

