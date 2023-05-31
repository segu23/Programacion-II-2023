#include <stdio.h>
#include <stdlib.h>

#include "arboles_utilidades.h"
#include "arbol_binario.h"
#include "nodo.h"
#include "tipo_elemento.h"
#include "listas.h"

#include "arboles_utilidades.c"
#include "arbol_binario_punteros.c"
#include "nodo.c"
#include "tipo_elemento.c"


#include "Validacion.h"

#define MAX 100
/*
Para un nodo del arbol binario determinado:
    a. Indicar el nombre del nodo padre (clave)
    b. Listar los hijos (solo las clave/s)
    c. Listar el hermano (solo la clave)
    d. Calcular el nivel en el que se encuentra
    e. Calcular la altura de su rama (Altura del Sub�rbol)
    f. Listar todos los nodos que est�n en el mismo nivel (solo la clave)
*/

ArbolBinario CreandoArbol(ArbolBinario);

void CargarSubArbol(ArbolBinario, NodoArbol, int);

bool IngresoEntero(ArbolBinario, int *);

void buscandoClaveRecursivamente(NodoArbol, int, bool *, NodoArbol *);

NodoArbol BuscarNodo(NodoArbol, int);

NodoArbol BuscandoNodorecursivamente(NodoArbol, int, bool *);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - // a. Indicar el nombre del nodo padre (clave)

void BuscandoPadreRecursivamente(NodoArbol actual, NodoArbol hijo, bool *encontrado, NodoArbol *retorno) {
    if (actual != NULL) {
        if (n_hijoizquierdo(actual) == hijo || n_hijoderecho(actual) == hijo) {
            *encontrado = true;
            *retorno = actual;
        }

        else if (*encontrado == false) BuscandoPadreRecursivamente(n_hijoizquierdo(actual), hijo, encontrado, retorno);
        else if (*encontrado == false) BuscandoPadreRecursivamente(n_hijoderecho(actual), hijo, encontrado, retorno);
    }
}

NodoArbol n_nodoPadre(ArbolBinario a, NodoArbol hijo) {
    if (a == NULL || hijo == NULL || hijo == a_raiz(a)) return NULL;

    bool encontrado = false;
    NodoArbol retorno = NULL;
    BuscandoPadreRecursivamente(a_raiz(a), hijo, &encontrado, &retorno);

    if (retorno != NULL) return retorno;
    else                 return NULL;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  // b. Listar los hijos (solo las clave/s)

void n_mostrarHijos(NodoArbol n) {
    if (n == NULL) return;

    else if (n_hijoizquierdo(n) == NULL && n_hijoderecho(n) == NULL) printf("\n>> El nodo sujeto clave %d no tiene nodos hijos . . .\n", n_recuperar(n)->clave);

    else {
        printf("\n>> Los hijos del nodo sujeto clave %d son: ", n_recuperar(n)->clave);

        if (n_hijoizquierdo(n) != NULL) printf("\n>>_ Nodo hijo izquierdo: clave(%d)", n_recuperar(n_hijoizquierdo(n))->clave);
        else                            printf("\n>>_ Nodo hijo izquierdo: NULL");

        if (n_hijoderecho(n) != NULL)   printf("\n>>_ Nodo hijo derecho: clave(%d)", n_recuperar(n_hijoderecho(n))->clave);
        else                            printf("\n>>_ Nodo hijo derecho: NULL");
        printf("\n");
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - // c. Listar el hermano (solo la clave)

void n_mostrarHermano(ArbolBinario a, NodoArbol n) {
    if (n == NULL) return;

    NodoArbol padre = n_nodoPadre(a, n);

    if      (n_hijoizquierdo(padre) != NULL && n_hijoizquierdo(padre) != n) printf("\n>> Nodo hermano del nodo sujeto clave %d: clave(%d)\n", n_recuperar(n)->clave, n_recuperar(n_hijoizquierdo(padre))->clave);
    else if (n_hijoderecho(padre) != NULL && n_hijoderecho(padre) != n)     printf("\n>> Nodo hermano del nodo sujeto clave %d: clave(%d)\n", n_recuperar(n)->clave, n_recuperar(n_hijoderecho(padre))->clave);
    else                                                                    printf("\n>> El nodo sujeto clave %d no tiene nodo hermano . . .\n", n_recuperar(n)->clave);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - // d. Calcular el nivel en el que se encuentra

void buscandoNivelRecursivamente(NodoArbol actual, int clave, int *nivel, int cant) {
    if (actual != NULL) {
        TipoElemento x = n_recuperar(actual);

        if (x->clave == clave) *nivel = cant;

        else {
            buscandoNivelRecursivamente(n_hijoizquierdo(actual), clave, nivel, cant+1);
            buscandoNivelRecursivamente(n_hijoderecho(actual), clave, nivel, cant+1);
        }
    }
}

int n_nivelNodo(ArbolBinario a, NodoArbol n) {
    if (a == NULL || n == NULL) return -1;
    else if (a_raiz(a) == n)    return 0;

    int nivel = -1;
    buscandoNivelRecursivamente(a_raiz(a), n_recuperar(n)->clave, &nivel, 0);
    return nivel;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - // e. Calcular la altura de su rama (Altura del Sub�rbol)

void calculandoAlturaRecursivamente(NodoArbol actual, int *altura, int suma) {
    if (actual != NULL) {

        suma++;
        *altura = suma;

        calculandoAlturaRecursivamente(n_hijoizquierdo(actual), altura, suma);
        calculandoAlturaRecursivamente(n_hijoderecho(actual), altura, suma);
    }
}

int n_alturaSubArbol(NodoArbol n) {
    if (n == NULL) return -1;

    int altura = 0;
    calculandoAlturaRecursivamente(n, &altura, 0);
    return altura;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - // f. Listar todos los nodos que est�n en el mismo nivel (solo la clave)

Lista encolandoNivelRecursivamente(NodoArbol actual, int nivel, int *cont, Lista cola) {
    if (*cont == nivel) {
        l_agregar(cola, n_recuperar(actual));
        *cont--;
    }

    else {
        *cont++;
        encolandoNivelRecursivamente(n_hijoizquierdo(actual), nivel, cont, cola);
        encolandoNivelRecursivamente(n_hijoderecho(actual), nivel, cont, cola);
    }

    return cola;
}

void n_mostrarNivel(ArbolBinario a, NodoArbol n) {
    if (a == NULL || n == NULL) return;

    printf("\n>> Claves de nodos en el nivel %d <<\n", n);
    int cont = 0, nivel = n_nivelNodo(a, n);
    Lista cola = l_crear();

    if (nivel == 0) l_agregar(cola, n_recuperar(a_raiz));
    else            cola = encolandoNivelRecursivamente(a_raiz(a), nivel, &cont, cola);
    
    l_mostrarLista(cola);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - // Cuerpo del programa

int main () {
    char filtro[MAX];
    bool corriendo = true;
    int accion;
    ArbolBinario arbol;
    NodoArbol sujeto;

    printf("\n// Generando arbol binario . . . \n");
    printf("\n>! Aviso: el ingreso se realiza en pre-orden, para terminar la carga se le tiene que asignar NULL o '.' a todasa las hojas\n");

    arbol = CreandoArbol(arbol);
    printf("\n// Arbol binario generado . . . \n");
    mostrar_arbol_binario(a_raiz(arbol), PRE_ORDEN);

    printf("\n<< ");
    system("pause");

    bool existe;
    printf("\n// Asignando nodo sujeto de prueba . . .\n");

    do{
        existe = true;
        printf("\n%d << Ingrese la clave de un nodo existente en el arbol: ", __LINE__);
        fgets(filtro, MAX, stdin);
        fflush(stdin);
        int clave = EntradaEntera(filtro, 0, -100000, 100000);
        
        sujeto = BuscarNodo(a_raiz(arbol), clave);

        if (sujeto == NULL) {
            printf("\n>! Clave inexistente, ingrese la clave de un nodo existente . . .\n");
            existe = false;
        }
    } while (!existe);

    printf("\n>> Nodo asignado: clave(%d) direccion(%p)\n", n_recuperar(sujeto)->clave, sujeto);
    
    printf("\n<< ");
    system("pause");

    while(corriendo) {
        printf("\n--> TP NRO. 5: ARBOLES BINARIOS <-- ");
        printf("\n_ 1 >> Cambiar nodo sujeto de prueba");
        printf("\n_ 2 >> Comenzar resolucion del ejercicio");
        printf("\n_ 0 >> Terminar programa");
        printf("\n\n%d << Ingrese accion: ", __LINE__);
        fgets(filtro, MAX, stdin);
        accion = EntradaEntera(filtro, 0, 0, 2);

        switch (accion) {
            case 0 : {
                printf("\n// Terminando programa . . . ");
                corriendo = false;
            } break;

            case 1 : {
                printf("\n// Asignando nodo sujeto de prueba . . . \n");

                do{
                    existe = true;
                    mostrar_arbol_binario(a_raiz(arbol), IN_ORDEN);
                    printf("\n%d << Ingrese la clave de un nodo existente en el arbol: ", __LINE__);
                    fgets(filtro, MAX, stdin);
                    int clave = EntradaEntera(filtro, 0, -100000, 100000);

                    sujeto = BuscarNodo(a_raiz(arbol), clave);
                    if (sujeto == NULL) {
                        printf("\n>! Clave inexistentes, ingrese la clave de un nodo existente . . .\n");
                        existe = false;
                    }

                    else printf("\n>> Nodo asignado: clave(%d) direccion(%p)\n", n_recuperar(sujeto)->clave, sujeto);

                } while (!existe);

                printf("\n<< ");
                system("pause");
            } break;

            case 2 : {
                printf("\n// Resolviendo . . .\n");

                if (a_raiz(arbol) == sujeto) printf("\n>> El nodo sujeto es la raiz del arbol, no tiene nodo padre . . .\n");
                else                         printf("\n>> La clave del nodo padre del nodo sujeto %d es %d\n", n_recuperar(sujeto)->clave, n_recuperar(n_nodoPadre(arbol, sujeto))->clave);

                n_mostrarHijos(sujeto);                        

                n_mostrarHermano(arbol, sujeto);                

                printf("\n>> El nodo sujeto clave %d se encuentra en el nivel %d\n", n_recuperar(sujeto)->clave, n_nivelNodo(arbol, sujeto));

                printf("\n>> La altura del (sub)arbol que tiene al nodo sujeto como raiz es de %d nodo/s\n", n_alturaSubArbol(sujeto));

                n_mostrarNivel(arbol, sujeto);                  

                printf("\n<< ");
                system("pause");
            } break;

            default: break;
        }
    }
    printf("\n ----------------------------------------------------------");
    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - // Funciones auxiliares

ArbolBinario CreandoArbol(ArbolBinario a) {
    a = a_crear();
    CargarSubArbol(a, NULL, 0);
    return a;
}

void CargarSubArbol(ArbolBinario A, NodoArbol N, int sa){
    TipoElemento contenido;
    NodoArbol nuevo_nodo;
    int n;
    bool b;

    if(!a_es_lleno(A)){
        b = IngresoEntero(A, &n);

        if (b){
            contenido = te_crear(n);

            if      (sa == -1) nuevo_nodo = a_conectar_hi(A, N, contenido);
            else if (sa == 1)  nuevo_nodo = a_conectar_hd(A, N, contenido);
            else               nuevo_nodo = a_establecer_raiz(A, contenido);

            CargarSubArbol(A, nuevo_nodo, -1);
            CargarSubArbol(A, nuevo_nodo, 1);
        }
    }
}

bool IngresoEntero(ArbolBinario a, int* n){
    char filtro[MAX];
    bool resultado, valido;
    int aux;
    *n = 0;

    do {
        resultado = true;
        valido = true;
        printf("\n%d << Ingrese una clave numerica o '.' para nulo: ", __LINE__);
        fgets(filtro, MAX, stdin);

        if (strrchr(filtro, '.') != NULL) {
            resultado = false;
            if (a_es_vacio(a)) {
                printf("\n>! El arbol esta vacio, ingrese una clave para el nodo raiz . . .\n");
                valido = false;
            }
        }

        else aux = EntradaEntera(filtro, 0, -100000, 100000);

        if (BuscarNodo(a_raiz(a), aux) != NULL && resultado) {
            printf("\n>! La clave ya existe en el arbol, ingrese una clave unica . . .\n");
            valido = false;
        }

        else *n = aux;

    } while (!valido);

    return resultado;
}

void buscandoClaveRecursivamente(NodoArbol n, int clave, bool *encontrado, NodoArbol *retorno) {
    if (n != NULL) {
        if (n->datos->clave == clave) {
            *encontrado = true;
            *retorno = n;
        }

        else {
            buscandoClaveRecursivamente(n_hijoizquierdo(n), clave, encontrado, retorno);
            buscandoClaveRecursivamente(n_hijoderecho(n), clave, encontrado, retorno);
        }
    }
}

NodoArbol BuscarNodo(NodoArbol n, int clave) {
    if (n == NULL) return NULL;
    bool encontrado = false;
    NodoArbol retorno = NULL;
    buscandoClaveRecursivamente(n, clave, &encontrado, &retorno);
    if (!encontrado) return NULL;
    else             return retorno;
}