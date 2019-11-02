#include "headers.h"

///Cuerpo de las funciones del Sub-menu 3 de Menu Central de Administracion - Gestion Contable:
void CobrarCuotasDeSocios(char asociados[10],char deportes[10],char pagos[10],celda ArrayActs[100],nodo* listaSocios)
{
    FILE* archi;
    FILE* varchi;
    FILE* xarchi;
    pago nuevo;
    int senial=-1;
    int cantSocios=0;
    socio socar;
    int cantDep=0;
    celda depar;
    char deporsArreglo[100];
    char* fecha;
    time_t tAct=time(NULL);
    char control='s';

    while(control=='s')
    {
        tAct=time(NULL);
        fecha=asctime(localtime(&tAct));
        archi=fopen("pagos","ab");
        strcpy(nuevo.fecha,fecha);
        system("cls");
        printf("Fecha: %s",nuevo.fecha);
        printf("DNI: ");
        scanf("%ld",&nuevo.dni);
        varchi=fopen("asociados","rb");
        fseek(varchi,0,SEEK_END);
        cantSocios=ftell(varchi)/sizeof(socio);
        if(cantSocios==0)
        {
            system("cls");
            system("color 0c");
            printf("Error! No hay socios cargados en el sistema.\n\n");
            system("pause");
            system("cls");
            MenuGestionSocios(asociados,deportes,pagos,ArrayActs,listaSocios);
        }
        fseek(varchi,0,SEEK_SET);
        while((fread(&socar,sizeof(socio),1,varchi)>0)&&(senial==-1))
        {
            if(socar.dni==nuevo.dni)
            {
                senial=1;
                strcpy(nuevo.actividad,socar.actividad);
                printf("Actividad/Deporte: %s",nuevo.actividad);
            }
            if((ftell(varchi)/sizeof(socio)==cantSocios)&&(socar.dni!=nuevo.dni))
            {
                system("cls");
                system("color 0c");
                printf("Error! El DNI ingresado no corresponde a ningun socio.\n\n");
                system("pause");
                system("cls");
                system("color 07");
                control=Preguntar();
                if(control!='s')
                {
                    MenuGestionContable(asociados,deportes,pagos,ArrayActs,listaSocios);
                }
                system("color 07");
                printf("Fecha: %s",nuevo.fecha);
                printf("DNI: ");
                scanf("%ld",&nuevo.dni);
                fseek(varchi,0,SEEK_SET);
            }
        }
        fclose(varchi);
        senial=-1;
        xarchi=fopen("deportes","rb");
        fseek(xarchi,0,SEEK_END);
        cantDep=ftell(xarchi)/sizeof(celda);
        fseek(xarchi,0,SEEK_SET);
        while((fread(&depar,sizeof(celda),1,xarchi)>0)&&(senial==-1))
        {
            if(strcmp(depar.actividad,nuevo.actividad)==0)
            {
                senial=1;
                nuevo.monto=depar.tarifa;
                printf("\nMonto a cobrar: %.3f",nuevo.monto);
            }
        }
        fclose(xarchi);
        nodo* auxi=inicLista();
        auxi=PasarAsociadosAlista(asociados,auxi);
        auxi=VincularPagosAlistaDeSocios(pagos,auxi);
        nodo* seg=auxi;
        while(seg->dato.dni!=nuevo.dni)
        {
            seg=seg->siguiente;
        }
        if(seg->registro==NULL)
        {
            nuevo.numCuota=1;
            printf("\nNumero de cuota: %i\n",nuevo.numCuota);
            printf("\n\n");
            system("pause");
        }
        else
        {
            if(seg->registro->dato.numCuota<12)
            {
                nuevo.numCuota=seg->registro->dato.numCuota+1;
                printf("\nNumero de cuota: %i\n",nuevo.numCuota);
                printf("\n\n");
                system("pause");
            }
            else
            {
                system("cls");
                system("color 0c");
                printf("Error! El socio ya ha alcanzado el limite de cuotas a pagar.\n\n");
                system("pause");
                system("cls");
                system("color 07");
                MenuGestionContable(asociados,deportes,pagos,ArrayActs,listaSocios);
            }
        }
        senial=-1;
        fwrite(&nuevo,sizeof(pago),1,archi);
        fclose(archi);
        control=Preguntar();
    }
}
void ListarPagosDeUnSocio(char pagos[10],char asociados[10])
{
    FILE* varchi;
    socio socar;
    int cantSocios=0;
    int senial=-1;
    long dni;
    nodo* lista;
    nodo* buscado;
    char control='s';

    while(control=='s')
    {
        system("cls");
        printf("Ingrese el DNI del socio que desea consultar su registro de pagos.\n\n");
        printf("DNI: ");
        scanf("%ld",&dni);
        varchi=fopen("asociados","rb");
        fseek(varchi,0,SEEK_END);
        cantSocios=ftell(varchi)/sizeof(socio);
        if(cantSocios==0)
        {
            system("cls");
            system("color 0c");
            printf("Error! No hay socios cargados en el sistema.\n\n");
            system("pause");
            system("cls");
            nuevoMenuCentralADM();
        }
        fseek(varchi,0,SEEK_SET);
        while((fread(&socar,sizeof(socio),1,varchi)>0)&&(senial==-1))
        {
            if(socar.dni==dni)
            {
                senial=1;
            }
            if((ftell(varchi)/sizeof(socio)==cantSocios)&&(socar.dni!=dni))
            {
                system("cls");
                system("color 0c");
                printf("Error! El DNI ingresado no corresponde a ningun socio.\n\n");
                system("pause");
                system("cls");
                system("color 07");
                control=Preguntar();
                if(control=='s')
                {
                    printf("DNI: ");
                    scanf("%ld",&dni);
                    fseek(varchi,0,SEEK_SET);
                }
                else
                {
                    nuevoMenuCentralADM();
                }
            }
        }
        fclose(varchi);
        senial=-1;
        lista=inicLista();
        lista=PasarAsociadosAlista(asociados,lista);
        lista=VincularPagosAlistaDeSocios(pagos,lista);
        buscado=buscarNodoLista(lista,dni);
        system("cls");
        printf("Nombre y Apellido: %s",buscado->dato.nombreYapellido);
        printf("\nDNI: %ld",buscado->dato.dni);
        printf("\nEdad: %i",buscado->dato.edad);
        printf("\nActividad/Deporte: %s",buscado->dato.actividad);
        printf("\n*********************************\n");
        printf("\nRegistro Contable:\n\n");
        mostrarListaRecursivo2(buscado->registro);
        printf("\n\n");
        system("pause");
        control=Preguntar();
    }
}
nodo* VincularPagosAlistaDeSocios(char pagos[10],nodo* lista)
{
    FILE* archi;
    pago aux;
    nodo* seg=lista;
    nodo2* nuevoNodo;

    archi=fopen("pagos","rb");
    while(fread(&aux,sizeof(pago),1,archi)>0)
    {
        seg=lista;
        while(seg!=NULL)
        {
            if(aux.dni==seg->dato.dni)
            {
                nuevoNodo=crearNodo2(aux);
                seg->registro=agregarAlprincipio2(seg->registro,nuevoNodo);
            }
            seg=seg->siguiente;
        }
    }
    fclose(archi);
    return lista;
}

void PasarPagosDeListaToArchivoExcluyendo(char pagos[10],nodo* lista,long dni)
{
    FILE* archi;
    pago aux;
    nodo* seg=lista;

    archi=fopen("pagos","wb");
    while(seg!=NULL)
    {
        seg->registro=buscarUltimo2(seg->registro);
        while(seg->registro!=NULL)
        {
            if(seg->registro->dato.dni!=dni)
            {
                aux=seg->registro->dato;
                fwrite(&aux,sizeof(pago),1,archi);
            }
            seg->registro=seg->registro->anterior;
        }
        seg=seg->siguiente;
    }
    fclose(archi);
}

void ExtraerRendimientoPorActividad(char asociados[10],char deportes[10],char pagos[10],celda ArrayActs[100],nodo* listaSocios)
{
    FILE* archi;
    char act[30];
    int i=0;
    int validos;
    socio aux;
    nodo* nuevoNodo;
    char control='s';
    char control2='n';
    int cuota=0;

    while(control=='s')
    {
        validos=PasarDeportesAvector(deportes,ArrayActs);
        system("cls");
        ListarNombreActividades(deportes,ArrayActs);
        printf("--------------------------------------------------------------------------------------------------------------\n\n");
        printf("Ingrese la Actividad/Deporte que desea visualizar su rendimiento:\n\n");
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
            archi=fopen("asociados","rb");
            while(fread(&aux,sizeof(socio),1,archi)>0)
            {
                if(strcmp(aux.actividad,ArrayActs[i].actividad)==0)
                {
                    nuevoNodo=crearNodoLista(aux);
                    ArrayActs[i].lista=agregarAlfinalLista(ArrayActs[i].lista,nuevoNodo);
                }
            }
            fclose(archi);
            ArrayActs[i].lista=VincularPagosAlistaDeSocios(pagos,ArrayActs[i].lista);
            int cantAfiliados=CalcularCantidadDeAfiliados(ArrayActs[i].lista);
            printf("\nCantidad de afiliados: %i",cantAfiliados);
            float gananciaAprox=cantAfiliados*ArrayActs[i].tarifa;
            printf("\nGanancia mensual aproximada: %.3f",gananciaAprox);
            float pozoAcum=CalcularPozoAcumulado(ArrayActs[i].lista);
            printf("\nPozo acumulado: %.3f",pozoAcum);
            printf("\n\nSeleccione el numero de cuota para saber los socios que la adeudan.\n");
            printf("\n[1]Enero\t[2]Febrero\t[3]Marzo\n[4]Abril\t[5]Mayo\t\t[6]Junio\n[7]Julio\t[8]Agosto\t[9]Septiembre\n[10]Octubre\t[11]Noviembre\t[12]Diciembre");
            printf("\n\nCuota: ");
            scanf("%i",&cuota);
            printf("\n\nAdeudan los siguientes socios la cuota %i:\n\n",cuota);
            DeterminarSociosQueAdeudanAlaFecha(ArrayActs[i].lista,cuota,act);
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
        }
        i=0;
        control=Preguntar();
    }
}
int CalcularCantidadDeAfiliados(nodo* lista)
{
    nodo* seg=lista;
    int rta=0;
    if(seg==NULL)
    {
        rta=rta+0;
    }
    else
    {
        rta=CalcularCantidadDeAfiliados(seg->siguiente)+1;
    }
    return rta;
}

float CalcularPozoAcumulado(nodo* lista)
{
    nodo* seg=lista;
    float rta=0;
    while(seg!=NULL)
    {
        rta=rta+SumarAportesDeUnSocio(seg->registro);
        seg=seg->siguiente;
    }

    return rta;
}

float SumarAportesDeUnSocio(nodo2* registro)
{
    nodo2* seg=registro;
    float aporte=0;

    while(seg!=NULL)
    {
        aporte=aporte+seg->dato.monto;
        seg=seg->siguiente;
    }

    return aporte;
}

void DeterminarSociosQueAdeudanAlaFecha(nodo* lista,int cuota,char actividad[30])
{
    nodo* seg=lista;

    while(seg!=NULL)
    {
        if(seg->registro!=NULL)
        {
        if((strcmp(actividad,seg->registro->dato.actividad)==0))
        {
            if((seg->registro->dato.numCuota<cuota))
            {
                MostrarUnSoloSocio(seg);
            }
        }
        }
        else
        {
            MostrarUnSoloSocio(seg);
        }
        seg=seg->siguiente;
    }
}

