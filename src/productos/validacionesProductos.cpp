#include <productos/validacionesProductos.h>
#include <usuarios/validaciones.h>
#include <iostream>
#include <regex>

bool productos::validaciones::validarCantidad(const int& cantidad){
    return (cantidad >= 0) ? true : false;
}

bool productos::validaciones::validarCantidad(const double& cantidad){
    return (cantidad >= 0) ? true : false;
}


bool productos::validaciones::patronRegexNombreProducto(const std::string& nombre){

    std::regex patronNombre(R"(^[a-zA-Z][a-zA-Z0-9]{3,14}$)");

    return std::regex_match(nombre,patronNombre);
}



bool productos::validaciones::validarNombre(const std::string& nombre){


    std::cout<<"NOmbre: "<<nombre<<std::endl;

    if(nombre.empty()){
        return false;
    }

    if(productos::validaciones::patronRegexNombreProducto(nombre)){
        std::cout<<"El patron es valido"<<std::endl;
    }else{
        
        std::cout<<"El patron no es valido"<<std::endl;
    }


    return productos::validaciones::patronRegexNombreProducto(nombre);
}

bool productos::validaciones::validarEstado(const ESTADO& estado){
    return (estado == ESTADO::agotado || estado == ESTADO::disponible || estado == ESTADO::pocasUnidades) ? true : false;
}


bool productos::validaciones::validarTodasLasCantidad(const Producto& producto){

    bool idValido = false , canValida = false, canMinValida = false, costoValido = false , precDetValido = false ,precMayValido = false;


    idValido = productos::validaciones::validarCantidad(producto.id);

    canValida = productos::validaciones::validarCantidad(producto.cantidad);

    canMinValida = productos::validaciones::validarCantidad(producto.cantidadMinima);

    costoValido = productos::validaciones::validarCantidad(producto.costo);

    precDetValido = productos::validaciones::validarCantidad(producto.precioDetalle);

    precMayValido = productos::validaciones::validarCantidad(producto.precioPorMayor);


    return idValido && canValida && canMinValida && costoValido && precDetValido && precMayValido;

}

bool productos::validaciones::validarProducto(const productos::Producto& producto){

    bool estadoValido = false,nombreValido = false,cantidadValida = false;

    cantidadValida = productos::validaciones::validarTodasLasCantidad(producto);

   estadoValido = productos::validaciones::validarEstado(producto.estado);

   nombreValido = productos::validaciones::validarNombre(producto.nombre);

   std::cout<<"ESTADO VALIDO: "<<estadoValido<<std::endl;
   std::cout<<"NOMBRE VALIDO: "<<nombreValido<<std::endl;
   std::cout<<"CANTIDAD VALIDA: "<<cantidadValida<<std::endl;


   return estadoValido && nombreValido && cantidadValida;


}