#include "venta.h"
#include <iostream>
using namespace std;

void crearArchivo(){
    struct Encabezado encabezado;
    struct Medicamento medicamento;
    //struct Fecha fecha;
    //struct Indice indice;

    //Declaramos el arreglo de indices para ir almecenando
    //los indices de los campos a ingresar
    Indice indices[100];

    int numeroRegistros = 0;
    int i = 0;

    //Calcular longitud de estructura encabezado y medicamento
    int le = sizeof(struct Encabezado);
    int lm = sizeof(struct Medicamento);
    //int li = sizeof(struct Indice);


    //Crea el archivo de Datos
    int archivoDatos = creat("datos.txt",(S_IREAD|S_IWRITE));

    //Crea el archivo de indices
    int archivoIndice = creat("indices.txt",S_IREAD|S_IWRITE);

    encabezado.numRegs = 0;

    //Pedir cantidad de registros
    cout<<"Cantidad de registros a ingresar: ";
    cin>>numeroRegistros;


    //Posicionamos al inicio del archivo
    lseek(archivoDatos,le,0);

    for(i = 0; i<numeroRegistros; i++){
        medicamento.codigo = ++encabezado.numRegs;


        /*Leer datos medicamento*/
        cout<<"Nombre medicamento: ";
        cin>>medicamento.nombre;
        cout<<"Laboratorio: ";
        cin>>medicamento.laboratorio;
        cout<<"Cantidad: ";
        cin>>medicamento.cantidad;
        cout<<"Precio: ";
        cin>>medicamento.precio;
        cout<<"Codigo: ";
        cin>>medicamento.codigo;
        cout<<"Dia: ";
        cin>>medicamento.fecha.dia;
        cout<<"Mes: ";
        cin>>medicamento.fecha.mes;
        cout<<"Anio: ";
        cin>>medicamento.fecha.anio;


        //Se van asignando los indices
        strcpy(indices[encabezado.numRegs - 1].nombre,medicamento.nombre);
        indices[encabezado.numRegs - 1].nroRegs = encabezado.numRegs;
        indices[encabezado.numRegs - 1].ptro = medicamento.codigo;
        write(archivoDatos,&medicamento,lm);

    }

    lseek(archivoDatos,0,0);
    write(archivoDatos,&encabezado,le);
    grabarIndices(archivoIndice,indices,encabezado);
    close(archivoDatos);

}

bool grabarIndices(int archivoIndice,Indice indices[],struct Encabezado encabezado){


    int i = 0;
    int j = 0;
    Indice temp;

    //Calcular longitud de estructura encabezado
    int le = sizeof(struct Encabezado);
    int li = sizeof(struct Indice);


    for(i = 0; i<encabezado.numRegs; i++){
        for(j = i + 1; j<encabezado.numRegs; j++){

            if(indices[j].nombre < indices[i].nombre){
                temp = indices[j];
                indices[j] = indices[i];
                indices[i] = temp;
            }
        }
    }

    lseek(archivoIndice,0,0);
    write(archivoIndice,&encabezado,le);

    for(i = 0; i<encabezado.numRegs; i++){
        write(archivoIndice,&indices[i],li);

       }
    close(archivoIndice);
    return true;
}

void listarOrdenado(){

    struct Medicamento medicamento;
    struct Indice indice;
    struct Encabezado encabezado;

    int lm = sizeof(struct Medicamento);
    int li = sizeof(struct Indice);
    int le = sizeof(struct Encabezado);

    Indice i;


    //Abrimos los dos archivos

    /* Apertura del archivo de Datos */

        int archivoDatos = open ("datos.txt", O_RDONLY);

        /* Comprobación */
        if (archivoDatos == -1)
        {
            perror("Error al abrir fichero:");
            exit(1);
        }


        /* Apertura del archivo de Indices */

            int archivoIndice = open ("indices.txt", O_RDONLY);

            /* Comprobación */
            if (archivoIndice == -1)
            {
                perror("Error al abrir fichero:");
                exit(1);
            }


          //Leemos el archivo de indices
            read(archivoIndice,&encabezado,le);
            int pos;

            while(read(archivoIndice,&i,li) > 0){

                pos  = (i.ptro - 1)*lm + le;
                lseek(archivoDatos,pos,0);
                read(archivoDatos,&medicamento,lm);

                cout<<"\n";
                cout<<"Nombre del medicamento: "<<medicamento.nombre<<" \n ";
                cout<<"Precio: $"<<medicamento.precio<<" \n ";
                cout<<"Laboratorio: "<<medicamento.laboratorio<<" \n ";
                cout<<"Codigo: "<<medicamento.codigo<<" \n ";
                cout<<"Fecha de ingreso (DD/MM/AAAA): "<<medicamento.fecha.dia<<"/"<<medicamento.fecha.mes<<"/"<<medicamento.fecha.anio;
                cout<<"\n";
            }
    close(archivoDatos|archivoIndice);

}
