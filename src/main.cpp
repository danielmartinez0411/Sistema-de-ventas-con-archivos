#include <iostream>
#include <user.h>
#include <productos.h>
#include <ventas.h>
#include <string>


int main(){
    std::cout<<"Hola munssdo"<<std::endl;


    /*
        funciones a implementar hoy:

        crear archivoProductos *hecho
        arreglar el mostrarVentas/productos  * hecho
        Enum class de productos por mayor y detalle * hecho
        eliminar un articulo * hecho
        eliminar una venta * hecho
        Validacion, un articulo no puede ser al detalle y al por mayor a la vez * hecho
        validacion, que una venta no se cree directamente por agregarProductos * hecho

    
    
    */


    Ventas::gestorVentas nuevo;

    nuevo.crearVenta("DAniel","1234567");


    nuevo.agregarProductos(2,1,Ventas::PRODUCTO::porMayor);

    nuevo.eliminarVenta(3);
    
    nuevo.mostrarVenta();
 

    
    return 0;
}