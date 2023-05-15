#include <stdio.h>
#include <stdlib.h>

#include"colas.h"
#include "tipo_elemento.h"
#include"Validacion.h"

void atender(Cola c1, Cola c2, Cola  c3, int Q)
{   
    Cola C1Aux, C2Aux, C3Aux;
    C1Aux = c_crear();
    C2Aux = c_crear();
    C3Aux = c_crear();

    TipoElemento X;
    
    int Fin = 0;   //Determina cuando sale del while principa;.
    int T1, T2, T3, Q1, Q2, Q3, Cli1, Cli2, Cli3;
    
    if (!c_es_vacia(c1))
    {
        X = c_recuperar(c1); 
        T1 = X->clave;          //La variable T es el tiempo de atencion que necesita cada cliente, hay un T para cada cola 1, 2 y 3.
        c_encolar(C1Aux,X);     //Guardo en una cola auxilliar para no perder la cola original.
    }

    if (!c_es_vacia(c2))
    {
        X = c_recuperar(c2);
        T2 = X->clave;
        c_encolar(C2Aux,X);
    }

    if (!c_es_vacia(c3))
    {   
        X = c_recuperar(c3);
        T3 = X->clave;
        c_encolar(C3Aux,X);
    }

    Cli1= 1; //Cli guarda el numero del cliente que esta siendo atendido, hay un Cli para cada cola 1, 2 y 3.
    Cli2= 1;
    Cli3= 1;

    while (Fin != 1)
    {
        if(!c_es_vacia(c1)) //Cola 1
        {
            Q1 = Q;  // Guardo el Q para poder modificarlo en cada cola sin perderlo.
            while(Q1 > 0 && !c_es_vacia(c1))  // Mientras Q1 tenga tiempo para atender y si hay clientes en la cola se seguira atendiendo.
            {
                if(Q1 >= T1)  // pregunto si tengo mas tiempo o el tiempo justo del que necesito para atender al cliente. 
                {
                    Q1 = Q1 - T1; // resto el tiempo de atencion al cliente, para obtener el tiempo restante en la cola.
                    c_desencolar(c1);
                    printf("Cliente %d Cola 1,\n", Cli1); // informo el cliente que fue atendido
                    Cli1 ++;    
                    X = c_recuperar(c1); // recupero el siguente cliente;
                    if (X != NULL)
                    {
                        T1 = X->clave;
                        c_encolar(C1Aux,X);
                    }
                }else   // si el tiempo del cliente es mayor al tiempo de atencion, resto el tiempo de atencion al cliente y paso a la siguiente cola.
                {
                    T1 = T1 - Q1;
                    Q1 = 0;
                }
            }       
        }
        // repito el proceso en las 2 colas restantes.
        if(!c_es_vacia(c2)) //Cola 2
        {
            Q2 = Q;
            while(Q2 > 0 && !c_es_vacia(c2))
            {
                if(Q2 >= T2)
                {
                    Q2 = Q2 - T2;
                    c_desencolar(c2);
                    printf("Cliente %d Cola 2,\n", Cli2);
                    Cli2 ++;
                    X = c_recuperar(c2);
                    if (X != NULL)
                    {
                        T2 = X->clave;
                        c_encolar(C2Aux,X);
                    }
                }else 
                {
                    T2 = T2 - Q2;
                    Q2 = 0;
                }
            }       
        }

        if(!c_es_vacia(c3)) //Cola 3
        {
            Q3 = Q;
            while(Q3 > 0 && !c_es_vacia(c3))
            {
                if(Q3 >= T3)
                {
                    Q3 = Q3 - T3;
                    c_desencolar(c3);
                    printf("Cliente %d Cola 3,\n", Cli3);
                    Cli3 ++;
                    X = c_recuperar(c3);
                    if (X != NULL)
                    {
                        T3 = X->clave;
                        c_encolar(C3Aux,X);
                    }
                }else 
                {
                    T3 = T3 - Q3;
                    Q3 = 0;
                }
            }       
        }

        if(c_es_vacia(c1) && c_es_vacia(c2) && c_es_vacia(c3)) {Fin = 1;};

    }

    //Recupero las pilas originales
     while (!c_es_vacia(C1Aux))
    {
        X = c_desencolar(C1Aux);
        c_encolar(c1, X);
    }
     while (!c_es_vacia(C2Aux))
    {
        X = c_desencolar(C2Aux);
        c_encolar(c2, X);
    }
     while (!c_es_vacia(C3Aux))
    {
        X = c_desencolar(C3Aux);
        c_encolar(c3, X);
    }
}


void main()
{
    int Q = 5;

    Cola c1, c2 ,c3;
    c1= c_crear();
    c2= c_crear();
    c3= c_crear();

    TipoElemento X;
    
    int Cant, Valor, i;
    char filtro[100];

    printf("\n Ingrese el tamanio de la Cola 1: ");
    fgets(filtro, 100, stdin);
    Cant = EntradaEntera(filtro, 0, 0, 100);
    
    i = 1;
    while (i <= Cant) {
        printf("\n Ingrese el tiempo de atencion para el cliente %d de la Cola 1:", i);
        fgets(filtro, 100, stdin);
        Valor = EntradaEntera(filtro, 0, 1, 1000);
        
            X = te_crear(Valor);
            c_encolar(c1, X);
            i = i + 1;     
    }
    
    printf("\n Ingrese el tamanio de la Cola 2: ");
    fgets(filtro, 100, stdin);
    Cant = EntradaEntera(filtro, 0, 0, 100);
    
    i = 1;
    while (i <= Cant) {
        printf("\n Ingrese el tiempo de atencion para el cliente %d de la Cola 2:", i);
        fgets(filtro, 100, stdin);
        Valor = EntradaEntera(filtro, 0, 1, 1000);
        
            X = te_crear(Valor);
            c_encolar(c2, X);
            i = i + 1;     
    }

    printf("\n Ingrese el tamanio de la Cola 3: ");
    fgets(filtro, 100, stdin);
    Cant = EntradaEntera(filtro, 0, 0, 100);
    
    i = 1;
    while (i <= Cant) {
        printf("\n Ingrese el tiempo de atencion para el cliente %d de la Cola 3:", i);
        fgets(filtro, 100, stdin);
        Valor = EntradaEntera(filtro, 0, 1, 1000);
        
            X = te_crear(Valor);
            c_encolar(c3, X);
            i = i + 1;     
    }
    
    printf("\n Ingrese el tiempo Q para atender cada cola: ");
    fgets(filtro, 100, stdin);
    Q = EntradaEntera(filtro, 0, 1, 1000);
    
    printf("--------------------------------------------\n");
    printf("Resultado:\n");
    atender(c1, c2, c3, Q);
    printf("--------------------------------------------\n");
    printf("Q = %d\n", Q);
    printf("Colas ingresadas: \n");
    
    if(!c_es_vacia(c1)){c_mostrar(c1);}else{printf("No habia nadie en la cola 1\n");}
    printf("\n");
    if(!c_es_vacia(c2)){c_mostrar(c2);}else{printf("No habia nadie en la cola 2\n");}
    printf("\n");
    if(!c_es_vacia(c3)){c_mostrar(c3);}else{printf("No habia nadie en la cola 3\n");}
    
}
