#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"listas.h"
#include"Validacion.h"

#define MAX_BUFFER 101

//IMPORTANTE: La recepción de claves de lista para el testeo está acotada en [-1000, 1000].

const int MAX_CLAVE = 1000;
const int MIN_CLAVE = -1000;

const int MENOR = -1;
const int IGUALES = 0;
const int MAYOR = 1;

const char SI = 's';
const char NO = 'n';

/*
    El algoritmo compara dos listas ordenadas por clave de menor a mayor (de mayor a menor vale tambien)
    Se consideran los casos donde una o ambas listas son vacias.
 */

/*
    La complejidad algorìtmica temporal de la solución (obviando el ordenamiento) es: O(n).
    Siendo n la lista de menor longitud.

    EL peor de los casos (dentro de comparar listas) es que ambas listas tengan elementos y difieran en longitud.
    En este caso, se comparan elementos de ambas n veces y luego se añade al contador correspondiente la cantidad faltante.
    Por ende, el peor de los casos está dictaminado por la longitud de la menor lista, indistintamente de las operaciones
    elementales que ocurran, dado que se est trabajando con cotas.

    Nota: Si se considera el ordenamiento, debido a que es bubblesort, la complejidad temporal se vuelve O(n^2).

    La complejidad algorítmica espacial de la solución (incluso considerando el ordenamiento) es: O(m).
    Siendo m la lista de mayor longitud.

    La cota se da dado que, en el peor de los casos, se tienen dos listas no vacías de tamaño diferente.
    Una es más grande que la otra, por ende, determina la cota espacial.
 */

//Añadi una funcion de ordenamiento, para facilitar el procedimiento del algoritmo

void cargar_buffer (char buffer[]) {

    for (int i = 0; i < MAX_BUFFER; i++) {

        buffer[i] = '\0';

    }

}

void cargar_lista_solo_claves (Lista lista) {

    int i = 0;

    char buffer[MAX_BUFFER];
    cargar_buffer(buffer);

    char cargar_otro_elemento[2];    //Para cargar el char
    cargar_otro_elemento[0] = SI;
    cargar_otro_elemento[1] = 0;
    cargar_otro_elemento[2] = '\0';


    int clave_a_cargar = 0;

    while ((i < 100) && (cargar_otro_elemento[0] == SI)) {

        printf("\nIngrese una clave para el elemento de la lista[-1000, 1000]: ");
        fgets(buffer, 100, stdin);
        clave_a_cargar = EntradaEntera(buffer, 0, MIN_CLAVE, MAX_CLAVE);
        l_agregar(lista, te_crear(clave_a_cargar));


        printf("\n¿Desea cargar otro elemento más?[s/n]: ");
        fgets(cargar_otro_elemento, 2, stdin);
        while(getchar() != '\n');

        while((cargar_otro_elemento[0] != SI) && (cargar_otro_elemento[0] != NO)) {

            printf("\n¿Desea cargar otro elemento más?[s/n]: ");
            fgets(cargar_otro_elemento, 2, stdin);
            while(getchar() != '\n');

        }

        i++;

    }

}

//Devuelve una clave segun sea el primero menor, igual o mayor al segundo
int comparar_enteros (int primero, int segundo) {

    int estado = IGUALES;

    if (primero > segundo) {

        estado = MAYOR;

    } else if (primero < segundo) {

        estado = MENOR;

    }

    return estado;
}

//Devuelve el menor de dos enteros
int menor (int un_entero, int otro_entero) {

    int menor_entero = 0;

    if (un_entero > otro_entero) {

        menor_entero = otro_entero;

    } else if (un_entero < otro_entero) {

        menor_entero = un_entero;

    } else {  //Si son iguales devuelve el primero.

        menor_entero = un_entero;

    }

    return menor_entero;
}

//Usa bubblesort. Se que no es el mejor en términos de eficiencia.
void ordenar_lista_menor_a_mayor (Lista lista) {

    int n = l_longitud(lista);

    TipoElemento a;
    TipoElemento b;

    for(int i = 0; i <= n; i++)

        for (int j = 2; j <= n - i; j++){

            a = l_recuperar(lista, j);
            b = l_recuperar(lista, j-1);

            if (b->clave > a->clave) {   //Inserta en posicion correspondiente y borra posicion previa (duplicada si no)

                l_insertar(lista, a, j-1);
                l_eliminar(lista, j+1);

           }

        }

}

//Si una lista esta vacia, vale 0, si ambas vacias ambaas valen 0.
int comparar_con_lista_vacia (Lista l1, Lista l2) {

    int resultado_comparacion = -2;

    if ((l_es_vacia(l1)) && (l_es_vacia(l2))) {

        resultado_comparacion = IGUALES;

    } else if ((l_es_vacia(l1)) && !(l_es_vacia(l2))) {

        resultado_comparacion = MENOR;

    } else {

        resultado_comparacion = MAYOR;

    }

    return resultado_comparacion;
}

//Compara dos listas, actualizando contadores de mayores, desde pos == 1 hasta longitud
void comparar_listas_hasta_longitud (Lista l1, Lista l2, int longitud, int* cont_l1, int* cont_l2) {

    Iterador it_l1 = iterador(l1);
    Iterador it_l2 = iterador(l2);

    TipoElemento e_l1;
    TipoElemento e_l2;

    for (int i = 1; i <= longitud; i++) {

        e_l1 = siguiente(it_l1);
        e_l2 = siguiente(it_l2);

        if (e_l1->clave > e_l2->clave) {

            (*cont_l1) += 1;

        } else if (e_l2->clave > e_l1->clave) {

            (*cont_l2) += 1;

        }

    }

}

//Asume listas ordenadas de menor a mayor, por eso añadi el ordenamiento (para testeos, no es el ordenamiento mas eficiente en temporalidad)
int comparar_listas (Lista l1, Lista l2) {

    int resultado_comparacion = -2;

    //Primer chequeo trata el caso de una o más listas vacias
    if ((l_es_vacia(l1)) || (l_es_vacia(l2))) {

        resultado_comparacion = comparar_con_lista_vacia(l1, l2);

    } else {    //Ambas listas no vacias

        int contador_l1 = 0;
        int contador_l2 = 0;

        if (l_longitud(l1) == l_longitud(l2)) {    //Ambas listas igual longitud

            comparar_listas_hasta_longitud(l1, l2, l_longitud(l1), &contador_l1, &contador_l2);

        } else {    //Listas de longitudes desiguales

            int menor_longitud = menor(l_longitud(l1), l_longitud(l2));

            comparar_listas_hasta_longitud(l1, l2, menor_longitud, &contador_l1, &contador_l2);

            if (l_longitud(l1) > l_longitud(l2)) {

                contador_l1 += l_longitud(l1) - l_longitud(l2);

            } else if (l_longitud(l2) > l_longitud(l1)) {

                contador_l2 += l_longitud(l2) - l_longitud(l1);

            }

        }

        //Ya cargados los contadores de elementos mayores, se los compara

        if (contador_l1 > contador_l2) {

            resultado_comparacion = MAYOR;

        } else if (contador_l1 < contador_l2) {

            resultado_comparacion = MENOR;

        } else {

            resultado_comparacion = IGUALES;

        }

    }

    return resultado_comparacion;
}

void informar_resultado(int resultado) {

    printf("\nComparando las listas resulta: ");

    if(resultado == MENOR) {

        printf("L1 < L2\n");

    } else if (resultado == IGUALES) {

        printf("L1 = L2\n");

    } else if (resultado == MAYOR) {

        printf("L1 > L2\n");

    }

}

void cargarListas (cantidad, lista) {
    char filtro[100];
    int numero;
    TipoElemento elemento;
    for(int i = 0; i < cantidad; i++){
        TipoElemento elemento;
        printf(" << Ingrese el elemento en posicion %i: ", i+1);
        fgets(filtro, 100, stdin);
        numero = EntradaEntera(filtro, 0, 0, 0);
        elemento = te_crear_con_valor(i, (void *) numero);
        l_agregar(lista, elemento);
    }
}

//El main es para hacer tests, ya viene con una prueba cargada
int main () {

    Lista l1 = l_crear();
    Lista l2 = l_crear();

    char filtro[100];
    printf(" << Ingrese la cantidad de elementos de la Lista nro. 1: ");
    fgets(filtro, 100, stdin);
    int cantidad = EntradaEntera(filtro, 1, 1, 99);
    cargarListas(cantidad, l1);

    printf(" << Ingrese la cantidad de elementos de la Lista nro. 2: ");
    fgets(filtro, 100, stdin);
    int cantidad = EntradaEntera(filtro, 1, 1, 99);
    cargarListas(cantidad, l2);
    
    /*
    l_agregar(l1, te_crear_con_valor(9, (int*)5));
    l_agregar(l1, te_crear_con_valor(8, (int*)4));
    l_agregar(l1, te_crear_con_valor(7, (int*)7));

    l_agregar(l2, te_crear_con_valor(22, (int*)5));
    l_agregar(l2, te_crear_con_valor(10, (int*)2));
    l_agregar(l2, te_crear_con_valor(19, (int*)2));
    */

    l_mostrarLista(l1);
    l_mostrarLista(l2);

    ordenar_lista_menor_a_mayor(l1);
    ordenar_lista_menor_a_mayor(l2);

    l_mostrarLista(l1);
    l_mostrarLista(l2);

    int resultado = comparar_listas(l1, l2);

    informar_resultado(resultado);

    free(l1);
    free(l2);

    return 0;
}
