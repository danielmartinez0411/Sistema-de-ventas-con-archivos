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

    std::string campoId, campoTotal, campoUsuario, campoEstado, campoProducto, linea;

    
    while(std::getline(archivo,linea)){

        std::stringstream ss(linea);

        std::getline(ss,campoId,',');
        std::getline(ss,campoTotal,',');
        std::getline(ss,campoUsuario,',');
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

    switch(estado){
        case ESTADO::exitosa : return "Exitosa"; break;
        case ESTADO::cancelada : return "Cancelada"; break;
    }

}


/*
================================================================


    FUNCIONES CLAVE


================================================================
*/


void Ventas::gestorVentas::crearVenta(const Usuarios::Usuario& user){

    std::ofstream archivo("txt/ventas.txt");

    int id = asignarId();

    Ventas::Venta nuevo(user,ESTADO::exitosa);

    archivo << id << "," << nuevo.usuario.nombre << "," << "$" << nuevo.total << "," << estadoATexto(nuevo.estado) << ","; 



    archivo.close();
}


/*

    DUDA: ¿es mejor pasar el nombre del usuario con string o directamente el objeto?

    porque, si le paso solo el string, lo puedo guardar mejor y en un futuro podria hacerlo mas facil
    cuando vaya a crear el menu, pero aun no estoy full convencido, lo pensare despues

    ¿que elegiste?


*/