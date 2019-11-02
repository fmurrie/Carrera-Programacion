#include "headers.h"

///Cuerpo de las funciones del Sub-menu 1 de Menu Central de Administracion - Gestion de Socios:
void CargarSocios(char asociados[10],char deportes[10],char pagos[10],celda ArrayActs[100],nodo* listaSocios)
{
    FILE* archi;
    FILE* xarchi;
    socio nuevo;
    socio aux;
    celda aux2;
    celda deporsArreglo[100];
    int senial=-1;
    int cantDep=0;
    char control='s';


    while(control=='s')
    {
        archi=fopen("asociados","a+b");
        system("cls");
        printf("A continuacion rellene los campos:\n\n");
        printf("Nombre y Apellido: ");
        fflush(stdin);
        gets(nuevo.nombreYapellido);
        printf("DNI: ");
        scanf("%ld",&nuevo.dni);
        while(fread(&aux,sizeof(socio),1,archi)>0)
        {
            while(aux.dni==nuevo.dni)
            {
                system("cls");
                system("color 0c");
                printf("Error! DNI ya en uso.\n\n");
                system("pause");
                system("cls");
                system("color 07");
                control=Preguntar();
                if(control!='s')
                {
                    MenuGestionSocios(asociados,deportes,pagos,ArrayActs,listaSocios);
                }
                system("color 07");
                printf("Nombre y Apellido: %s\n",nuevo.nombreYapellido);
                printf("DNI: ");
                scanf("%ld",&nuevo.dni);
                fseek(archi,0,SEEK_SET);
            }
        }
        printf("Edad: ");
        scanf("%i",&nuevo.edad);
        printf("Actividad/Deporte: ");
        fflush(stdin);
        gets(nuevo.actividad);
        xarchi=fopen("deportes","rb");
        fseek(xarchi,0,SEEK_END);
        cantDep=ftell(xarchi)/sizeof(celda);
        fseek(xarchi,0,SEEK_SET);
        if(cantDep==0)
        {
            system("cls");
            system("color 0c");
            printf("Error! No hay actividades/deportes cargados en el sistema.\n\n");
            system("pause");
            system("cls");
            MenuGestionActividades(asociados,deportes,pagos,ArrayActs,listaSocios);
        }
        fseek(xarchi,0,SEEK_SET);
        while((fread(&aux2,sizeof(celda),1,xarchi)>0)&&(senial==-1))
        {
            if(strcmp(aux2.actividad,nuevo.actividad)==0)
            {
                senial=1;
            }
            if((ftell(xarchi)/sizeof(celda)==cantDep)&&(strcmp(aux2.actividad,nuevo.actividad)!=0))
            {
                system("cls");
                system("color 0c");
                printf("Error! La actividad indicada no existe.\n\n");
                system("pause");
                system("cls");
                system("color 07");
                control=Preguntar();
                if(control=='s')
                {
                    ListarActividades(deportes,deporsArreglo);
                    system("cls");
                }
                else
                {
                    system("color 07");
                    MenuGestionSocios(asociados,deportes,pagos,ArrayActs,listaSocios);
                }
                system("color 07");
                printf("Nombre y Apellido: %s\n",nuevo.nombreYapellido);
                printf("DNI: %ld\n",nuevo.dni);
                printf("Edad: %i\n",nuevo.edad);
                printf("Actividad/Deporte: ");
                fflush(stdin);
                gets(nuevo.actividad);
                fseek(xarchi,0,SEEK_SET);
            }
        }
        fclose(xarchi);
        fwrite(&nuevo,sizeof(socio),1,archi);
        fclose(archi);
        control=Preguntar();
        senial=-1;
    }
}
void ModificarSocio(char asociados[10],char deportes[10],char pagos[10],celda ArrayActs[100],nodo* listaSocios)
{
    nodo* lista;
    long dni;
    nodo* buscado;
    celda Arrayaux[100];
    int i=0;
    int bandera=0;
    char actAnterior[30];
    char control='s';
    int opcion=0;

    lista=inicLista();
    lista=PasarAsociadosAlista(asociados,lista);
    system("cls");
    printf("Ingrese el DNI del socio que desea modificar.\n\n");
    printf("DNI: ");
    scanf("%ld",&dni);
    buscado=buscarNodoLista(lista,dni);
    if(buscado==NULL)
    {
        system("cls");
        system("color 0c");
        printf("El socio no ha sido encontrado!\n\n");
        system("pause");
        system("cls");
        system("color 07");
        MenuGestionSocios(asociados,deportes,pagos,ArrayActs,listaSocios);
    }
    else
    {
        system("cls");
        while(control=='s')
        {
            MostrarUnSoloSocio(buscado);
            printf("\n\nDatos permitidos para modificar:\n\n[1]Nombre y Apellido.\n[2]Edad.\n[3]Actividad/Deporte.\n[4]Volver");
            printf("\n\nSeleccione la opcion que desea modificar: ");
            scanf("%i",&opcion);
            switch(opcion)
            {
            case 1:
                printf("\nNombre y Apellido: ");
                fflush(stdin);
                gets(buscado->dato.nombreYapellido);

                system("cls");
                system("color 0a");
                printf("El socio se ha modificado correctamente!\n\n");
                system("pause");
                system("cls");
                system("color 07");
                control=Preguntar();
                break;
            case 2:
                printf("\nEdad: ");
                scanf("%i",&buscado->dato.edad);

                system("cls");
                system("color 0a");
                printf("El socio se ha modificado correctamente!\n\n");
                system("pause");
                system("cls");
                system("color 07");
                control=Preguntar();
                break;
            case 3:
                strcpy(actAnterior,buscado->dato.actividad);
                printf("\nActividad/Deporte: ");
                fflush(stdin);
                gets(buscado->dato.actividad);
                int cantDep=PasarDeportesAvector(deportes,Arrayaux);
                while(bandera!=-1)
                {
                    if(strcmp(buscado->dato.actividad,Arrayaux[i].actividad)==0)
                    {
                        bandera=-1;
                    }
                    if((i==cantDep)&&(bandera!=-1))
                    {
                        i=0;
                        system("cls");
                        system("color 0c");
                        printf("Error! La actividad indicada no existe.\n\n");
                        system("pause");
                        system("cls");
                        system("color 07");
                        control=Preguntar();
                        if(control=='s')
                        {
                            ListarActividades(deportes,Arrayaux);
                            system("cls");
                            printf("Nombre y Apellido: %s\n",buscado->dato.nombreYapellido);
                            printf("Edad: %i\n",buscado->dato.edad);
                            printf("Actividad/Deporte: ");
                            fflush(stdin);
                            gets(buscado->dato.actividad);
                            i=-1;
                        }
                        else
                        {
                            system("color 07");
                            MenuGestionSocios(asociados,deportes,pagos,ArrayActs,listaSocios);
                        }
                    }
                    i++;
                }
                if(strcmp(actAnterior,buscado->dato.actividad)!=0)
                {
                    lista=VincularPagosAlistaDeSocios(pagos,lista);
                    PasarPagosDeListaToArchivoExcluyendo(pagos,lista,dni);
                }

                system("cls");
                system("color 0a");
                printf("El socio se ha modificado correctamente!\n\n");
                system("pause");
                system("cls");
                system("color 07");

                control=Preguntar();
                break;
            case 4:
                PasarDeListaAasociados(asociados,lista);
                MenuGestionSocios(asociados,deportes,pagos,ArrayActs,listaSocios);
                break;
            }

        }
        PasarDeListaAasociados(asociados,lista);
    }
}
nodo* PasarAsociadosAlista(char asociados[10],nodo* lista)
{
    FILE* archi;
    nodo* nuevoNodo;
    socio aux;

    archi=fopen("asociados","rb");
    while(fread(&aux,sizeof(socio),1,archi)>0)
    {
        nuevoNodo=crearNodoLista(aux);
        lista=agregarAlfinalLista(lista,nuevoNodo);
    }
    fclose(archi);
    return lista;
}
void PasarDeListaAasociados(char asociados[10],nodo* lista)
{
    FILE* archi;
    socio aux;

    archi=fopen("asociados","wb");
    while(lista!=NULL)
    {
        aux=lista->dato;
        fwrite(&aux,sizeof(socio),1,archi);
        lista=lista->siguiente;
    }
    fclose(archi);
}
void DarBajaSocio(char asociados[10],char deportes[10],char pagos[10],celda ArrayActs[100],nodo* listaSocios)
{
    nodo* lista;
    long dni;
    nodo* buscado;

    lista=inicLista();
    lista=PasarAsociadosAlista(asociados,lista);
    system("cls");
    printf("Ingrese el DNI del socio que desea dar de baja.\n\n");
    printf("DNI: ");
    scanf("%ld",&dni);
    buscado=buscarNodoLista(lista,dni);
    if(buscado==NULL)
    {
        system("cls");
        system("color 0c");
        printf("El socio ha dar de baja no ha sido encontrado!\n\n");
        system("pause");
        system("cls");
        system("color 07");
        MenuGestionSocios(asociados,deportes,pagos,ArrayActs,listaSocios);
    }
    else
    {
        lista=borrarNodo(lista,dni);
        system("cls");
        system("color 0a");
        printf("El socio se ha dado de baja correctamente!\n\n");
        system("pause");
        system("cls");
        system("color 07");
    }
    PasarDeListaAasociados(asociados,lista);
}
void MostrarUnSoloSocio(nodo* lista)
{
    printf("Nombre y Apellido: %s",lista->dato.nombreYapellido);
    printf("\nEdad: %i",lista->dato.edad);
    printf("\nActividad: %s",lista->dato.actividad);
    printf("\n-----------------------------\n");
}
