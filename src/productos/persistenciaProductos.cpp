#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include "productos/persistenciaProductos.h"
#include "productos/serializacion.h"
#include "productos/auxiliarProductos.h"



bool productos::persistencia::inicializarArchivo(){

    std::ifstream archivo("txt/productos.txt");

    if(!archivo.good()){

        archivo.close();

        std::ofstream archivoNuevo("/txt/productos.txt");

        archivoNuevo.close();

    }

    return true;
}


bool productos::persistencia::agregarProductoAlArchivo(const Producto& producto){

    std::ofstream archivo("txt/productos.txt");

    std::string linea = productos::serializacion::convertirProductoALinea(producto);

    if(archivo << linea << "\n"){
        return true;
    }

    archivo.close();
    return false;
}


bool productos::persistencia::buscarYObtenerProducto(const int& id, Producto& producto){

    std::ifstream archivo("txt/productos.txt");

    std::string linea;

    while(std::getline(archivo,linea)){

        Producto nuevo = productos::serializacion::convertirLineaAProducto(linea);

        if(nuevo.id == id){
            producto = nuevo;
            return true;
        }


    }


    archivo.close();
    return false;
}

bool productos::persistencia::eliminarProductoArchivo(const int& id){

    std::ifstream archivo("txt/productos.txt");
    std::ofstream archivoCopia("txt/productosTemporal.txt");

    std::string linea;

    while(std::getline(archivo,linea)){

        Producto nuevo = productos::serializacion::convertirLineaAProducto(linea);


        if(nuevo.id != id){
            archivoCopia << linea << "\n";
        }



    }

    archivoCopia.close();
    archivo.close();

    if(std::remove("txt/productos.txt") == 0){

        if(std::rename("txt/productosTemporal.txt","txt/productos.txt") == 0){
            return true;
        }



    }



    return false;

}

std::string productos::persistencia::modificarSwitch(const Producto& producto, const std::string& modificacion, const MODIFICAR& campo){

    std::stringstream ss;

    switch(campo){

        case MODIFICAR::cantidad :{

            ss << producto.id << ","<< modificacion << "," << producto.cantidadMinima << "," 
            << producto.costo << "," << producto.precioDetalle << "," << producto.precioPorMayor << "," << producto.nombre
            << "," << productos::auxiliar::estadoATexto(producto.estado) << "\n";



            break;
        }

        case MODIFICAR::cantidadMinima :{

            ss << producto.id << ","<< producto.cantidad << "," << modificacion << "," 
            << producto.costo << "," << producto.precioDetalle << "," << producto.precioPorMayor << "," << producto.nombre
            << "," << productos::auxiliar::estadoATexto(producto.estado) << "\n";



            break;
        }

        case MODIFICAR::costo :{

            ss << producto.id << ","<< producto.cantidad << "," << producto.cantidadMinima << "," 
            << modificacion << "," << producto.precioDetalle << "," << producto.precioPorMayor << "," << producto.nombre
            << "," << productos::auxiliar::estadoATexto(producto.estado) << "\n";



            break;
        }

        case MODIFICAR::precioDetalle :{

            ss << producto.id << ","<< producto.cantidad << "," << producto.cantidadMinima << "," 
            << producto.costo << "," << modificacion << "," << producto.precioPorMayor << "," << producto.nombre
            << "," << productos::auxiliar::estadoATexto(producto.estado) << "\n";



            break;
        }

        case MODIFICAR::precioPorMayor :{

            ss << producto.id << ","<< producto.cantidad << "," << producto.cantidadMinima << "," 
            << producto.costo << "," << producto.precioDetalle << "," << modificacion << "," << producto.nombre
            << "," << productos::auxiliar::estadoATexto(producto.estado) << "\n";



            break;
        }

        case MODIFICAR::nombre :{

            ss << producto.id << ","<< producto.cantidad << "," << producto.cantidadMinima << "," 
            << producto.costo << "," << producto.precioDetalle << "," << producto.precioPorMayor << "," << modificacion
            << "," << productos::auxiliar::estadoATexto(producto.estado) << "\n";



            break;
        }

        case MODIFICAR::estado :{

            ss << producto.id << ","<< producto.cantidad << "," << producto.cantidadMinima << "," 
            << producto.costo << "," << producto.precioDetalle << "," << producto.precioPorMayor << "," << producto.nombre
            << "," << modificacion << "\n";



            break;
        }



    }

    return ss.str();

}


bool productos::persistencia::modificarProductoArchivo(const int& id, const std::string& modificacion, const MODIFICAR& campo){

    std::ifstream archivo("txt/productos.txt");
    std::ofstream archivoCopia("txt/productosTemporal.txt");

    std::string linea;

    while(std::getline(archivo,linea)){

        Producto nuevo = productos::serializacion::convertirLineaAProducto(linea);

        if(nuevo.id != id){
            archivoCopia << linea << "\n";
        }else{
            archivoCopia << modificarSwitch(nuevo,modificacion,campo) << "\n";
        }


    }
    

    archivo.close();
    archivoCopia.close();

    if(std::remove("txt/productos.txt") == 0){

        if(std::rename("txt/productosTemporal.txt","txt/productos.txt") == 0){
            return true;
        }



    }

    return false;
}

bool productos::persistencia::validarExistenciaProducto(const std::string& nombre){

    std::ifstream archivo("txt/productos.txt");

    std::string linea;

    while(std::getline(archivo,linea)){

        Producto nuevo = productos::serializacion::convertirLineaAProducto(linea);

        if(nuevo.nombre == nombre){
            return true;
        }



    }



    return false;
}

int productos::persistencia::mayorID(){

    std::ifstream archivo("txt/productos.txt");

    int mayor = 0;

    std::string linea;

    while(std::getline(archivo,linea)){

        Producto nuevo = productos::serializacion::convertirLineaAProducto(linea);

        if(nuevo.id > mayor){
            mayor = nuevo.id;
        }

    }


    return mayor;
}


void productos::persistencia::mostrarProducto(){

    std::ifstream archivo("txt/productos.txt");

    std::string linea;

    while(std::getline(archivo,linea)){

        Producto nuevo = productos::serializacion::convertirLineaAProducto(linea);

        std::cout<<"\nID: "<<nuevo.id<<std::endl;
        std::cout<<"Nombre: "<<nuevo.nombre<<std::endl;
        std::cout<<"Precio Detalle: $"<<nuevo.precioDetalle<<std::endl;
        std::cout<<"Precio Por Mayor: $"<<nuevo.precioPorMayor<<std::endl;
        std::cout<<"Costo: $"<<nuevo.costo<<std::endl;
        std::cout<<"Cantidad: "<<nuevo.cantidad<<std::endl;
        std::cout<<"Cantidad Minima: "<<nuevo.cantidadMinima<<std::endl;
        std::cout<<"Estado: "<<productos::auxiliar::estadoATexto(nuevo.estado)<<std::endl;



    }



}

void productos::persistencia::mostrarProducto(const int& id){

    std::ifstream archivo("txt/productos.txt");

    std::string linea;

    while(std::getline(archivo,linea)){

        Producto nuevo = productos::serializacion::convertirLineaAProducto(linea);


        if(nuevo.id == id){

            std::cout<<"\nID: "<<nuevo.id<<std::endl;
            std::cout<<"Nombre: "<<nuevo.nombre<<std::endl;
            std::cout<<"Precio Detalle: $"<<nuevo.precioDetalle<<std::endl;
            std::cout<<"Precio Por Mayor: $"<<nuevo.precioPorMayor<<std::endl;
            std::cout<<"Costo: $"<<nuevo.costo<<std::endl;
            std::cout<<"Cantidad: "<<nuevo.cantidad<<std::endl;
            std::cout<<"Cantidad Minima: "<<nuevo.cantidadMinima<<std::endl;
            std::cout<<"Estado: "<<productos::auxiliar::estadoATexto(nuevo.estado)<<std::endl;

        }




    }



}