

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
    else if (r>=1){
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
    printf("ingrese un numero:");
    scanf("%i",&n);
    printf("ingrese otro numero:");
    scanf("%i",&m);
    float a=division(n,m,1.0,r);
    printf("%f",a);
    return 0;
}