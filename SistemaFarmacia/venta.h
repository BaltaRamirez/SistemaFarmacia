#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

struct Encabezado{

    int numRegs;

};

struct Fecha{

    int dia;
    int mes;
    int anio;

};

struct Medicamento{

    int codigo;
    char nombre[20];
    char laboratorio[15];
    int cantidad;
    double precio;
    Fecha fecha;

};

struct Indice{

    int nroRegs; //Numero de registros
    char nombre[20];
    int ptro;

};

void crearArchivo();
bool grabarIndices(int archivoIndice,Indice indices[],struct Encabezado encabezado);
void listarOrdenado();
