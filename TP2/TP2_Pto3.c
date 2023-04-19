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
bool es_divisible (int x1, int x2) {
    //int residuo;
    bool result = false;
    int residuo = x1 % x2;
    if (residuo == 0){
        result = true ;
    }
return result;
}


int main (){
int resultado = 1;    
int i = 1;  
int j = 1;  
int k = 1; 
int valor1;
int valor2;  
char filtro[100];
Lista l = l_crear();
Lista l2 = l_crear();
TipoElemento z1;
TipoElemento z2;
Iterador iter = iterador(l);
Iterador iter1 = iterador(l2);
printf("\nIngrese la longitud de las 2 listas:");
int t; 
scanf("%c",&filtro);
t = EntradaEntera(filtro,1,0,0);



printf("\nIngrese los valores de la lista 1 de a 1:"); 

for (i = 1;i <= t;i++){
   char filtro2[100]; 
   //scanf("%s",&filtro2);
   fgets(filtro2,100,stdin);
   valor1 = EntradaEntera(filtro2,0,0,0);
   z1 = te_crear(valor1);
   l_agregar(l,z1);

}
printf("\nIngrese los valores de la lista 2 de a 1:");
for (j = 1;j <= t;j++){ 
    char filtro3[100];
   //scanf("%s",&filtro3);
   fgets(filtro3,100,stdin);
   valor2 = EntradaEntera(filtro3,0,0,0);
    z2 = te_crear(valor2);
   l_agregar(l2,z2);
}


z1 = l_recuperar(l, k); 
z2 = l_recuperar(l2, k);
int check = 0;

for (k = 1;k <= t;k++){
    //resultado = es_divisible(z1->clave,z2->clave); 
    if (es_divisible(z1->clave,z2->clave)){
        z1 = siguiente(iter); 
        z2 = siguiente(iter1); 
                        }
    if (es_divisible(z1->clave,z2->clave)== false){
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


