#include <iostream>
#include <user.h>
#include <productos.h>
#include <ventas.h>
#include <string>


int main(){
    std::cout<<"Hola munssdo"<<std::endl;


    Ventas::gestorVentas nuevo;

    //nuevo.crearVenta("DAniel","1234567");


    std::string campo = "Poz,Pozo(M),Poz";

    std::vector<std::string> productos = nuevo.obtenerProductos(campo);

    float total = nuevo.totalVenta(campo);

    for(const auto& n : productos){
        std::cout<<n<<std::endl;
    }

    std::cout<<"Total: "<<total<<std::endl;
    






    /*Productos::gestorProducto nuevo;

    nuevo.mostrarProductos();

    std::cout<<"\n"<<nuevo.retornarTotal(1,Productos::BUSCAR::precioMayor);

   */



   /*
    quejas / cambio que quieros hacer:



    hay que cambiar la funcion calcular total, tiene un bug
    solo aparece el precio de un solo articulo.

    mejor crear una funcion que calcule la cantidad que hay de un producto y usando esa cantidad.
    se calcule el total

    ya existe la funcion para verificar si un precio es al por mayor o no.


    ******

    probablemente calcular total sea una funcion de venta en vez de producto
    me siento mas convencido asi, entonces tu sabras lo que decidiste.

    por el momento voy en la funcion mostrar: la cual solo tiene ese error y ya.

    solo faltaria el:

    nombre producto, precio producto y cantidad producto, por lo tanto con esa sola funcion termino el mostra

    solo faltaria el eliminar venta, modificar venta, eliminar producto de una venta.

    modificar el precio de un producto en una venta

    mostrar una venta unica.

    cancelar una venta

    validacion de estado de venta

    y ya, por el momento solo se me ocurren esas, por lo tanto despues de esas, ya comenzaria a trabajar con
    el menu y tambien con el sistema en general (entrada y salida de datos, validaciones etc)
   
   
   
   
   
   */
    
    return 0;
}