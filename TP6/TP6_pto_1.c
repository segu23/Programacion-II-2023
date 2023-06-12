#include "stdlib.h"
#include "stdio.h"
#include "tipo_elemento.h"
#include "tabla_hash.h"

#include "tabla_hash_zona_overflow.c"
#include "tipo_elemento.c"
#include "listas_punteros.c"

int calcularHash(int clave){
    return clave%10;
}

int main(){
    TablaHash hashTable = th_crear(10, *calcularHash);
    th_mostrar(hashTable);
    th_insertar(hashTable, te_crear_con_valor(631, 45));
    th_mostrar(hashTable);
    th_insertar(hashTable, te_crear(130));
    th_mostrar(hashTable);
    th_insertar(hashTable, te_crear_con_valor(611, 23));
    th_mostrar(hashTable);
    th_insertar(hashTable, te_crear(417));
    th_mostrar(hashTable);
    th_insertar(hashTable, te_crear(534));
    th_mostrar(hashTable);
    th_insertar(hashTable, te_crear(965));
    th_mostrar(hashTable);
    th_insertar(hashTable, te_crear(394));
    th_mostrar(hashTable);
    TipoElemento te = th_recuperar(hashTable, 631);
    printf("%i", te->valor);
    TipoElemento te2 = th_recuperar(hashTable, 611);
    printf("%i", te2->valor);
    return 0;
}