#include <iostream>
#include <ventas/serializacionVentas.h>
#include <ventas/auxiliarVentas.h>
#include <ventas/ventas.h>
#include <string>
#include <ventas/persistenciaVentas.h>




int main(){

    std::string venta = "2,DanielMartinez,550,Cancelada";

    ventas::Venta nuevaVenta;
    
    nuevaVenta = ventas::serializacion::convertirLineaAVenta(venta);


    ventas::persistencia::inicializarArchivo();

    ventas::persistencia::agregarVentaArchivo(nuevaVenta);

    ventas::persistencia::mostrarVenta();

    ventas::persistencia::modificarVenta(2,"600",ventas::MODIFICAR::totalVenta);

    ventas::persistencia::mostrarVenta();
    
    /*
    
      Modulo persistencia probado, sin errores.


      ahora falta probar el gestorVenta (ventaCruda).

      al probarlo y arreglar los errores, entonces comenzare a trabajarCOn los productos.
    
    
    */



    return 0;
}