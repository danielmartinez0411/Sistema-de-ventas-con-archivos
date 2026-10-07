#include "ventas.h"
#include "productos.h"
#include "user.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>


/*
================================================================


    FUNCIONES AUXILIARES


================================================================
*/

int Ventas::gestorVentas::mayorID(){

    std::ifstream archivo("txt/ventas.txt");

    int id = 0, mayor = 0;

    std::string campoId, campoUsuario, campoTotal, campoEstado, campoProducto, linea;

    
    while(std::getline(archivo,linea)){

        std::stringstream ss(linea);

        std::getline(ss,campoId,',');
        std::getline(ss,campoUsuario,',');
        std::getline(ss,campoTotal,',');
        std::getline(ss,campoEstado,',');
        std::getline(ss,campoProducto);

        id = std::stoi(campoId);

        if(id > mayor){
            mayor = id;
        }


    }


    archivo.close();
    return mayor;
}

inline int Ventas::gestorVentas::asignarId(){
    return mayorID() + 1;
}

std::string Ventas::gestorVentas::estadoATexto(ESTADO estado){

    std::string texto;


    switch(estado){
        case ESTADO::exitosa : return texto = "Exitosa"; break;
        case ESTADO::cancelada : return texto ="Cancelada"; break;
    }

    return texto;
}

inline bool Ventas::gestorVentas::validarVenta(const std::streampos& posicion){
    return (posicion == -1) ? false : true;
}


void Ventas::gestorVentas::mostrarProductos(const std::string& campoProductos){

    std::stringstream ss(campoProductos);

    while(ss){

        std::string nombreProducto;

        std::getline(ss,nombreProducto,',');

        //Me quede en esta funcion.
        /*

            tengo pensado crear una gran funcion que muestre la venta tipo:

            id de venta
            nombre del vendedor

            productos

            total:

            esta es la parte de mostrar los productos, pero aun estoy medio trancao en como mostraria el precio
            junto con el nombre, supongo que es por el sueño xd.

        */



    }



}


/*
================================================================


    FUNCIONES CLAVE


================================================================
*/



std::streampos Ventas::gestorVentas::busquedaPorId(const int& ventaID){

    std::ifstream archivo("txt/ventas.txt");

    std::string campoId, campoUsuario, campoTotal, campoEstado, campoProducto, linea;

    int id;


    while(archivo){


        std::streampos posicion = archivo.tellg();
    
        std::getline(archivo,linea);
    
        std::stringstream ss(linea);
    
    
        std::getline(ss,campoId,',');
        std::getline(ss,campoUsuario,',');
        std::getline(ss,campoTotal,',');
        std::getline(ss,campoEstado,',');
        std::getline(ss,campoProducto);
    
        std::stringstream cambio(campoId);

        cambio >> id;
    
        if(ventaID == id){
            archivo.close();
            return posicion;
        }


    }    

    archivo.close();
    return -1;


}



void Ventas::gestorVentas::crearVenta(const std::string& userNombre, const std::string& userClave){

    
    Usuarios::gestorUsuario nuevo;
    
    if(nuevo.validarExistencia(userClave,userNombre)){
        
        std::ofstream archivo("txt/ventas.txt", std::ios_base::app);

        int id = asignarId();

        archivo << id << "," << userNombre << "," << "$" << 0 << "," << estadoATexto(ESTADO::exitosa); 

        archivo.close();

    }else{
        std::cout<<"========ERROR: EL USUARIO NO EXISTE======"<<std::endl;
    }







}

void Ventas::gestorVentas::agregarProductos(const int& ventasID, const int& productoID){

    std::streampos posicion = busquedaPorId(ventasID);


    if(validarVenta(posicion) == true){

        std::ifstream archivoOriginal("txt/ventas.txt");
        std::ofstream archivoCopia("txt/temporal.txt");

        Productos::gestorProducto gestorNuevo;
        
        int id;

        float nuevoTotal = 0;


        std::string campoId, campoUser, campoTotal, campoEstado, campoProducto, productoNuevo, linea;

        productoNuevo = gestorNuevo.retornarNombre(productoID);

        while(std::getline(archivoOriginal,linea)){

            std::stringstream ss(linea);

            std::getline(ss,campoId,',');
            std::getline(ss,campoUser,',');
            std::getline(ss,campoTotal,',');
            std::getline(ss,campoEstado,',');
            std::getline(ss,campoProducto);


            id = std::stoi(campoId);

            if(id != ventasID){
                archivoCopia << campoId << "," << campoUser << "," << campoTotal << "," << campoEstado << "," << campoProducto << "\n";
                std::cout<<campoProducto<<std::endl;
            }else{

                std::stringstream cambio(campoTotal);


                cambio >> nuevoTotal;

                archivoCopia << campoId << "," << campoUser << "," << "$"<<gestorNuevo.calcularTotal(gestorNuevo.obtenerNombreConId(productoID),nuevoTotal,Productos::BUSCAR::precioDetalle) << "," << campoEstado << "," <<productoNuevo << "," << campoProducto << "\n";
                std::cout<<campoProducto<<std::endl;
            }




        }   

        archivoCopia.close();
        archivoOriginal.close();

        std::remove("txt/ventas.txt");
        std::rename("txt/temporal.txt","txt/ventas.txt");


    }else{
        std::cout<<"========ERROR: LA VENTA NO EXISTE======"<<std::endl;
    }


}