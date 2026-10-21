#include "ventas.h"
#include "productos.h"
#include "user.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>


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

    std::string nombre;
    int cantidad, id;
    float precio;
    bool porMayor;


    Productos::gestorProducto nuevo;

    std::vector<std::string> productos = obtenerProductos(campoProductos);

    for(const auto& n : productos){

        if(n != "" && n != ","){

            nombre = corregirNombre(n);
    
            id = nuevo.obtenerIdConNombre(nombre);
    
            cantidad = calcularCantidad(campoProductos,id);
    
            porMayor = validarPorMayor(n);
    
            if(porMayor){
                precio = nuevo.retornarTotal(id,Productos::BUSCAR::precioMayor);
            }else{
                precio = nuevo.retornarTotal(id,Productos::BUSCAR::precioDetalle);
            }
    
    
            std::cout<<"\nNombre Producto: "<<nombre<<" Precio: $"<<precio<<" Cantidad: "<<cantidad<<" Sub total: $"<<cantidad*precio<<std::endl;

        }



    }



}


bool Ventas::gestorVentas::validarPorMayor(const std::string& nombreProducto){

    bool estado = false, mayuscula = false;
    int parentesis = 0;

    for(const auto& n : nombreProducto){

        if(n == '(' || n == ')'){
            parentesis++;
        }

        if(n == 'M'){
            mayuscula = true;
        }




    }


    if(mayuscula == true &&  parentesis == 2){
        estado = true;
    }


    return estado;

}


int Ventas::gestorVentas::calcularCantidad(const std::string& productos, const int& id){

    int cantidad = 0, prodID;

    std::stringstream ss(productos);


    std::string producto, nombre;

    Productos::gestorProducto nuevo;

    while(std::getline(ss,producto,',')){

        nombre = corregirNombre(producto);

        prodID = nuevo.obtenerIdConNombre(nombre);



        if(id == prodID){
            cantidad++;
        }

    }

    return cantidad;

}


std::vector<std::string> Ventas::gestorVentas::obtenerProductos(const std::string& campoProductos){

    std::vector<std::string> productos;

    std::stringstream ss(campoProductos);

    std::string producto;


    bool encontrado = false;

    while(ss){

        std::getline(ss,producto,',');


        for(int i = 0; i < productos.size();i++){

            if(productos[i] == producto){
                encontrado = true;
            }




        }


        if(!encontrado){
            productos.push_back(producto);
        }



    }


    return productos;

}


std::string Ventas::gestorVentas::corregirNombre(const std::string& nombre){

    std::stringstream ss(nombre);

    std::string nom;

    std::getline(ss,nom,'(');


    return nom;

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

        archivo << id << "," << userNombre << "," << "$" << 0 << "," << estadoATexto(ESTADO::exitosa) << "\n"; 

        archivo.close();

    }else{
        std::cout<<"========ERROR: EL USUARIO NO EXISTE======"<<std::endl;
    }







}

void Ventas::gestorVentas::agregarProductos(const int& ventasID, const int& productoID, const PRODUCTO& estado){

    std::streampos posicion = busquedaPorId(ventasID);


    if(validarVenta(posicion) == true){

        std::ifstream archivoOriginal("txt/ventas.txt");
        std::ofstream archivoCopia("txt/temporal.txt");

        Productos::gestorProducto gestorNuevo;
        
        int id;

        float total = 0;


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
            }else{

                std::stringstream productos;

                productos << productoNuevo << "," << campoProducto;

                if(estado == PRODUCTO::alDetalle){
                    
                    archivoCopia << campoId << "," << campoUser << "," << "$ "<<totalVenta(productos.str()) << "," << campoEstado << "," << productos.str() << "\n";

                }else{

                    archivoCopia << campoId << "," << campoUser << "," << " $"<<totalVenta(productos.str()) << "(M)" << "," << campoEstado << "," << productos.str() << "\n";
                }

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



void Ventas::gestorVentas::mostrarVenta(){

    std::ifstream archivo("txt/ventas.txt");


    std::string campoId, campoUser, campoTotal, campoEstado, campoProducto, linea;

    while(std::getline(archivo,linea)){

        std::stringstream ss(linea);

        std::getline(ss,campoId,',');
        std::getline(ss,campoUser,',');
        std::getline(ss,campoTotal,',');
        std::getline(ss,campoEstado,',');
        std::getline(ss,campoProducto);


        std::cout<<"\nVenta ID: "<<campoId<<std::endl;
        std::cout<<"Nombre Usuario: "<<campoUser<<std::endl;
        std::cout<<"Precio de la venta: "<<campoTotal<<std::endl;
        std::cout<<"Estado venta: "<<campoEstado<<std::endl;
        std::cout<<"\n\tProductos "<<std::endl;


        mostrarProductos(campoProducto);

        std::cout<<"\n";

    }


    archivo.close();


}



float Ventas::gestorVentas::totalVenta(const std::string& campoProductos){

    float total = 0, precio = 0;
    int cantidad = 0, id = 0;

    Productos::gestorProducto nuevo;

    bool porMayor = false;

    std::vector<std::string> productos = obtenerProductos(campoProductos);


    for(const auto& n : productos){

        std::string nombre = corregirNombre(n);

        id = nuevo.obtenerIdConNombre(nombre);

        cantidad = calcularCantidad(campoProductos,id);

        porMayor = validarPorMayor(n);

        if(porMayor == true){
            precio = nuevo.retornarTotal(id,Productos::BUSCAR::precioMayor);
        }else{
            precio = nuevo.retornarTotal(id,Productos::BUSCAR::precioDetalle);
        }

        total += precio * cantidad;



    }




    return total;


}