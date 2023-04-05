#include <stdio.h>
#include <stdlib.h>

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
printf ("ingrese el termino de la serie fibonacci que desee saber: \n");
scanf ("%i",&n);  

printf ("termino de la serie fibonacci: %i  \n",terminoSeridFibonacci(n));
system("pause");

} 
