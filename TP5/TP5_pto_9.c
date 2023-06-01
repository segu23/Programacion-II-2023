/* GLORIA UT DEUS
 * conatus me
 */

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include"Validacion.h"
#include"arbol_binario.h"
#include"arboles_utilidades.h"
#include"arbol_avl.h"
#include"nodo.h"

#define MAX_BUFFER 101

int potencia (int base, int exponente) {

    if (exponente == 0) {

        return 1;

    }

    int resultado = base;

    if (exponente > 1) {

        for (int i = 2; i <= exponente; i++) {

            resultado *= base;

        }

    }

    return resultado;

}

//Devuelve el exponente al cual debe ser elevada la base para obtener el resultado (Pasa al mayor entero siguiente válido)
int antilogaritmo (int resultado, int base) {

    int exponente = 0;

    while (potencia(base, exponente) < resultado) {

        exponente++;

    }

    return exponente;
}

void cargar_buffer (char buffer[]) {

    for (int i = 0; i < MAX_BUFFER; i++) {

        buffer[i] = '\0';

    }

}

bool ingresoEntero(int* n, bool *letra){
    char s[10];
    *letra = false;
    bool resultado = true;
    *n=0;
    printf("Ingrese una clave numerica o '.' para nulo: ");
    scanf("%s", s);
    fflush(stdin);
    if (s[0]=='.'){
        resultado = false;
    }else{
        for (int i = 0; s[i] != '\0'; i++) {
            if ((s[i]>='0')&&(s[i]<='9')){
                *n = *n * 10 + (s[i] - 48);
            }else{*letra = true;}
        }
    }
    return resultado;
}

bool ComprobarRepetidos(ArbolBinario A, NodoArbol N, int n){
    bool b = false;
    if(!a_es_vacio(A) ){
        if(n_recuperar(N)->clave == n){
            b = true;
            return b;
        }else{
            if(n_hijoderecho(N) != NULL){b = ComprobarRepetidos(A,n_hijoderecho(N), n);}
            if(b == false){
                if(n_hijoizquierdo(N) != NULL){b = ComprobarRepetidos(A,n_hijoizquierdo(N), n);}
            }
            return b;
        }
    }
    return b;
}

void Cargar_SubArbol(ArbolBinario A, NodoArbol N, int sa){
    TipoElemento X;
    NodoArbol N1;
    int n;
    bool b, letra;
    letra = false;
    if(!a_es_lleno(A)){
        b= ingresoEntero(&n, &letra);
        while((ComprobarRepetidos(A ,a_raiz(A), n) && b) || letra ){
            if (letra){
                printf("Valor invalido, ingrese un numero.\n");
            }else{printf("El valor ingresado ya se encuentra en el arbol, ingrese otro.\n");}
            b= ingresoEntero(&n, &letra);
        }

        if (b){
            X= te_crear(n);

            if(sa == -1) N1 = a_conectar_hi(A, N, X);
            else if(sa == 1) N1 = a_conectar_hd(A, N, X);
            else N1 = a_establecer_raiz(A, X);

            Cargar_SubArbol(A, N1, -1);
            Cargar_SubArbol(A, N1, 1);
        }
    }
}

//Funcion para la carga del arbol
void cargar_arbol_binario(ArbolBinario A){
    Cargar_SubArbol(A, NULL, 0);
}


//Retornar una lista con todos los nodos terminales u hojas.
Lista hojaslista(NodoArbol N, Lista ret){
    TipoElemento x;
    if (N!=NULL){
        if ((n_hijoizquierdo(N)==NULL)&&(n_hijoderecho(N)==NULL)){
            x=n_recuperar(N);
            l_agregar(ret,x);
        }
        hojaslista(n_hijoizquierdo(N),ret);
        hojaslista(n_hijoderecho(N),ret);
    }
    return ret;
}
Lista hojas(ArbolBinario a){
    Lista ret;
    ret=l_crear();
    ret=hojaslista(a_raiz(a),ret);
    return ret;
}

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
    else if (a_raiz(a) == n) return 0;

    int nivel = -1;
    buscandoNivelRecursivamente(a_raiz(a), n, &nivel, 0);

    return nivel;
}

int obtener_altura_binario (ArbolBinario binario) {

    int altura = 0;

    Lista l_hojas = hojas(binario);

    if (l_es_vacia(l_hojas)) {

        free(l_hojas);
        return altura;

    } else {

        Iterador ite_hojas = iterador(l_hojas);

        int clave_mayor = siguiente(ite_hojas)->clave;

        int nivel = -1;
        buscandoNivelRecursivamente(a_raiz(binario), clave_mayor, &nivel, 0);
        int altura_mayor = nivel;

        int clave_aux;
        int altura_aux;

        while (hay_siguiente(ite_hojas)) {

            clave_aux = siguiente(ite_hojas)->clave;
            int nivel = -1;
            buscandoNivelRecursivamente(a_raiz(binario), clave_aux, &nivel, 0);
            altura_aux = nivel;

            if (altura_aux > altura_mayor) {

                altura_mayor = altura_aux;

            }

        }

        free(ite_hojas);

    }

    free(l_hojas);

    return altura;

}

void cargar_avl_por_binario (ArbolAVL avl, ArbolBinario binario) {

    Iterador nodos_binarios = iterador_in_orden(a_raiz(binario));

    TipoElemento aux;

    while (hay_siguiente(nodos_binarios)) {

        aux = siguiente(nodos_binarios);
        avl_insertar(avl, te_crear(aux->clave));

    }

    free(nodos_binarios);
}

int obtener_altura_avl (ArbolAVL avl) {

    int altura_avl = -1;

    int cant_nodos_avl = avl_cantidad_elementos(avl);

    int limite_nivel = antilogaritmo(TAMANIO_MAXIMO, 2);

    if ((cant_nodos_avl + 1) == (potencia(2, limite_nivel - 1))) {

        altura_avl = limite_nivel - 1;

    } else {

        altura_avl = limite_nivel;

    }

    return altura_avl;
}

void comparar_alturas (int altura_binario, int altura_avl) {

    printf("\n\nAltura árbol binario: %i\n", altura_binario);
    printf("Altura árbol AVL: %i\n", altura_avl);

    printf("\nResultado: ");

    if (altura_binario > altura_avl) {

        printf("El Árbol binario es el de mayor altura\n");

    } else if (altura_binario < altura_avl) {

        printf("El Árbol AVL es el de mayor altura\n");

    } else {

        printf("Ambos árboles tienen igual altura.\n");

    }

}

void procesar_algoritmo () {

    //crear y cargar árbol binario, mostrar con el metodo que muestra los nodos ordenados
    ArbolBinario binario = a_crear();
    cargar_arbol_binario(binario);
    printf("\nEl árbol binario resulta:\n");
    mostrar_arbol_binario(a_raiz(binario), IN_ORDEN);

    //Obtener altura del arbol binario (lo dejo vacio por ahora)
    int altura_binario = obtener_altura_binario(binario);

    //Crear AVL a partir del arbol binario
    ArbolAVL avl = avl_crear();
    cargar_avl_por_binario(avl, binario);
    printf("\nTras generar el árbol AVL, este resulta:\n");
    mostrar_arbol_binario(avl_raiz(avl), IN_ORDEN);
    printf("\nEl árbol binario se mantiene como fue generado:\n");
    mostrar_arbol_binario(a_raiz(binario), IN_ORDEN);

    //obtener altura AVL
    int altura_avl = obtener_altura_avl(avl);

    //Comparar alturas
    comparar_alturas(altura_binario, altura_avl);

    free(binario);
    free(avl);
}

void mensaje_bienvenida () {

    printf("\n--TP5-PTO9-ARBOL-BINARIO-A-AVL--\n\n");

}

void mostrar_menu () {

    printf("\n-------MENU-------\n");
    printf("1. Algoritmo\n");
    printf("2. Complejidad y detalles de implementación\n");
    printf("3. Salir\n");

}

int recibir_opcion () {

    int opcion = 0;

    char buffer[MAX_BUFFER];
    cargar_buffer(buffer);

    printf("\nIngrese su opcion[1, 2 o 3]: ");
    fgets(buffer, 100, stdin);
    opcion = EntradaEntera(buffer, 0, 1, 3);

    return opcion;
}

void mostrar_complejidad () {

    printf("\nLa complejidad algorítmica por tiempo de ejecución es O()\n");
    printf("Dado que la consigna dice, cito '...a partir de un árbol binario sin un orden determinado'\n");
    printf("La creación de dicho árbol binario  ");

}

void procesar_menu (int opcion) {

    switch (opcion) {

        case 1:
            procesar_algoritmo();
        break;
        case 2:
            mostrar_complejidad();
        break;
        case 3:
            return;
        break;
        default:
            printf("Opcion ingresada no valida.\n");
        break;

    }

}

void despedida () {

    printf("\n¡Tenga un buen día!\n");

}

int main () {

    mensaje_bienvenida();
    mostrar_menu();
    int opcion = recibir_opcion();
    procesar_menu(opcion);
    despedida();

    return 0;
}
