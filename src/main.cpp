#include <iostream>
#include <user.h>
#include <productos.h>
#include <ventas.h>
#include <string>


int main(){
    std::cout<<"Hola munssdo"<<std::endl;


    Ventas::gestorVentas nuevo;

    nuevo.crearVenta("DAniel","1234567");

    nuevo.agregarProductos(1,2);

   
    
    return 0;
}