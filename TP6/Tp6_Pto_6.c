#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#include "tabla_hash.h"
#include "listas.h"
#include "tipo_elemento.h"
#include "Validacion.h"

static const int TAMANIO_MAXIMO = 110;
static const int NRO_PRIMO = 107;


int hashFunctionNroPrimo(int a) {
    return (a % NRO_PRIMO);
}

int esFechaValida(int anio, int mes, int dia) {
    time_t T;
    T = time(NULL);
    struct tm *fecha;
    fecha = localtime(&T);

     if (anio > fecha->tm_year + 1900)
        return 0;
    else if (anio == fecha->tm_year + 1900) {
        if (mes > fecha->tm_mon + 1)
            return 0;
        else if (mes == fecha->tm_mon + 1) {
            if (dia > fecha->tm_mday)
                return 0;
        }
    }

    if (anio < 2020 || anio > 2023 || mes < 1 || mes > 12 || dia < 1) {
        return 0;  
    }

    int diasEnMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};  

    
    if ((anio % 4 == 0 && anio % 100 != 0) || anio % 400 == 0) {
        diasEnMes[1] = 29;  
    }

    if (dia > diasEnMes[mes - 1]) {
        return 0;  
    }

    return 1;  
}

int ValidarFecha(char *FechaStr){
    int i, CodigoHash = 0,Dia = 0, Mes = 0, Anio = 0 ,Valida;
    char C;

    if(strlen(FechaStr) > 10){
        return -1;
    }

    for ( i = 0; i < strlen(FechaStr); i++){
        C = FechaStr[i];
        if(C >= '0' && C <= '9'){
            if(i<2){
                if(i == 0){
                    Dia = Dia + (C - 48);
                    Dia = Dia * 10;
                }else{Dia = Dia + (C - 48);}

            }else if(i<5){
                if(i == 3){
                    Mes = Mes + (C - 48);
                    Mes = Mes * 10;
                }else{Mes = Mes + (C - 48);}
            }else{
                if(i == 9){
                    Anio = Anio + (C - 48);    
                }else{
                    Anio = Anio + (C - 48);
                    Anio = Anio * 10; 
                }
            }
        }else if((i == 2 || i == 5) && C != '/'){
            return -1;
        }else if((C < '0' || C > '9') && C != '/'){
            return -1;
        }
    }

    //Validacion de la fecha.
    Valida = esFechaValida(Anio, Mes, Dia);
    if(Valida == 0){
        return -1;
    }else{
        CodigoHash = CodigoHash + Anio;
        CodigoHash = CodigoHash * 100;
        CodigoHash = CodigoHash + Mes;
        CodigoHash = CodigoHash * 100;
        CodigoHash = CodigoHash + Dia;
    }

    return CodigoHash;
    
}


void CargarDatos(TablaHash Vacunados){
    TipoElemento X, P, R, T;
    Lista VacPorFecha;
    VacPorFecha = l_crear();
    const char s[2] = ",";
    char DNI[15], NomYApe[30],Fecha[15] ,*Datos, *v, *DNIVal, DatosVal[60];
    char PermitidosDNI[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '\0'};
    int i, CodHash;
    bool NomCorrecto =false;
    Datos = calloc(60,sizeof(char));
    printf("(El ingreso de personas va del anio 2020 hasta el dia de hoy)\n");
    printf("Ingrese la fecha de vacunacion de la siguiente manera (dd/mm/yyyy):\n");
    gets(Fecha);
    fflush(stdin);

    //Validar fecha y generar el codigo hash
    CodHash = ValidarFecha(Fecha);

    while(CodHash == -1){
        printf("Fecha Invalida\n");
        printf("(El ingreso de personas va del anio 2020 hasta el dia de hoy)\n");
        printf("Ingrese la fecha de vacunacion de la siguiente manera (dd/mm/yyyy):\n");
        gets(Fecha);
        fflush(stdin);
        CodHash = ValidarFecha(Fecha);
    }


    printf("Ingrese el DNI de la persona vacunada:\n");
    gets(DNI);
    fflush(stdin);
    while(CadenaValida(DNI, PermitidosDNI) == 0 || strlen(DNI)< 1 || strlen(DNI)> 9){
        printf("Ingrese un DNI Valido:\n"); 
        gets(DNI);
        fflush(stdin); 
    }

    if (th_recuperar(Vacunados,CodHash) != NULL){
        R = th_recuperar(Vacunados, CodHash);
        for ( i = 1; i <= l_longitud(R->valor) ; i++)
        {
            T = l_recuperar(R->valor,i);
            strcpy(DatosVal, T->valor);
            DNIVal = strtok(DatosVal, s);
            DNIVal = strtok(NULL, s);
            if(strcmp(DNI, DNIVal) == 0){
                printf("La persona con el DNI ingresado ya fue cargada para esta fecha\n");
                system("pause");
                return;
            }
        } 
    }

    printf("Ingrese el nombre y apellido de la persona vacunada:\n");
    gets(NomYApe);
    fflush(stdin);
    v = NomYApe;

    while(!NomCorrecto){
        NomCorrecto = true;
        while(*v != '\0' && NomCorrecto){
            if(*v >= 'A' && *v <= 'z'){
                NomCorrecto = true;
                if(*v > 'Z' && *v < 'a'){
                    NomCorrecto = false;
                }
            }else if(*v < 'A' || *v > 'z'){
                NomCorrecto = false;
                if(*v == ' '){NomCorrecto = true;}
            } 
            v++;
        }
        if(!NomCorrecto){
            printf("El nombre ingresado tiene caracteres no validos, ingrese nuevamente.\n");
            printf("Ingrese el nombre y apellido de la persona vacunada:\n");
            gets(NomYApe);
            fflush(stdin);
            v = NomYApe;
            }

    }



    strcat(Datos, Fecha);
    strcat(Datos, s);
    strcat(Datos, DNI);
    strcat(Datos, s);
    strcat(Datos, NomYApe);
    
    X = te_crear_con_valor(CodHash, Datos);
    
    if (th_recuperar(Vacunados,X->clave) == NULL){
        P = te_crear_con_valor(X->clave, VacPorFecha);
        l_agregar(P->valor,X);
        th_insertar(Vacunados,P);
    }else{
        P = th_recuperar(Vacunados, X->clave);
        l_agregar(P->valor,X);
    }
    system("cls");
    printf("Datos cargados correctamente\n"); 
    system("pause");
}

void BuscarVacunadosPorFecha(TablaHash Vacunados){
    TipoElemento X, X2;
    int i, Codigo;
    char Fecha[15];
    char Datos[60], *DNI, *NomYApe,*Fe;
    const char s[2] = ",";
    Fe = calloc(15,sizeof(char));
    DNI = calloc(15,sizeof(char));
    NomYApe = calloc(30,sizeof(char));
    printf("(El ingreso de personas va del anio 2020 hasta el dia de hoy)\n");
    printf("Ingrese la fecha de vacunacion de la siguente manera (dd/mm/yyyy):\n");
    gets(Fecha);
    fflush(stdin);

    Codigo = ValidarFecha(Fecha);
    while(Codigo == -1){
        printf("Fecha Invalida.\n");
        printf("(El ingreso de personas va del anio 2020 hasta el dia de hoy)\n");
        printf("Ingrese la fecha de vacunacion de la siguiente manera (dd/mm/yyyy):\n");
        gets(Fecha);
        fflush(stdin);
        Codigo = ValidarFecha(Fecha);    
    }
    
    X = th_recuperar(Vacunados,Codigo);

    if(X == NULL){
        printf("No hay vacunados en la fecha ingeresada\n");
    }else{
    
        for ( i = 1; i <= l_longitud(X->valor) ; i++)
        {
            X2 = l_recuperar(X->valor,i);
            printf("--------------------------------------\n");
            strcpy(Datos, X2->valor);
            Fe = strtok(Datos, s);
            DNI = strtok(NULL, s);
            NomYApe = strtok(NULL, s);

            printf("Fecha: ");
            printf("%s\n", Fe);
            printf("DNI: ");
            printf("%s\n", DNI);
            printf("Nombre y apellido: ");
            printf("%s\n", NomYApe);
           
        }
    }
    printf("--------------------------------------\n");
    system("pause");
}

void main(){
    bool MENU = true;
    char tecla;
    char F[15];
    int Valor, borrar;
    TablaHash Vacunados;
    Vacunados = th_crear(TAMANIO_MAXIMO, &hashFunctionNroPrimo);
    
    while(MENU){
        printf("     \n~~~~~~~~~~~~~~~~~~~~~~~MENU~~~~~~~~~~~~~~~~~~~~~~~     \n");  
        printf("1- Cargar datos de los vacunados\n");
        printf("2- Buscar vacunados por fecha\n");
        printf("3- Mostrar tabla hash\n");
        printf("0- SALIR\n");

        printf("Presione un nuero para elejir una opcion\n");
            scanf("%c", &tecla);
            fflush(stdin);
        if(tecla >= '0' && tecla <= '3'){
            if(tecla == '1'){
                system("cls");
                CargarDatos(Vacunados);    
            }else if(tecla == '2'){
                system("cls");
                BuscarVacunadosPorFecha(Vacunados);   

            }else if(tecla == '3'){
                system("cls");
                th_mostrar(Vacunados);
                system("pause");
            }else if(tecla == '0'){MENU = false;}   
        }
        tecla = ' '; 
        fflush(stdin);
        system("cls");
    }


}
    

    
