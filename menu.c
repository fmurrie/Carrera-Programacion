#include "headers.h"

///Menu Interactivo
void nuevoMenuLogin()
{
    int colorNormal=15;
    int colorSobre=11;
    char cuentas[10];
    char asociados[10];
    char deportes[10];
    char pagos[10];
    int candado=-1;
    char control='s';
    char opcion;
    int y=7;
    int cm=0;
    do
    {
        system("cls");
        color(10);///letra verde/ fondo negro
        for(cm=0; cm<23; cm++)
        {
            if(cm==0)
            {
                printf("%c",201);
            }
            printf("%c",205);
            if(cm==22)
            {
                printf("%c",187);
            }
        }
        printf("\n%cBIENVENIDO AL SISTEMA!!%c\n",186,186);
        for(cm=0; cm<23; cm++)
        {
            if(cm==0)
            {
                printf("%c",200);
            }
            printf("%c",205);
            if(cm==22)
            {
                printf("%c",188);
            }
        }
        printf("\n\n\n");
        color(colorNormal);///letra blanca/ fondo negro
        if(y==7)
            color(colorSobre);
        printf("Iniciar Sesion\n");
        color(colorNormal);
        if(y==10)
            color(colorSobre);
        printf("Cifrar Sistema\n");
        color(colorNormal);
        if(y==13)
            color(colorSobre);
        printf("Formatear Sistema\n");
        color(colorNormal);
        if(y==16)
            color(colorSobre);
        printf("Salir");
        ///-----------------------
        opcion=getch();///retorna el numero del codigo ascii de la tecla ingresada
        if(opcion==80)///tecla de abajo
        {
            if(y==16)
            {
                y=7;
            }
            else
            {
                y=y+3;
            }
        }
        if(opcion==72)///tecla de arriba
        {
            if(y==7)
            {
                y=16;
            }
            else
            {
                y=y-3;
            }
        }
        if(opcion==13)///tecla ENTER
        {
            system("cls");
            if(y==7)
            {
                candado=IniciarSesion(cuentas);
                if(candado==-1)
                {
                    system("cls");
                    system("color 0c");
                    printf("Error! Se ha denegado su acceso.\n\nMotivos:\n\t>El sistema puede no estar cifrado.\n\t>Ha alcanzado el limites de intentos.\n\n");
                    system("pause");
                    system("color 07");
                    system("cls");
                    nuevoMenuLogin();
                }
                else
                {
                    candado=-1;
                    nuevoMenuCentralADM();
                }
            }
            if(y==10)
            {
                CrearCifrado(cuentas);
            }
            if(y==13)
            {
                FormatearSistema(cuentas,asociados,deportes,pagos);
            }
            if(y==16)
            {
                control='s';
                control=PreguntarSalida();
                if(control!='s')
                {
                    nuevoMenuLogin();
                }

                else
                {
                    system("cls");
                    system("color 0f");
                    printf("------------->Fin del programa<-------------\n\n");
                    exit(1);
                }
                break;
            }
            break;
        }
    }
    while(1);
}
void nuevoMenuCentralADM()
{
    int colorNormal=15;
    int colorSobre=11; ///color con el que se va a mover
    int cm=0;
    ///----------Variables--para--gestion--de--socios--------------
    char asociados[10]; ///archivo de socios
    nodo* listaSocios;
    ///----------Variables--para--gestion--de--actividades---------
    char deportes[10]; ///archivo de actividades
    celda ArrayActs[100];
    ///----------Variables--para--gestion--contable----------------
    char pagos[10];
    int y=18, opcion2=0;
    char control='s';


    do
    {
        system("cls");
        color(10);
        for(cm=0; cm<30; cm++)
        {
            if(cm==0)
            {
                printf("%c",201);
            }
            printf("%c",205);
            if(cm==29)
            {
                printf("%c",187);
            }
        }
        printf("\n%c",186);
        printf("Menu de Gestion Administrativa");
        printf("%c\n",186);
        for(cm=0; cm<30; cm++)
        {
            if(cm==0)
            {
                printf("%c",200);
            }
            printf("%c",205);
            if(cm==29)
            {
                printf("%c",188);
            }
        }
        printf("\n\n\n");
        color(colorNormal);
        if(y==18)
            color(colorSobre);
        printf("Gestionar Socios\n");
        color(colorNormal);
        if(y==21)
            color(colorSobre);
        printf("Gestionar Actividades\n");
        color(colorNormal);
        if(y==24)
            color(colorSobre);
        printf("Gestion Contable\n");
        color(colorNormal);
        if(y==27)
            color(colorSobre);
        printf("Cerrar Sesion\n");
        opcion2=getch();
        if(opcion2==80)///tecla de abajo
        {
            if(y==27)
            {
                y=18;
            }
            else
            {
                y=y+3;
            }
        }
        if(opcion2==72)///tecla de arriba
        {
            if(y==18)
            {
                y=27;
            }
            else
            {
                y=y-3;
            }
        }
        if(opcion2==13)///tecla enter
        {
            system("cls");
            if(y==18)/// Gestionar Socios
            {
                MenuGestionSocios(asociados,deportes,pagos,ArrayActs,listaSocios);
                break;
            }
            if(y==21)/// Gestionar Actividades
            {
                MenuGestionActividades(asociados,deportes,pagos,ArrayActs,listaSocios);
                break;
            }
            if(y==24)/// Gestion Contable
            {
                MenuGestionContable(asociados,deportes,pagos,ArrayActs,listaSocios);
                break;
            }
            if(y==27)/// Cerrar Sesion
            {
                control='s';
                control=PreguntarSalida();
                if(control=='s')
                    nuevoMenuLogin();
                else
                    nuevoMenuCentralADM();
                break;
            }
            break;

        }
    }
    while(1);
}
void color(int x)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
}

///Cuerpo de las funciones del menu login:
void CrearCifrado(char cuentas[10])
{
    FILE* archi;
    cuenta nueva;
    int cm=0;

    archi=fopen("cuentas","a+b");
    fseek(archi,0,SEEK_END);
    if(ftell(archi)/sizeof(cuenta)==0)
    {
        color(10);
        for(cm=0; cm<16; cm++)
        {
            if(cm==0)
            {
                printf("%c",201);
            }
            printf("%c",205);
            if(cm==15)
            {
                printf("%c",187);
            }
        }
        printf("\n%c",186);
        color(11);
        printf(">Crear cifrado. ");
        color(10);
        printf("%c\n",186);
        for(cm=0; cm<16; cm++)
        {
            if(cm==0)
            {
                printf("%c",200);
            }
            printf("%c",205);
            if(cm==15)
            {
                printf("%c",188);
            }
        }
        printf("\n\n\n");
        color(15);
        printf("Nombre de usuario: ");
        fflush(stdin);
        gets(nueva.usuario);
        printf("Clave: ");
        fflush(stdin);
        arreglopass(nueva.clave);
        printf("\nConfirmacion de clave: ");
        fflush(stdin);
        arreglopass(nueva.reclave);
        while(strcmp(nueva.clave,nueva.reclave)!=0)
        {
            system("cls");
            system("color 0c");
            printf("Error! Las claves ingresadas no coinciden.\n\n");
            system("pause");
            system("cls");
            system("color 07");
            color(10);
            for(cm=0; cm<16; cm++)
            {
                if(cm==0)
                {
                    printf("%c",201);
                }
                printf("%c",205);
                if(cm==15)
                {
                    printf("%c",187);
                }
            }
            printf("\n%c",186);
            color(11);
            printf(">Crear cifrado. ");
            color(10);
            printf("%c\n",186);
            for(cm=0; cm<16; cm++)
            {
                if(cm==0)
                {
                    printf("%c",200);
                }
                printf("%c",205);
                if(cm==15)
                {
                    printf("%c",188);
                }
            }
            printf("\n\n\n");
            color(15);
            printf("Nombre de usuario: %s\n",nueva.usuario);
            printf("Clave: ");
            fflush(stdin);
            arreglopass(nueva.clave);
            printf("\nConfirmacion de clave: ");
            fflush(stdin);
            arreglopass(nueva.reclave);
        }
        fwrite(&nueva,sizeof(cuenta),1,archi);
        system("cls");
        system("color 0a");
        printf("El sistema se ha cifrado correctamente!\n\n");
        system("pause");
        system("cls");
        system("color 07");
    }
    else
    {
        system("cls");
        system("color 0c");
        printf("Error! El sistema ya se encuentra cifrado.\n\n");
        system("pause");
        system("cls");
        system("color 07");
    }
    fclose(archi);
    nuevoMenuLogin();
}
void FormatearSistema(char cuentas[10],char asociados[10],char deportes[10],char pagos[10])
{
    FILE* archi;
    FILE* archiS;
    FILE* archiD;
    FILE* archiP;
    cuenta nueva;
    char control='s';
    int candado=1;

    color(7);
    printf("Requisito de Seguridad:\n\n");
    color(11);
    printf(">Introduza los datos de cifrado del sistema actuales.\n\n>Debera iniciar sesion.\n\n");
    candado=IniciarSesion(cuentas);
    if(candado==1)
    {
        system("cls");
        system("color 0c");
        printf("Advertencia: usted va a restaurar el sistema.\n\n\n-Esta accion implica:\n\n-Perdida de la informacion almacenada.\n-Nuevo cifrado del programa.\n\n");
        printf("Desea continuar realmente?(S/N): ");
        fflush(stdin);
        scanf("%c",&control);
        system("cls");
        system("color 07");
        if(control=='s')
        {
            archi=fopen("cuentas","w+b");
            color(11);
            printf(">A continuacion rellene los campos:\n\n");
            color(15);
            printf("Nombre de usuario: ");
            fflush(stdin);
            gets(nueva.usuario);
            printf("Clave: ");
            fflush(stdin);
            arreglopass(nueva.clave);
            printf("\nConfirmacion de clave: ");
            fflush(stdin);
            arreglopass(nueva.reclave);
            while(strcmp(nueva.clave,nueva.reclave)!=0)
            {
                system("cls");
                system("color 0c");
                printf("Error! Las claves ingresadas no coinciden.\n\n");
                system("pause");
                system("cls");
                color(11);
                printf(">A continuacion rellene los campos:\n\n");
                color(15);
                printf("Nombre de usuario: %s\n",nueva.usuario);
                printf("Clave: ");
                fflush(stdin);
                arreglopass(nueva.clave);
                printf("\nConfirmacion de clave: ");
                fflush(stdin);
                arreglopass(nueva.reclave);
            }
            fwrite(&nueva,sizeof(cuenta),1,archi);
            fclose(archi);
            archiS=fopen("asociados","wb");
            fclose(archiS);
            archiD=fopen("deportes","wb");
            fclose(archiD);
            archiP=fopen("pagos","wb");
            fclose(archiP);
            system("cls");
            system("color 0a");
            printf("El sistema se ha restaurado correctamente!\n\n");
            system("pause");
            system("cls");
            system("color 07");
            nuevoMenuLogin();
        }
        else
        {
            nuevoMenuLogin();
        }
    }
    else
    {
        nuevoMenuLogin();
    }
}
int IniciarSesion(char cuentas[10])
{
    cuenta aux,aux2;
    FILE* archi;
    int intentos=1,rta=-1;
    int cm=0;
    int haycuenta=0;

    color(10);
    archi=fopen("cuentas","rb");
    fseek(archi,0,SEEK_END);
    haycuenta=ftell(archi)/sizeof(cuenta);
    fseek(archi,0,SEEK_SET);
    if(haycuenta!=1)
    {
        system("cls");
        system("color 0c");
        printf("Error! El sistema no esta cifrado.\n\n");
        system("pause");
        system("color 07");
        system("cls");
        CrearCifrado(cuentas);
    }
    for(cm=0; cm<16; cm++)
    {
        if(cm==0)
        {
            printf("%c",201);
        }
        printf("%c",205);
        if(cm==15)
        {
            printf("%c",187);
        }
    }
    printf("\n%c",186);
    color(11);
    printf(">Iniciar sesion.");
    color(10);
    printf("%c\n",186);
    for(cm=0; cm<16; cm++)
    {
        if(cm==0)
        {
            printf("%c",200);
        }
        printf("%c",205);
        if(cm==15)
        {
            printf("%c",188);
        }
    }
    printf("\n\n\n");
    color(15);
    printf("Nombre de usuario: ");
    fflush(stdin);
    gets(aux.usuario);
    printf("Clave: ");
    fflush(stdin);
    arreglopass(aux.clave);
    //archi=fopen("cuentas","rb");
    while((fread(&aux2,sizeof(cuenta),1,archi)>0)&&(intentos<4)&&(rta!=1))
    {
        if((strcmp(aux.usuario,aux2.usuario)==0)&&(strcmp(aux.clave,aux2.clave)==0))
        {
            rta=1;
        }
        else
        {
            system("cls");
            system("color 0c");
            printf("Error! El nombre de usuario y la clave no coinciden.\n\n");
            printf("Van %i/3 intentos!\n\n",intentos);
            intentos++;
            if(intentos==3)
            {
                printf("Advertencia: ultimo intento!\n\n");
            }
            if(intentos<=3)
            {
                system("pause");
                system("cls");
                system("color 07");
                color(10);
                for(cm=0; cm<16; cm++)
                {
                    if(cm==0)
                    {
                        printf("%c",201);
                    }
                    printf("%c",205);
                    if(cm==15)
                    {
                        printf("%c",187);
                    }
                }
                printf("\n%c",186);
                color(11);
                printf(">Iniciar sesion.");
                color(10);
                printf("%c\n",186);
                for(cm=0; cm<16; cm++)
                {
                    if(cm==0)
                    {
                        printf("%c",200);
                    }
                    printf("%c",205);
                    if(cm==15)
                    {
                        printf("%c",188);
                    }
                }
                printf("\n\n\n");
                color(15);
                printf("Nombre de usuario: ");
                fflush(stdin);
                gets(aux.usuario);
                printf("Clave: ");
                fflush(stdin);
                arreglopass(aux.clave);
            }
        }
        fseek(archi,0,SEEK_SET);
    }
    fclose(archi);
    return rta;
}
void arreglopass(char pass[20])
{
    int pos=0, cont=0, cont2=0;
    int i=0;
    for(i=0; i<20; i++)
    {
        pass[i]=0;
    }
    pass[pos]=getch();
    if((pass[pos]!=13)&&(pass[pos]!=8))
    {
        printf("*");
    }
    while(pass[pos]!=13)
    {
        pos++;
        fflush(stdin);
        pass[pos]=getch();
        while((pos>0)&&(pass[pos]==8))
        {
            pass[pos]=0;
            pos=pos-1;
            printf("\b \b");
            pass[pos]=getch();
            while(pos==0&&pass[pos]==8)
            {
                pass[pos]=getch();
            }
        }
        if((pass[pos]!=13)&&(pass[pos]!=8))
        {
            printf("*");
            cont++;
        }
    }
}

///Cuerpo de las funciones de eleccion:
char Preguntar()
{
    char control='s';
    system("cls");
    printf("Desea continuar?(S/N): ");
    fflush(stdin);
    scanf("%c",&control);
    system("cls");
    return control;
}
char PreguntarModificacion()
{
    char control='s';

    printf("Desea modificarlo?(S/N)");
    fflush(stdin);
    scanf("%c",&control);
    system("cls");

    return control;
}
char PreguntarSalida()
{
    char control='s';
    system("cls");
    system("color 0c");
    printf("Seguro desea salir?(S/N): ");
    fflush(stdin);
    scanf("%c",&control);
    system("cls");
    system("color 07");
    return control;
}
void MenuGestionSocios(char asociados[10],char deportes[10],char pagos[10],celda ArrayActs[100],nodo* listaSocios)
{
    int y=30,opcion2=0;
    int colorNormal=15;
    int colorSobre=11;
    int candado=-1;
    char control='s';
    char opcion;
    int cm=0;
    do
    {
        system("cls");
        color(10);
        for(cm=0; cm<25; cm++)
        {
            if(cm==0)
            {
                printf("%c",201);
            }
            printf("%c",205);
            if(cm==24)
            {
                printf("%c",187);
            }
        }
        printf("\n%c",186);
        printf("Menu de Gestion De Socios");
        printf("%c\n",186);
        for(cm=0; cm<25; cm++)
        {
            if(cm==0)
            {
                printf("%c",200);
            }
            printf("%c",205);
            if(cm==24)
            {
                printf("%c",188);
            }
        }
        printf("\n\n\n");
        color(colorNormal);
        if(y==30)
            color(colorSobre);
        printf("Dar de Alta un Socio\n");
        color(colorNormal);
        if(y==33)
            color(colorSobre);
        printf("Modificar un Socio\n");
        color(colorNormal);
        if(y==36)
            color(colorSobre);
        printf("Dar de Baja un Socio\n");
        color(colorNormal);
        if(y==39)
            color(colorSobre);
        printf("Listar Socios\n");
        color(colorNormal);
        if(y==42)
            color(colorSobre);
        printf("Volver\n");
        color(colorNormal);
        if(y==45)
            color(colorSobre);
        printf("Cerrar Sesion\n");
        opcion2=getch();
        if(opcion2==80)///tecla de abajo
        {
            if(y==45)
            {
                y=30;
            }
            else
            {
                y=y+3;
            }
        }
        if(opcion2==72)///tecla de arriba
        {
            if(y==30)
            {
                y=45;
            }
            else
            {
                y=y-3;
            }
        }
        if(opcion2==13)
        {
            if(y==30)
            {
                system("cls");
                CargarSocios(asociados,deportes,pagos,ArrayActs,listaSocios);
                MenuGestionSocios(asociados,deportes,pagos,ArrayActs,listaSocios);
                break;
            }
            if(y==33)
            {
                system("cls");
                ModificarSocio(asociados,deportes,pagos,ArrayActs,listaSocios);
                MenuGestionSocios(asociados,deportes,pagos,ArrayActs,listaSocios);
                break;
            }
            if(y==36)
            {
                system("cls");
                DarBajaSocio(asociados,deportes,pagos,ArrayActs,listaSocios);
                MenuGestionSocios(asociados,deportes,pagos,ArrayActs,listaSocios);
                break;
            }
            if(y==39)
            {
                system("cls");
                listaSocios=inicLista();
                listaSocios=PasarAsociadosAlista(asociados,listaSocios);
                printf("Lista de socios afiliados:\n\n\n");
                mostrarListaRecursivo(listaSocios);
                printf("\n\n");
                system("pause");
                system("cls");
                MenuGestionSocios(asociados,deportes,pagos,ArrayActs,listaSocios);
                break;
            }
            if(y==42)
            {
                system("cls");
                nuevoMenuCentralADM();
                break;
            }
            if(y==45)
            {
                system("cls");
                control='s';
                control=PreguntarSalida();
                if(control=='s')
                    nuevoMenuLogin();
                else
                    MenuGestionSocios(asociados,deportes,pagos,ArrayActs,listaSocios);
                break;
            }
        }
    }
    while(1);
}
void MenuGestionActividades(char asociados[10],char deportes[10],char pagos[10],celda ArrayActs[100],nodo* listaSocios)
{
    int y=48,opcion2=0;
    int colorNormal=15;
    int colorSobre=11;
    int candado=-1;
    char control='s';
    char opcion;
    int cm=0;
    do
    {
        system("cls");
        color(10);
        for(cm=0; cm<30; cm++)
        {
            if(cm==0)
            {
                printf("%c",201);
            }
            printf("%c",205);
            if(cm==29)
            {
                printf("%c",187);
            }
        }
        printf("\n%c",186);
        printf("Menu de Gestion De Actividades");
        printf("%c\n",186);
        for(cm=0; cm<30; cm++)
        {
            if(cm==0)
            {
                printf("%c",200);
            }
            printf("%c",205);
            if(cm==29)
            {
                printf("%c",188);
            }
        }
        printf("\n\n\n");
        color(colorNormal);
        if(y==48)
            color(colorSobre);
        printf("Dar de Alta una Actividad\n");
        color(colorNormal);
        if(y==51)
            color(colorSobre);
        printf("Modificar una Actividad\n");
        color(colorNormal);
        if(y==54)
            color(colorSobre);
        printf("Dar de Baja una Actividad\n");
        color(colorNormal);
        if(y==57)
            color(colorSobre);
        printf("Listar Actividades\n");
        color(colorNormal);
        if(y==60)
            color(colorSobre);
        printf("Listar Socios por Actividad\n");
        color(colorNormal);
        if(y==63)
            color(colorSobre);
        printf("Volver\n");
        color(colorNormal);
        if(y==66)
            color(colorSobre);
        printf("Cerrar Sesion\n");
        opcion2=getch();
        if(opcion2==80)///tecla de abajo
        {
            if(y==66)
            {
                y=48;
            }
            else
            {
                y=y+3;
            }
        }
        if(opcion2==72)///tecla de arriba
        {
            if(y==48)
            {
                y=66;
            }
            else
            {
                y=y-3;
            }
        }
        if(opcion2==13)
        {
            if(y==48)
            {
                system("cls");
                CargarActividadesNuevas(asociados,deportes,pagos,ArrayActs,listaSocios);
                MenuGestionActividades(asociados,deportes,pagos,ArrayActs,listaSocios);
                break;
            }
            if(y==51)
            {
                system("cls");
                ModificarActividad(asociados,deportes,pagos,ArrayActs,listaSocios);
                MenuGestionActividades(asociados,deportes,pagos,ArrayActs,listaSocios);
                break;
            }
            if(y==54)
            {
                DarBajaActividad(asociados,deportes,pagos,ArrayActs,listaSocios);
                MenuGestionActividades(asociados,deportes,pagos,ArrayActs,listaSocios);
                break;
            }
            if(y==57)
            {
                system("cls");
                ListarActividades(deportes,ArrayActs);
                MenuGestionActividades(asociados,deportes,pagos,ArrayActs,listaSocios);
                break;
            }
            if(y==60)
            {
                system("cls");
                ListarSociosPorActividades(asociados,deportes,pagos,ArrayActs,listaSocios);
                MenuGestionActividades(asociados,deportes,pagos,ArrayActs,listaSocios);
                break;
            }
            if(y==63)
            {
                system("cls");
                nuevoMenuCentralADM();
                break;
            }
            if(y==66)
            {
                system("cls");
                control='s';
                control=PreguntarSalida();
                if(control=='s')
                    nuevoMenuLogin();
                else
                    MenuGestionActividades(asociados,deportes,pagos,ArrayActs,listaSocios);
                break;
            }
        }
    }
    while(1);
}
void MenuGestionContable(char asociados[10],char deportes[10],char pagos[10],celda ArrayActs[100],nodo* listaSocios)
{
    int y=69,opcion2=0;
    int colorNormal=15;
    int colorSobre=11;
    int candado=-1;
    char control='s';
    char opcion;
    int cm=0;
    do
    {
        system("cls");
        color(10);
        for(cm=0; cm<27; cm++)
        {
            if(cm==0)
            {
                printf("%c",201);
            }
            printf("%c",205);
            if(cm==26)
            {
                printf("%c",187);
            }
        }
        printf("\n%c",186);
        printf("Menu de Gestion De Contable");
        printf("%c\n",186);
        for(cm=0; cm<27; cm++)
        {
            if(cm==0)
            {
                printf("%c",200);
            }
            printf("%c",205);
            if(cm==26)
            {
                printf("%c",188);
            }
        }
        printf("\n\n\n");
        color(colorNormal);
        if(y==69)
            color(colorSobre);
        printf("Cobrar Cuotas\n");
        color(colorNormal);
        if(y==72)
            color(colorSobre);
        printf("Listar Pagos de un Socio\n");
        color(colorNormal);
        if(y==75)
            color(colorSobre);
        printf("Visualizar rendimiento\n");
        color(colorNormal);
        if(y==78)
            color(colorSobre);
        printf("Volver\n");
        color(colorNormal);
        if(y==81)
            color(colorSobre);
        printf("Cerrar Sesion\n");
        opcion2=getch();
        if(opcion2==80)///tecla de abajo
        {
            if(y==81)
            {
                y=69;
            }
            else
            {
                y=y+3;
            }
        }
        if(opcion2==72)///tecla de arriba
        {
            if(y==69)
            {
                y=81;
            }
            else
            {
                y=y-3;
            }
        }
        if(opcion2==13)
        {
            if(y==69)
            {
                system("cls");
                CobrarCuotasDeSocios(asociados,deportes,pagos,ArrayActs,listaSocios);
                MenuGestionContable(asociados,deportes,pagos,ArrayActs,listaSocios);
                break;
            }
            if(y==72)
            {
                system("cls");
                ListarPagosDeUnSocio(pagos,asociados);
                MenuGestionContable(asociados,deportes,pagos,ArrayActs,listaSocios);
                break;
            }
            if(y==75)
            {
                system("cls");
                ExtraerRendimientoPorActividad(asociados,deportes,pagos,ArrayActs,listaSocios);
                MenuGestionContable(asociados,deportes,pagos,ArrayActs,listaSocios);
                break;
            }
            if(y==78)
            {
                system("cls");
                nuevoMenuCentralADM();
                break;
            }
            if(y==81)
            {
                system("cls");
                control='s';
                control=PreguntarSalida();
                if(control=='s')
                    nuevoMenuLogin();
                else
                    MenuGestionContable(asociados,deportes,pagos,ArrayActs,listaSocios);
                break;
            }
        }
    }
    while(1);
}
