#include <ventas/persistenciaVentas.h>
#include <ventas/ventas.h>
#include <ventas/serializacionVentas.h>
#include <ventas/auxiliarVentas.h>
#include <usuarios/funcionalidades.h>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

bool ventas::persistencia::inicializarArchivo(){
    
    std::ifstream archivo("txt/ventas.txt");

    if(!archivo.good()){


        archivo.close();

        std::ofstream archivoNuevo("txt/ventas.txt");



        archivoNuevo.close();


    }

    return true;

}


bool ventas::persistencia::agregarVentaArchivo(const Venta& venta){

    std::ofstream archivo("txt/ventas.txt",std::ios_base::app);


    std::string linea = ventas::serializacion::convertirVentaALinea(venta);


    if(archivo << linea){
        return true;
    }

    archivo.close();
    return false;
}


bool ventas::persistencia::buscarYObtenerVenta(const int& ventaID, Venta& venta){

    std::ifstream archivo("txt/ventas.txt");


    std::string linea;

    while(std::getline(archivo,linea)){


        ventas::Venta nuevo = ventas::serializacion::convertirLineaAVenta(linea);

        if(nuevo.id == ventaID){
            venta = nuevo;
            return true;
        }



    }

    archivo.close();
    return false;

}

bool ventas::persistencia::eliminarVenta(const int& ventaID){

    std::ifstream archivo("txt/ventas.txt");
    std::ofstream archivoTemporal("txt/temporalVentas.txt");


    std::string linea;


    while(std::getline(archivo,linea)){

        ventas::Venta nuevo = ventas::serializacion::convertirLineaAVenta(linea);


        if(nuevo.id != ventaID){
            archivoTemporal << linea << "\n";
        }



    }

    archivo.close();
    archivoTemporal.close();


    if(std::remove("txt/ventas.txt") == 0){
        
        if(std::rename("txt/temporalVentas.txt","txt/ventas.txt") == 0){

            return true;
        
        }
    } 

    return false;
}


std::string ventas::persistencia::modificarSwitch(const Venta& venta, const std::string& modificacion, const MODIFICAR& campo){

    std::stringstream ss;

    switch(campo){

        case MODIFICAR::estadoVenta : {

            ventas::ESTADO nuevo = ventas::auxiliar::convertirTextoAEstado(modificacion);

            ss << venta.id << "," << venta.usuario.nombre << "," << venta.total << "," << ventas::auxiliar::convertirEstadoATexto(nuevo) << "\n";



            break;
        }


        case MODIFICAR::nombreUsuario : {

            usuarios::Usuario nuevo = usuarios::funcionalidades::obtenerUsuarioConNombre(modificacion);

            ss << venta.id << "," << nuevo.nombre << "," << venta.total << "," << ventas::auxiliar::convertirEstadoATexto(venta.estado) << "\n";

            break;
        }

        case MODIFICAR::totalVenta :{

            std::stringstream cambio(modificacion);

            double precio;

            cambio >> precio;

            ss << venta.id << "," << venta.usuario.nombre << "," << precio << "," << ventas::auxiliar::convertirEstadoATexto(venta.estado) << "\n";

            break;

        }




    }

    return ss.str();

}



bool ventas::persistencia::modificarVenta(const int& ventaID, const std::string& modificacion, const MODIFICAR& campo){

    std::ifstream archivo("txt/ventas.txt");
    std::ofstream archivoTemporal("txt/temporalVentas.txt");


    std::string linea;

    while(std::getline(archivo,linea)){

        ventas::Venta nuevo = ventas::serializacion::convertirLineaAVenta(linea);


        if(nuevo.id != ventaID){
            archivoTemporal << linea << "\n";
        }else{
            archivoTemporal << modificarSwitch(nuevo,modificacion,campo);
        }



    }

    archivo.close();
    archivoTemporal.close();


    if(std::remove("txt/ventas.txt") == 0){
        
        if(std::rename("txt/temporalVentas.txt","txt/ventas.txt") == 0){

            return true;
        
        }
    } 

    return false;


}


void ventas::persistencia::mostrarVenta(){

    std::ifstream archivo("txt/ventas.txt");

    std::string linea;


    while(std::getline(archivo,linea)){

        ventas::Venta nuevo = ventas::serializacion::convertirLineaAVenta(linea);


        std::cout<<"\nID: "<<nuevo.id<<std::endl;
        std::cout<<"NOMBRE: "<<nuevo.usuario.nombre<<std::endl;
        std::cout<<"TOTAL: "<<nuevo.total<<std::endl;
        std::cout<<"ESTADO: "<<ventas::auxiliar::convertirEstadoATexto(nuevo.estado)<<std::endl;



    }



    archivo.close();

}

void ventas::persistencia::mostrarVenta(const int& ventaID){

    std::ifstream archivo("txt/ventas.txt");

    std::string linea;


    while(std::getline(archivo,linea)){

        ventas::Venta nuevo = ventas::serializacion::convertirLineaAVenta(linea);



        if(nuevo.id == ventaID){

            std::cout<<"\nID: "<<nuevo.id<<std::endl;
            std::cout<<"NOMBRE: "<<nuevo.usuario.nombre<<std::endl;
            std::cout<<"TOTAL: "<<nuevo.total<<std::endl;
            std::cout<<"ESTADO: "<<ventas::auxiliar::convertirEstadoATexto(nuevo.estado)<<std::endl;

        }





    }



    archivo.close();

}


int ventas::persistencia::mayorID(){

    std::ifstream archivo("txt/ventas.txt");

    std::string linea;

    int id = 0;

    while(std::getline(archivo,linea)){

        ventas::Venta nuevo = ventas::serializacion::convertirLineaAVenta(linea);

        if(nuevo.id > id){
            id = nuevo.id;
        }

    }


    archivo.close();
    return id;
}