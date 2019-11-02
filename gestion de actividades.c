#include "headers.h"

///Cuerpo de las funciones del Sub-menu 2 de Menu Central de Administracion - Gestion de Actividades:
void CargarActividadesNuevas(char asociados[10],char deportes[10],char pagos[10],celda ArrayActs[100],nodo* listaSocios)
{
    FILE* archi;
    celda nueva;
    celda aux;
    char control='s';

    while(control=='s')
    {
        archi=fopen("deportes","a+b");
        system("cls");
        printf("A continuacion rellene los campos:\n\n");
        printf("Actividad/Deporte: ");
        fflush(stdin);
        gets(nueva.actividad);
        while(fread(&aux,sizeof(celda),1,archi)>0)
        {
            while(strcmp(nueva.actividad,aux.actividad)==0)
            {
                system("cls");
                system("color 0c");
                printf("Error! Actividad ya existente.\n\n");
                system("pause");
                system("cls");
                system("color 07");
                control=Preguntar();
                if(control!='s')
                {
                    MenuGestionActividades(asociados,deportes,pagos,ArrayActs,listaSocios);
                }
                system("color 07");
                printf("Actividad/Deporte: ");
                fflush(stdin);
                gets(nueva.actividad);
                fseek(archi,0,SEEK_SET);
            }
        }
        printf("Tarifa mensual: ");
        scanf("%f",&nueva.tarifa);
        printf("Horario: ");
        fflush(stdin);
        gets(nueva.horario);
        nueva.lista=inicLista();
        nueva.estado='a';
        fwrite(&nueva,sizeof(celda),1,archi);
        fclose(archi);
        control=Preguntar();
    }
}
void ModificarActividad(char asociados[10],char deportes[10],char pagos[10],celda ArrayActs[100],nodo* listaSocios)
{
    int i=0;
    char act[30];
    int validos;
    int opcion=0;
    char control='s';

    validos=PasarDeportesAvector(deportes,ArrayActs);
    system("cls");
    printf("Ingrese la actividad/deporte que desea modificar.\n\n");
    printf("Actividad/Deporte: ");
    fflush(stdin);
    gets(act);
    while((i<validos)&&(strcmp(act,ArrayActs[i].actividad)!=0))
    {
        i++;
    }

    if(strcmp(act,ArrayActs[i].actividad)==0)
    {
        while(control=='s')
        {
            system("cls");
            printf("Actividad/Deporte: %s\n",ArrayActs[i].actividad);
            printf("Tarifa mensual: %.3f\n",ArrayActs[i].tarifa);
            printf("Horario: %s\n",ArrayActs[i].horario);
            printf("Estado: activo\n");
            printf("\n---------------------------------------\n");
            printf("\n\nDatos permitidos para modificar:\n\n[1]Tarifa mensual.\n[2]Horario.\n[3]Volver");
            printf("\n\nSeleccione la opcion que desea modificar: ");
            scanf("%i",&opcion);
            switch(opcion)
            {
            case 1:
                printf("\nTarifa mensual: ");
                scanf("%f",&ArrayActs[i].tarifa);
                system("cls");
                system("color 0a");
                printf("La actividad se ha modificado correctamente!\n\n");
                system("pause");
                system("cls");
                system("color 07");
                break;
            case 2:
                printf("\nHorario: ");
                fflush(stdin);
                gets(ArrayActs[i].horario);
                system("cls");
                system("color 0a");
                printf("La actividad se ha modificado correctamente!\n\n");
                system("pause");
                system("cls");
                system("color 07");
                break;
            case 3:
                PasarDeVectorAdeportes(deportes,ArrayActs,validos);
                MenuGestionActividades(asociados,deportes,pagos,ArrayActs,listaSocios);
                break;
            }
        }
    }
    else
    {
        system("cls");
        system("color 0c");
        printf("La actividad no ha sido encontrada!\n\n");
        system("pause");
        system("cls");
        system("color 07");
        MenuGestionActividades(asociados,deportes,pagos,ArrayActs,listaSocios);
    }

    PasarDeVectorAdeportes(deportes,ArrayActs,validos);
}
void DarBajaActividad(char asociados[10],char deportes[10],char pagos[10],celda ArrayActs[100],nodo* listaSocios)
{
    int i=0;
    char act[30];
    int validos;

    validos=PasarDeportesAvector(deportes,ArrayActs);
    system("cls");
    printf("Ingrese la actividad/deporte que desea dar de baja.\n\n");
    printf("Actividad/Deporte: ");
    fflush(stdin);
    gets(act);
    while((i<validos)&&(strcmp(act,ArrayActs[i].actividad)!=0))
    {
        i++;
    }
    if(strcmp(act,ArrayActs[i].actividad)==0)
    {
        system("cls");
        ArrayActs[i].estado='i';
        system("color 0a");
        printf("La actividad se ha modificado correctamente!\n\n");
        system("pause");
        system("cls");
        system("color 07");
    }
    else
    {
        system("cls");
        system("color 0c");
        printf("La actividad no ha sido encontrada!\n\n");
        system("pause");
        system("cls");
        system("color 07");
        MenuGestionActividades(asociados,deportes,pagos,ArrayActs,listaSocios);
    }
    PasarDeVectorAdeportes(deportes,ArrayActs,validos);
}
int PasarDeportesAvector(char deportes[10],celda ArrayActs[100])
{
    FILE* archi;
    celda aux;
    int i=0;

    archi=fopen("deportes","rb");
    while(fread(&aux,sizeof(celda),1,archi)>0)
    {
        ArrayActs[i]=aux;
        i++;
    }
    fclose(archi);

    return i;
}
void PasarDeVectorAdeportes(char deportes[10],celda ArrayActs[100],int validos)
{
    FILE* archi;
    celda aux;
    int i=0;

    archi=fopen("deportes","wb");
    for(i=0; i<validos; i++)
    {
        if(ArrayActs[i].estado=='a')
        {
            aux=ArrayActs[i];
            fwrite(&aux,sizeof(celda),1,archi);
        }
    }
    fclose(archi);
}
void ListarActividades(char deportes[10],celda ArrayActs[100])
{
    int i=0;
    int validos;

    validos=PasarDeportesAvector(deportes,ArrayActs);
    system("cls");
    printf("Lista de actividades y deportes:\n\n\n");
    for(i=0; i<validos; i++)
    {
        printf("Actividad/Deporte: %s",ArrayActs[i].actividad);
        printf("\nTarifa mensual: %.3f",ArrayActs[i].tarifa);
        printf("\nHorario: %s",ArrayActs[i].horario);
        printf("\nEstado: activo");
        printf("\n--------------------------------------\n");
    }
    printf("\n\n");
    system("pause");
}
void ListarNombreActividades(char deportes[10],celda ArrayActs[100])
{
    int i=0,f=0;
    int validos;

    validos=PasarDeportesAvector(deportes,ArrayActs);
    system("cls");
    printf("Lista de actividades y deportes:\n\n\n");
    for(i=0; i<validos; i++)
    {
        printf("Actividad/Deporte: %s\t",ArrayActs[i].actividad);
        f++;
        if(f==3)
        {
            printf("\n");
            f=0;
        }
    }
    printf("\n\n");
}
void ListarSociosPorActividades(char asociados[10],char deportes[10],char pagos[10],celda ArrayActs[100],nodo* listaSocios)
{
    FILE* archi;
    char act[30];
    int i=0;
    int validos;
    socio aux;
    nodo* nuevoNodo;

    validos=PasarDeportesAvector(deportes,ArrayActs);
    system("cls");
    printf("Ingrese la Actividad/Deporte que desea listar sus respectivos socios:\n\n");
    printf("Actividad/Deporte: ");
    fflush(stdin);
    gets(act);
    while((i<validos)&&(strcmp(act,ArrayActs[i].actividad)!=0))
    {
        i++;
    }
    if(strcmp(act,ArrayActs[i].actividad)==0)
    {
        system("cls");
        printf("Actividad/Deporte: %s",ArrayActs[i].actividad);
        printf("\nTarifa mensual: %.3f",ArrayActs[i].tarifa);
        printf("\nHorario: %s",ArrayActs[i].horario);
        printf("\nEstado: activo");
        printf("\n***************************************\n");
        printf("\nSocios vinculados a la actividad:\n\n\n");
        archi=fopen("asociados","rb");
        while(fread(&aux,sizeof(socio),1,archi)>0)
        {
            if(strcmp(aux.actividad,ArrayActs[i].actividad)==0)
            {
                nuevoNodo=crearNodoLista(aux);
                ArrayActs[i].lista=agregarEnordenLista(ArrayActs[i].lista,nuevoNodo);
            }
        }
        fclose(archi);
        mostrarListaRecursivo(ArrayActs[i].lista);
        printf("\n\n");
        system("pause");
    }
    else
    {
        system("cls");
        system("color 0c");
        printf("La actividad no ha sido encontrada!\n\n");
        system("pause");
        system("cls");
        system("color 07");
        MenuGestionActividades(asociados,deportes,pagos,ArrayActs,listaSocios);
    }
}
