#include <stdio.h>
#include <stdlib.h>

#include "validacion.h"
//#include "tipo_elemento.c"
#include "tipo_elemento.h"
//#include "colas_punteros.c"
#include "colas.h"

#define MAX 100
#define MAXV 1000
#define MINV -1000

/*
Dada una cola de valores enteros no repetidos y mayores o iguales a 2, obtener todos los valores que son Divisores Totales o parciales. 
Se dice que un valor es Divisor Total si permite dividir a todos los demás valores de la cola en forma exacta. 
Se dice que un divisor es parcial si al menos puede dividir en forma exacta al menos al 50% de la cola (es decir a la mitad de los elementos). 
Determinar la complejidad algorítmica de la solución. 

Ejemplo: si “C” contiene (8, 12, 2, 6, 4) se dice que “2” es el divisor total de la cola porque divide al resto en forma exacta. 
Y “4” es divisor parcial por divide a 8,12 y el mismo. 
*/

void BuscarDivisores(Cola cola, Cola cdivtot, Cola cdivpar, float longitud) {
    if (c_es_vacia(cola)) return;

    TipoElemento aux, div;
    int i, t, cont = 0;

    for (i = 0; i < longitud; i++) {                                        
        aux = c_desencolar(cola);
        div = aux;
        c_encolar(cola, aux);

        for (t = 1; t <= longitud; t++) {                                   
            aux = c_desencolar(cola);

            if (aux->clave % div->clave == 0) cont++; 

            c_encolar(cola, aux);
        }

        if      (cont == longitud)               c_encolar(cdivtot, div);
        else if (cont >= (float) (longitud / 2)) c_encolar(cdivpar, div);

        cont = 0;
    }
}

bool c_existe (Cola cola, int clave, int longitud) {
    if(c_es_vacia(cola)) return false;

    TipoElemento aux;
    bool salida = false;

    for (int i = 0; i < longitud; i++) {
        aux = c_desencolar(cola);

        if (aux->clave == clave) {
            salida = true;
        }
        c_encolar(cola, aux);
    }

    return salida;
}

int main () {
    char filtro[MAX];
    Cola cl = c_crear();
    TipoElemento elemento;
    bool repite;
    int clave;

    printf("\n--> TP NRO. 2: PILAS <-- ");
    printf("\n<< Generando pila...");
    printf("\n<< Ingrese la longitud de la pila [0; 100]: ");
    fgets(filtro, MAX, stdin);
    int longitud = EntradaEntera(filtro, 0, 0, 100);

    for (int i = 1; i <= longitud; i++) {
        do {
            repite = false;
            printf("\n<< Ingrese la clave ([-1000; -2] union [2; 1000]) nro. %d a la cola: ", i);
            fgets(filtro, MAX, stdin);

            if (strchr(filtro, '-') != NULL) elemento = te_crear(EntradaEntera(filtro, 0, -1000, -2));
            else                             elemento = te_crear(EntradaEntera(filtro, 0, 2, 1000));

            repite = c_existe(cl, elemento->clave, longitud);

            if (repite) printf("\n>! Clave repetida; ingrese de nuevo . . . \n");
            
        } while (repite);

        c_encolar(cl, elemento);
    }
   
    if (longitud != 0) {
        printf("\n>> Pila generada . . . \n");
        c_mostrar(cl);

        Cola cdivtot = c_crear();
        Cola cdivpar = c_crear();

        BuscarDivisores(cl, cdivtot, cdivpar, longitud);

        printf("\n>> Divisores totales . . . \n");
        c_mostrar(cdivtot);

        printf("\n>> Divisores parciales . . . \n");
        c_mostrar(cdivpar);
    } 
    else printf("\n>! Pila vacia. Imposible buscar divisores . . . \n");

    printf("\n>> Complejidad algoritmica; la complejidad de la solución de (BuscarDivisores()) es de O(n**2).");
    printf("\n>> Terminando programa . . . \n");

    return 0;
}
