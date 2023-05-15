//Dada una cola de números enteros, no ordenada, construir un algoritmo que permita
//pasar a otra cola todos los elementos que no se repiten en la primera, sin destruir el
//contenido de la cola original y dejándola en su estado inicial. Determinar la
//complejidad algorítmica de la solución. 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Validacion.h"
#include <string.h>
#include "colas.h"
//#include "colas_punteros.c"
#include "tipo_elemento.h"
//#include "tipo_elemento.c"
Cola Num_no_repetidos(Cola c, int t){
    int i = 0;
    int i2 = 0;
    int i3 = 0;
    TipoElemento x1 ;
    x1 = te_crear(0);
    Cola Caux = c_crear();
    Cola Caux2 = c_crear();
    Cola Cresultado = c_crear();
    while (i < t){
        x1 = c_desencolar(c);
        c_encolar(Caux, x1);
        c_encolar(Caux2, x1);
        c_encolar(c,x1);
        i++;
    }
    int contador = 0 ;
    TipoElemento x2 ;
    x2 = te_crear(0);
    TipoElemento x3 ;
    x3 = te_crear(0);
    for (i2 = 0; i2 < t; i2++){
        x2 = c_desencolar(Caux);
            for (i3 = 0; i3 < t;i3++){
                x3 = c_desencolar(Caux2);
                if (x2->clave == x3->clave){
                    contador = contador + 1;   
                    c_encolar(Caux2,x3);
                }
                else
                {
                    c_encolar(Caux2,x3);
                }
        }
        if (contador >= 2){
            
            
            contador = 0;
        }
        else{
            c_encolar(Cresultado,x2);
            contador = 0;
        }
        c_encolar(Caux,x2);
    }
    return Cresultado;

    //dos for uno que recupoere el elemento y depsues el otro que lo busque en la ota cola (cantidades)
}


int main(){
TipoElemento x;
Cola c = c_crear();   
Cola cres = c_crear();  
int i = 0;
int t;    
int dato;
char filtro[100];
char filtro2[100];  
printf("Ingrese el tamanio de la cola:\n");
fgets(filtro,100,stdin);
t = EntradaEntera(filtro,0,0,100);
if (t != 0) {
    printf("Ingrese los elementos de la cola de a 1:\n");
    for (i = 0; i < t; i++){
        fgets(filtro2,100,stdin);
        dato = EntradaEntera(filtro2,0, -1000, 1000);
        x = te_crear(dato);
        c_encolar(c,x);
    }
}
cres = Num_no_repetidos(c,t);
if (c_es_vacia(cres) == true) {
 printf("No hay numeros que no se repitan, la cola esta vacia\n");
}
else{
    printf("\nCola con los numeros no repetidos:\n");
    c_mostrar(cres); 
}

printf("Cola original:\n");
c_mostrar(c);

printf("\nLa complejidad algoritmica de la funcion es O(n^2) ya que utiliza dos for anidados\n");

system("pause");
    
}
