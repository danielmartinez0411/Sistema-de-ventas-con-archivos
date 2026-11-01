#include <iostream>
#include <user.h>
#include <productos.h>
#include <ventas.h>
#include <string>


int main(){
    std::cout<<"Hola munssdo"<<std::endl;


    /*
        funciones a implementar hoy:

        mostrar productos por estado * hecho
        modificar estado * hecho
        validacion, el producto tiene una cantidad > 0 o la que se pide
        agregar productos (agregar cantidad)
        modificar cantidad
        vender (agregar cantidad)




        Para las funciones de cantidad, necesito conectar la cantidad dada en productos con la venta
        asi si tengo 5 papas, en la venta no pueda tener 20 por ejemplo.

        conectartodo validar y ya, al final, ya esto es lo ultimo de ventas.

        claro, tendre que modificar TODAS las funciones para que sigan esa regla.
    
    
    */


    Ventas::gestorVentas nuevo;

    //nuevo.crearVenta("DAniel","1234567");

    nuevo.agregarProductos(1,1,Ventas::PRODUCTO::alDetalle);


    
    return 0;
}