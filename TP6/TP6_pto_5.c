#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "listas.h"
//#include "listas_punteros.c"

#include "nodo.h"
//#include "nodo.c"

#include "tipo_elemento.h"
//#include "tipo_elemento.c"

#include "arbol_avl.h"
//#include "arbol_avl_m.c"

#include "tabla_hash.h"
//#include "tabla_hash_zona_overflow.c"

#include "Validacion.h"

static int cantidad;

#define MAX 100

/*
Realizar una comparación de los tiempos de accesos a las claves entre un árbol AVL y
una Tabla Hash. El operador debe poder indicarle cuantas claves se deben generar
(entre 1 y 2000), cuantas repeticiones se realizaran y cuál es el rango de las claves a
generar. Luego se tomarán claves al azar dentro del mismo rango y se buscaran en
ambas estructuras. El proceso se repetirá “n” veces (repeticiones a ingresar por el 
operador). Documentar la conclusión final respecto a los tiempos de accesos de
ambas estructuras. 
*/

bool esPrimo(int num) {
    if (num <= 1) return false;

    for (int i = 2; i <= sqrt(num); i++) 
        if (num % i == 0) 
            return false;

    return true;
}

// Función para encontrar el número primo más cercano a un número dado
int encontrarPrimoMasCercano(int num) {
    if      (num <= 1) return 2;
    else if (esPrimo(num)) return num;

    int menorPrimo = num - 1;
    int mayorPrimo = num + 1;

    while (true) {
        if      (esPrimo(menorPrimo)) return menorPrimo;
        else if (esPrimo(mayorPrimo)) return mayorPrimo;

        menorPrimo--;
        mayorPrimo++;
    }
}

int funcionHash(int clave) {
    return clave % encontrarPrimoMasCercano(cantidad);
}

void CargandoClaves(int cantidad, int minimo, int maximo, TablaHash th, ArbolAVL avl) {
    srand(time(NULL));
    int clave;
    TipoElemento te;

    for (int i = 0 ; i < cantidad ; i++) {
        clave = minimo + rand() / (RAND_MAX / (maximo - minimo + 1) + 1);
        te = te_crear(clave);
        avl_insertar(avl, te);
        th_insertar(th, te);
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - // Cuerpo del programa

void main () {
    char filtro[MAX];
    bool corriendo = true;
    int buscando;

    clock_t start, end;
    double th_elapsed, avl_elapsed, th_acum = 0, avl_acum = 0;

    TipoElemento retorno;

    printf("\n// Ingresando parametros de prueba . . . \n");

    printf("\n// Nota: se hace uso de una implementacion de arboles avl modificado (arbol_avl_m.c) para poder generar arboles de hasta 2000 nodos");
    printf("\n0%d<< Ingrese la cantidad de nodos a generar [1; 2000]: ", __LINE__);
    fgets(filtro, MAX, stdin);
    cantidad = EntradaEntera(filtro, 0, 1, 2000);

    printf("\n%d<< Ingrese el valor minimo posible a generar [1; 2000]: ", __LINE__);
    fgets(filtro, MAX, stdin);
    int minimo = EntradaEntera(filtro, 0, 1, 2000);  

    printf("\n%d<< Ingrese el valor maximo posible a generar [minimo; 2000]: ", __LINE__);
    fgets(filtro, MAX, stdin);
    int maximo = EntradaEntera(filtro, 1, minimo-1, 2000);  

    printf("\n%d<< Ingrese la cantidad de veces a repetir la prueba [1; 1000]: ", __LINE__);
    fgets(filtro, MAX, stdin);
    int repeticiones = EntradaEntera(filtro, 0, 1, 1000);  

    printf("\n// Nota: se recomienda usar ordenes de magnitud entre 3 y 6 incluidos, mayor 6 y el muestreo se vuelve mas lento . . .");
    printf("\n%d<< Ingrese el orden de magnitud de busquedas/prueba (10**n busquedas) [1; 8]: ", __LINE__);
    fgets(filtro, MAX, stdin);
    double potencia = EntradaEntera(filtro, 0, 1, 8);  

    long busquedas = pow(10, potencia);

    printf("\n<< ");
    system("pause");

    TablaHash th = th_crear(cantidad, &funcionHash);
    ArbolAVL avl = avl_crear();

    printf("\n// Tiempo acumulado por prueba dado %d busquedas/prueba\n", busquedas);
    printf("\nPrueba / Tabla Hash (seg.) / Arbol AVL (seg.) / Superioridad (mas rapido)");

    for (int i = 1 ; i <= repeticiones ; i++) {
        CargandoClaves(cantidad, minimo, maximo, th, avl);
        srand(time(NULL));

        start = clock();
        for (int thsi = 1; thsi <= busquedas ; thsi++) {
            buscando = minimo + rand() / (RAND_MAX / (maximo - minimo + 1) + 1);
            retorno = th_recuperar(th, buscando);
        }
        end = clock();
        th_elapsed = (double)(end - start)/CLOCKS_PER_SEC;
        th_acum += th_elapsed;

        start = clock();
        for (int avli = 1; avli <= busquedas ; avli++) {
            buscando = minimo + rand() / (RAND_MAX / (maximo - minimo + 1) + 1);
            retorno = avl_buscar(avl, buscando);
        }
        end = clock();
        avl_elapsed = (double)(end - start)/CLOCKS_PER_SEC;
        avl_acum += avl_elapsed;

        if      (th_elapsed > avl_elapsed) printf("\n%d -   %.8f   -   %.8f    -   AVL", i, th_elapsed, avl_elapsed);
        else if (th_elapsed < avl_elapsed) printf("\n%d -   %.8f   -   %.8f    -   TH", i, th_elapsed, avl_elapsed);
        else                               printf("\n%d -   %.8f   -   %.8f    -   IGUALDAD", i, th_elapsed, avl_elapsed);
    }

    printf("\n\n>> Tiempo de busqueda en tabla Hash acumulado: %.3f seg. - Promedio: %.5f seg.", th_acum, (double)(th_acum/repeticiones));
    printf("\n>> Tiempo de busqueda en arbol avl acumulado: %.3f seg.  - Promedio: %.5f seg.", avl_acum, (double)(avl_acum/repeticiones));

    printf("\n\n// Conclusion: la busqueda en arbol avl es considerablemente mas rapida que la busqueda en tabla hash. No solo se observa por los tiempos acumulados \n   sino que tambien se puede ver en la diferencia en acumulaciones de tiempo de busqueda de cada prueba.");

    printf("\n\n<< ");
    system("pause");

    printf("\n// Terminando programa . . . ");                
    printf("\n ----------------------------------------------------------");
}
