#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include "Validacion.h"
#include <string.h>

#include "listas_arreglos.c"
#include "tipo_elemento.c"
//recibe directamente los dos elementos y los compara
int es_divisible (int x1, int x2) {
    //int residuo;
    bool esdivisible;
    int residuo = x1 % x2;
return residuo;
}


int main (){
int resultado = 1;    
int i = 1;  
int j = 1;  
int k = 1;
int t1 = 1;  
int t2 = 1; 
int valor1;
int valor2;  
Lista l = l_crear();
Lista l2 = l_crear();
TipoElemento z1;
TipoElemento z2;
Iterador iter = iterador(l);
Iterador iter1 = iterador(l2);
printf("Ingrese la longitud de la primera lista: \n");
scanf("%i",&t1);
printf("Ingrese la longitud de la segunda lista: \n");
scanf("%i",&t2);
printf("Ingrese los valores de la lista 1 de a 1: \n"); 
for (i = 1;i <= t1;i++){
   scanf("%d",&valor1);
   z1 = te_crear(valor1);
   l_agregar(l,z1);

}
printf("Ingrese los valores de la lista 2 de a 1: \n");
for (j = 1;j <= t2;j++){
   scanf("%d",&valor2);
    z2 = te_crear(valor2);
   l_agregar(l2,z2);
}


z1 = l_recuperar(l, k); 
z2 = l_recuperar(l2, k);
int check = 0;

for (k = 1;k <= t1;k++){
    resultado = es_divisible(z1->clave,z2->clave); 
    if (resultado == 0){
        z1 = siguiente(iter); 
        z2 = siguiente(iter1); 
                        }
if (resultado > 0){
    check = 1;
}
}

if (check == 0){
    printf("la lista 1 es divisible por la lista 2\n");
}
if (check == 1){
    printf("la lista 1 no es divisible por la lista 2\n");  
}

system("pause");
}


//printf("%i",k);


