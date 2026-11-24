#include <iostream>
#include <ventas/serializacionVentas.h>
#include <ventas/auxiliarVentas.h>
#include <ventas/ventas.h>
#include <string>




int main(){

    std::string venta = "1,DanielMartinez,550,Cancelada";

    ventas::Venta nuevaVenta;
    
    nuevaVenta = ventas::serializacion::convertirLineaAVenta(venta);

    std::cout<<"ID: "<<nuevaVenta.id<<std::endl;
    std::cout<<"Nombre: "<<nuevaVenta.usuario.nombre<<std::endl;
    std::cout<<"total: "<<nuevaVenta.total<<std::endl;
    std::cout<<"Estado: "<<ventas::auxiliar::convertirEstadoATexto(nuevaVenta.estado)<<std::endl;

    /*
    
      algunas funciones del modulo ventas (archivo) terminadas.

      falta probar persistencia. tengo sueño.
    
    
    
    */



    return 0;
}