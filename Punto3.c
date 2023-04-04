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
printf ("termino referido: %i  \n",terminoSeridFibonacci(6));
system("pause");

} 
