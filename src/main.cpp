#include <iostream>
#include <user.h>
#include <productos.h>
#include <string>


int main(){
    std::cout<<"Hola munssdo"<<std::endl;


    Productos::gestorProducto nuevo;

    //nuevo.agregarProducto(0,0,50.2,76,65,"Pozar");


    nuevo.mostrarProductos();

    //nuevo.mostrarRangoDePrecios(70,90,Productos::BUSCAR::precioDetalle);


    //nuevo.busquedaPorNombre("Pozod");

    //nuevo.modificarProducto(3,"Pozar","Riquito");


    int id = nuevo.obtenerIdConNombre("Pozd");


    std::cout<<"ID: "<<id<<std::endl;
    
    return 0;
}