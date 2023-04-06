#include "TP1_Validacion.h"
#include <stdio.h>
/*4. Dados los números enteros m y n, construir una función recursiva que devuelva el
cociente de ambos, calculando el mismo mediante restas sucesivas. Se deberá tener
en cuenta que en el caso de que la división no sea exacta, se devolverán hasta 4 cifras
decimales (si es necesario).
Ejemplos:
division (10,2) => 5
division (22,3) => 7,3333 */
float division(int n,int m,float c,float r){
    float resultado;
    while (m<n)
    {
        n=n-m;
        r=r+c;
    }
    if(n==m){
        r+=c;
        resultado= r;}
    else if (r>=1||r==0){
        c=0.1;
        resultado=(r+=division(n*10,m,c,0));}
    else if (r>=0.1){
        c=0.01;
        resultado=(r+=division(n*10,m,c,0));}
    else if (r>=0.01){
        c=0.001;
        resultado=(r+=division(n*10,m,c,0));}
    else if (r>=0.001){
        c=0.0001;
        resultado=(r+=division(n*10,m,c,0));}
    else if (r>=0.0001){
        resultado= r;}
    return resultado;
}
int main(){
    int n,m;
    float r=0;
    char filtro[100];
    for (int i = 0 ; i < 100 ; i++) filtro[i] = '\0';
    printf("\n << Ingrese un numero entero: ");
    fgets(filtro, 100, stdin);
    n= EntradaEntera(filtro, 1, 0, 0);
    fflush(stdin);
    printf("\n << Ingrese otro numero entero: ");
    for (int i = 0 ; i < 100 ; i++) filtro[i] = '\0';
    fgets(filtro, 100, stdin);
    m = EntradaEntera(filtro, 1, 0, 0);
    fflush(stdin);
    printf(" >> Division: %10.4f\n", division(n,m,1.0,r));
    return 0;
}
