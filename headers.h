#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "windows.h"
#include "time.h"

///Estructuras:
typedef struct
{
    char usuario[20];
    char clave[20];
    char reclave[20];
} cuenta;

typedef struct
{
    char fecha[50]; /// Ej: 12/09/2018
    long dni;
    char actividad[30];
    int numCuota; ///De 1 a 12 por año
    float monto;
} pago;

typedef struct
{
    pago dato;
    struct nodo2* anterior;
    struct nodo2* siguiente;
} nodo2;

typedef struct
{
    char nombreYapellido[30];
    long dni;
    int edad;
    char actividad[30];
} socio;

typedef struct
{
    socio dato;
    struct nodo* siguiente;
    nodo2* registro;
} nodo;

typedef struct
{
    char actividad[30]; //nombre de la actividad
    float tarifa; //cuota por mes
    char horario[200];
    char estado; //a o i
    nodo* lista;
} celda;


void color(int x);

///Protipado de las funciones del login:

void nuevoMenuLogin();
void CrearCifrado(char cuentas[10]);
void FormatearSistema(char cuentas[10],char asociados[10],char deportes[10],char pagos[10]);
int IniciarSesion(char cuentas[10]);
void arreglopass(char pass[20]);

///Protipado de las funciones de eleccion:

char Preguntar();
char PreguntarModificacion();
char PreguntarSalida();

///Protipado de las funciones de menu administrador:

void nuevoMenuCentralADM();
void MenuGestionSocios(char asociados[10],char deportes[10],char pagos[10],celda ArrayActs[100],nodo* listaSocios);
void MenuGestionActividades(char asociados[10],char deportes[10],char pagos[10],celda ArrayActs[100],nodo* listaSocios);
void MenuGestionContable(char asociados[10],char deportes[10],char pagos[10],celda ArrayActs[100],nodo* listaSocios);

///Prototipado de las funciones del Sub-menu 1 de Menu Central de Administracion - Gestion de Socios:

void CargarSocios(char asociados[10],char deportes[10],char pagos[10],celda ArrayActs[100],nodo* listaSocios);
void ModificarSocio(char asociados[10],char deportes[10],char pagos[10],celda ArrayActs[100],nodo* listaSocios);
nodo* PasarAsociadosAlista(char asociados[10],nodo* lista);
void PasarDeListaAasociados(char asociados[10],nodo* lista);
void DarBajaSocio(char asociados[10],char deportes[10],char pagos[10],celda ArrayActs[100],nodo* listaSocios);
void MostrarUnSoloSocio(nodo* lista);

///Prototipado de las funciones del Sub-menu 2 de Menu Central de Administracion - Gestion de Actividades:

void CargarActividadesNuevas(char asociados[10],char deportes[10],char pagos[10],celda ArrayActs[100],nodo* listaSocios);
void ModificarActividad(char asociados[10],char deportes[10],char pagos[10],celda ArrayActs[100],nodo* listaSocios);
void DarBajaActividad(char asociados[10],char deportes[10],char pagos[10],celda ArrayActs[100],nodo* listaSocios);
int PasarDeportesAvector(char deportes[10],celda ArrayActs[100]);
void PasarDeVectorAdeportes(char deportes[10],celda ArrayActs[100],int validos);
void ListarActividades(char deportes[10],celda ArrayActs[100]);
void ListarNombreActividades(char deportes[10],celda ArrayActs[100]);
void ListarSociosPorActividades(char asociados[10],char deportes[10],char pagos[10],celda ArrayActs[100],nodo* listaSocios);

///Prototipado de las funciones del Sub-menu 3 de Menu Central de Administracion - Gestion Contable:

void CobrarCuotasDeSocios(char asociados[10],char deportes[10],char pagos[10],celda ArrayActs[100],nodo* listaSocios);
void ListarPagosDeUnSocio(char pagos[10],char asociados[10]);
nodo* VincularPagosAlistaDeSocios(char pagos[10],nodo* lista);
void PasarPagosDeListaToArchivoExcluyendo(char pagos[10],nodo* lista,long dni);
void ExtraerRendimientoPorActividad(char asociados[10],char deportes[10],char pagos[10],celda ArrayActs[100],nodo* listaSocios);
int CalcularCantidadDeAfiliados(nodo* lista);
float CalcularPozoAcumulado(nodo* lista);
float SumarAportesDeUnSocio(nodo2* registro);
void DeterminarSociosQueAdeudanAlaFecha(nodo* lista,int cuota,char actividad[30]);

///Prototipado de las funciones para listas simples:

nodo* inicLista();
nodo* inicNodoLista();
nodo* crearNodoLista(socio dato);
nodo* buscarUltimoLista(nodo* lista);
nodo* agregarAlprincipioLista(nodo* lista,nodo* nuevoNodo);
nodo* buscarNodoLista(nodo* lista,long dni);
nodo* agregarAlfinalLista(nodo* lista,nodo* nuevoNodo);
nodo* agregarEnordenLista(nodo* lista,nodo* nuevoNodo);
nodo* borrarNodo(nodo* lista,long dni);
void mostrarListaRecursivo(nodo* lista);

///Prototipado de las funciones para listas dobles:

nodo2* inicLista2();
nodo2* inicNodo2();
nodo2* crearNodo2(pago dato);
nodo2* agregarAlprincipio2(nodo2* lista,nodo2* nuevoNodo);
nodo2* buscarUltimo2(nodo2* lista);
nodo2* agregarAlfinal2(nodo2* lista,nodo2* nuevoNodo);
void mostrarListaRecursivo2(nodo2* lista);
