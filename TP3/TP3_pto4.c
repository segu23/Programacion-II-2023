#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
//#include "pilas_apuntadores.c"
//#include "tipo_elemento.c"
#include "tipo_elemento.h"
#include "pilas.h"
#include "Validacion.h"


char* DecimalAhexadecimal(int numero, int base){
    Pila p1 = p_crear();
    TipoElemento x1;
    char* numeroRes =(char*) calloc(30,1);
    int resto;
    int acum = 0;
    
    while (numero != 0){
        resto = (numero % base);
        numero = (numero / base);
        x1 = te_crear (resto) ;
        p_apilar(p1,  x1);
    }

    while (!p_es_vacia(p1) ){
        x1 = p_desapilar(p1);      
        if (x1->clave <= 9){
          *(numeroRes + acum )  = 48 + x1->clave;  
        }
        else {
            *(numeroRes + acum) = 55 +x1->clave;
        }
        acum++;
        
    }
    return numeroRes;
}

int main(){
int numeroI;
int baseI;    
char* resultado =(char*) calloc(30,1);
char filtro[100];
char filtro2[100];

printf("Ingrese el numero al que quiere convertir:\n");    
fgets(filtro,100,stdin);
numeroI = EntradaEntera(filtro,0,0,0);
printf ("ingrese la base al que quieres pasar el numero: \n");
fgets(filtro2,100,stdin);
baseI = EntradaEntera(filtro2,0,2,16);
if (numeroI > 0){
    resultado = DecimalAhexadecimal(numeroI,baseI);
    printf("El numero pasado a base %i es: %s\n",baseI, resultado);
    }
else if (numeroI < 0){
    numeroI = (numeroI * -1) ;   
    resultado = DecimalAotrabase(numeroI,baseI);
    printf("El numero pasado a base %i es: -%s\n",baseI, resultado);
        }  
else printf("El numero pasado a base %i es: 0\n",baseI);


printf("La complejidad algortimica de la funcion DecimalAotrabase es de  O(Log N) ya que utiliza un ciclo que va dividiendo un \nnumero hasta que este llegue a 0\n");
system("pause");


}
