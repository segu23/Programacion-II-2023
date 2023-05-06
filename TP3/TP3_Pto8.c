#include <stdio.h>
#include <stdlib.h>

#include "tipo_elemento.h"
#include "pilas.h"
#include "Validacion.h"

Pila CantRepeticiones(Pila P)
{
    Pila Pcopy; //Su funcion es guardar la pila original para que no se pierda
    Pila PAux;  //Una pilaxuliar para no perder la pila al momento de recorrerlas
    Pila PRta;  //Pila que almacena el resultado
    TipoElemento X;

    Pcopy= p_crear();
    PAux= p_crear();
    PRta= p_crear();

    int Numero, Repe, Primera, Salir; 

    Primera = 1;    //Si esta en 1 guarda la pila original en otra pila cuando se recorre por primera vez
    Repe = 0;       //Acumula la repeticion de los valores de la lista
    Salir = 1;      //Termina el bucle cuando se vuelve 0
    
    while(Salir == 1)
    {
        if(p_es_vacia(PAux)){
            X= p_desapilar(P);
            if(Primera == 1){p_apilar(Pcopy,X);}
            Numero = X->clave; 
            Repe++;
            while(!p_es_vacia(P)){
                X= p_desapilar(P);
                if(Primera == 1){p_apilar(Pcopy,X);} //Guardo la pila original
                if(X->clave != Numero)
                { 
                    p_apilar(PAux,X);
                }else{Repe++;}
            }
            Primera= 0;
            X=te_crear_con_valor(Numero, (void *)Repe); //Se guarda en X->Clave el numero y en X->Valor las repeticiones
            Repe= 0;
            p_apilar(PRta,X);
        }else if(p_es_vacia(P)){
            X= p_desapilar(PAux);
            Numero = X->clave;
            Repe++;
            while(!p_es_vacia(PAux)){
                X= p_desapilar(PAux);
                if(X->clave != Numero)
                { 
                    p_apilar(P,X);
                }else{Repe++;}
            }
            X=te_crear_con_valor(Numero, (void *)Repe);
            Repe = 0;
            p_apilar(PRta,X);    
        }


        if (p_es_vacia(P) && p_es_vacia(PAux)){Salir = 0;}
    }
    while(!p_es_vacia(Pcopy)){
        X=p_desapilar(Pcopy);
        p_apilar(P,X);
    }
    return PRta;
}




void main (){
    Pila PMostrarResultado;
    Pila PRta;
    Pila P;
    TipoElemento X;
    int Cant, Valor, i;
    char filtro[100];

    PMostrarResultado= p_crear();
    PRta = p_crear();
    P = p_crear();
    
 printf("\n Ingrese el tamanio de la Pila: ");
    fgets(filtro, 100, stdin);
    Cant = EntradaEntera(filtro, 0, 1, 100);
    
    i = 1;
    while (i <= Cant) {
        printf("\n Ingrese el entero %d para la Pila:", i);
        fgets(filtro, 100, stdin);
        Valor = EntradaEntera(filtro, 0, 0, 0);
        
            X = te_crear(Valor);
            p_apilar(P, X);
            i = i + 1;
            
    }

    //Muestro el resultado de una mejor forma
    PRta = CantRepeticiones(P);
    
    printf("-------------------------------\n");
    p_mostrar(P);
    printf("-------------------------------\n");
    printf("Los valores y las repeticiones de la pila ingresada son: ");
    
    while(!p_es_vacia(PRta)){
        X=p_desapilar(PRta);
        p_apilar(PMostrarResultado,X);    
    }

while(!p_es_vacia(PMostrarResultado)){
        X=p_desapilar(PMostrarResultado);
        printf("(%d:%d)",X->clave, X->valor);
         
    }

    printf("\n-------------------------------\n");
    printf("Pila original\n");
    p_mostrar(P);
    printf("-------------------------------\n");
    printf("La complejidad algoritmica de la funcion Repeticiones es de algo de O(n^2) orden cuadratico, ya que para recorrer la pila y sacar los valores repetidos necesito de un while de N veces (siendo N el largo de la pila) y dentro de ese while hay otro para sacar el elemento y sus repeticiones, entonces tenemos N*N*O(1)= O(n^2)");
    

}