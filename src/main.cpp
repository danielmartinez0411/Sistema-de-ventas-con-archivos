#include <iostream>
#include <ventas/serializacionVentas.h>
#include <ventas/auxiliarVentas.h>
#include <ventas/ventas.h>
#include <string>




int main(){

    std::string venta = "1,DAniel,550,Cancelada";

    ventas::Venta nuevaVenta;
    
    nuevaVenta = ventas::serializacion::convertirLineaAVenta(venta);

    std::cout<<"ID: "<<nuevaVenta.id<<std::endl;
    std::cout<<"Nombre: "<<nuevaVenta.usuario.nombre<<std::endl;
    std::cout<<"total: "<<nuevaVenta.total<<std::endl;
    std::cout<<"Estado: "<<ventas::auxiliar::convertirEstadoATexto(nuevaVenta.estado)<<std::endl;
    

    /*
    
        El pequeño modulo ya tiene bugs jajajaja
        no se esta creando bien la venta.


        lo mas probable es que tenga que ver en como estoy sacando los datos de ss.

        pero bueno, tengo mucho sueño, me ire a dormir.
    
    
    
    */



    return 0;
}