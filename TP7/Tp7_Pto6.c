#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "conjuntos.h"
#include "tipo_elemento.h"
#include "Validacion.h"

void main(){
    Conjunto CtoA, CtoB, CtoInte;
    TipoElemento X;
    int i, Valor, Cant;
    char filtro[100];
    CtoA = cto_crear();
    CtoB = cto_crear();


    printf("\n Ingrese la cantidad de elementos que quiera ingresar en el conjunto A: ");
    fgets(filtro, 100, stdin);
    while(filtro[0] < '0' || filtro[0]> '9'){
        printf(" Valor invaido\n");
        printf("\n Ingrese la cantidad de elementos que quiera ingresar en el conjunto A: ");
        fgets(filtro, 100, stdin);
    }
    Cant = EntradaEntera(filtro, 0, 0, 100);
    
    i = 1;
    while (i <= Cant) {
        printf("\n Ingrese el entero %d para el conjunto A:", i);
        fgets(filtro, 100, stdin);
         while(filtro[0] < '0' || filtro[0]> '9'){
            printf(" Valor invaido\n");
            printf("\n Ingrese el entero %d para el conjunto A: ", i);
            fgets(filtro, 100, stdin);
        }
        Valor = EntradaEntera(filtro, 1, 0, 0);
      
        if(cto_es_vacio(CtoA)){
            X = te_crear(Valor);
            cto_agregar(CtoA, X);
            i = i + 1;    
        }else if (cto_pertenece(CtoA,Valor)){
            printf("\n Error, Valor repetido");
        }else{
            X = te_crear(Valor);
            cto_agregar(CtoA, X);
            i = i + 1;
        }

        
            
    }

    printf("\n Ingrese la cantidad de elementos que quiera ingresar en el conjunto B:");
    fgets(filtro, 100, stdin);
    while(filtro[0] < '0' || filtro[0]> '9'){
        printf(" Valor invaido\n");
        printf("\n Ingrese la cantidad de elementos que quiera ingresar en el conjunto B: ");
        fgets(filtro, 100, stdin);
    }
    Cant = EntradaEntera(filtro, 0, 0, 100);

    i = 1;
    while (i <= Cant) {
        printf("\n Ingrese el entero %d para el conjunto B: ", i);
        fgets(filtro, 100, stdin);
        while(filtro[0] < '0' || filtro[0]> '9'){
            printf(" Valor invaido\n");
            printf("\n Ingrese el entero %d para el conjunto B: ", i);
            fgets(filtro, 100, stdin);
        }
        Valor = EntradaEntera(filtro, 1, 0, 0);

        if(cto_es_vacio(CtoB)){
            X = te_crear(Valor);
            cto_agregar(CtoB, X);
            i = i + 1;   
        }else if (cto_pertenece(CtoB,Valor)){
            printf("\n Error, Valor repetido");
        }
        else{
            X = te_crear(Valor);
            cto_agregar(CtoB, X);
            i = i + 1;
        } 
    }


    printf("El conjunto A contiene:\n");
    cto_mostrar(CtoA);
    printf("El conjunto B contiene:\n");
    cto_mostrar(CtoB);
    printf("----------------------------------------------\n");
    

    if(cto_es_vacio(CtoA) && cto_es_vacio(CtoB)){
        printf("\nAmbos conjuntos son vacios\n\n");
        
    }else if(cto_es_vacio(cto_diferencia(CtoA, CtoB))){
        printf("\nEl conjunto A es subconjunto del conjunto B\n\n");
        
    }else{
        printf("\nEl conjunto A no es subconjunto de B\n\n");
    }
    printf("---------------------COMPLEJIDAD ALGORITMICA---------------------\n");    
    printf("La complejidad algoritmica depende del TAD utilizado.\nSi se utiliza Conjuntos de listas la complejidad sera de O(n^2), ya que se utiliza la operacion de cto_diferencia() la cual recorre la lista de forma lineal.\nEn cambio al utilizar el TAD de conjuntos con arboles AVL la complejidad pasara a ser O(n log n) ya que el rtecorrido de un arbol AVL es mas eficiente y no hace falta recorrer todo el arbol.");    
}
