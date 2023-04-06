#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int terminoSeridFibonacci (int n) {
if (n == 0){
    return 0; 
}
else if ( n == 1)
{
    return 1;
}
else
{
return (terminoSeridFibonacci(n-1) + terminoSeridFibonacci(n-2));
}
}

int main (){
int n = 0;
bool aux = false;
printf ("ingrese el termino de la serie fibonacci que desee saber: \n");   
while (aux == false){ 
scanf ("%i",&n);  
    if (n >= 0) {
        printf ("termino de la serie fibonacci: %i  \n",terminoSeridFibonacci(n));
        aux = true;        
    }   
    else {
        printf ("El numero ingresado no pude ser negativo, por favor ingrese otro: \n");           
    }
}
system("pause");
} 
