#include <stdio.h>
#include<stdlib.h>
#include <string.h>

char *Puntos(char C[]){
    int largo = strlen(C);
    int i;
    char c1[25];
    char c2[25];
    strcpy(c2,".");
    if (largo < 4){ //Caso base
        
        return C;	
        
    }else{
		
        for (i=0;i<largo-3;i++){ //guardo todo el string menos los ultimos 3 caracreres en c1
            c1[i]=C[i];
        }    
        c1[largo-3]='\0';
        for (i=0;i<largo-1;i++){  //guardo los tres ultimos caracteres en c2
            c2[i+1]=C[largo - 3 + i];
        }
        c2[4]='\0';

        strcpy(C,c1);
        return strcat(Puntos(C),c2); //concateno llamando a la funcion recursiva

    }
}    



int main(){
    int i;
    char permitidos[12] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-', '\0'};
    int validacion = 1;
    char c[16];
    memset(c, 16, '\0');
    printf("\n << Coloque un numero para que el programa incerte los puntos de los miles (solo se tomara hasta un maximo de 15 caracteres):");

    while(validacion == 1){ //si la cadena ingresada es erronea, pide una nueva hasta que sea valida.
		validacion=0;
		fgets(c, 16, stdin);
		c[strcspn(c, "\n")] = '\0';
		for (i=0;i<(strlen(c));i++){	//Valido que la cadena solo tenga numeros.
			if (strrchr(permitidos,  c[i]) == NULL){
				validacion=1;
				i= strlen(c);
                memset(c, 16, '\0');
				printf("\n >! Entrada invalida; valor fuera de rago");
				printf("\n << Coloque un numero para que el programa incerte los puntos de los miles (solo se tomara hasta un maximo de 15 caracteres): ");
			}
		} 
		      
	}
	while (c[0]=='0' &&  strlen(c)>1){		//Elimino el 0 si es el primer valor de la cadena
		for (i=0;i<=(strlen(c));i++){
			c[i]=c[i+1];
		}
	}
	printf("%s",Puntos(c));
}


/*
int main(){
    int i;
    int validacion = 1;
    char c[16];
    printf("\n << Coloque un numero para que el programa incerte los puntos de los miles (solo se tomara hasta un maximo de 15 caracteres):");

    while(validacion == 1){ //si la cadena ingresada es erronea, pide una nueva hasta que sea valida.
		validacion=0;
		scanf("%15s",c);
		   
		for (i=0;i<(strlen(c));i++){	//Valido que la cadena solo tenga numeros.
			if (c[i]<'0' || c[i]>'9'){
				validacion=1;
				i= strlen(c);
				printf("Solo se admiten numeros!\n");
				printf("Coloque un numero para que el programa incerte los puntos de los miles (solo se tomara hasta un maximo de 15 caracteres):\n");
			}
		} 
		      
	}
	while (c[0]=='0' &&  strlen(c)>1){		//Elimino el 0 si es el primer valor de la cadena
		for (i=0;i<=(strlen(c));i++){
			c[i]=c[i+1];
		}
	}
	printf("%s",Puntos(c));
}
*/
