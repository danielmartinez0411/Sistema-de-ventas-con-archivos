#include "productos/productos.h"
#include "productos/validacionesProductos.h"
#include "productos/validacionSemantica.h"
#include "productos/persistenciaProductos.h"
#include "productos/auxiliarProductos.h"


int productos::gestorProducto::asignarID(){
    return productos::persistencia::mayorID() + 1;
}


productos::Producto productos::gestorProducto::crearProducto(const int& can, const int& canMin, const double& costo, const double& precDet, const double& precMay, const std::string& nombre, const int& estadoProducto){

    bool canValida = false, canMinValida = false, costoValido = false, precDetValido = false, precMayValido = false;
    bool nombreValido = false, estadoValido = false;

    productos::ESTADO nuevo = productos::auxiliar::enteroAEstado(estadoProducto);

    canValida = productos::validaciones::validarCantidad(can);
    canMinValida = productos::validaciones::validarCantidad(canMin);
    costoValido = productos::validaciones::validarCantidad(costo);
    precDetValido = productos::validaciones::validarCantidad(precDet);
    precMayValido = productos::validaciones::validarCantidad(precMay);
    nombreValido = productos::validaciones::validarNombre(nombre);
    estadoValido = productos::validaciones::validarEstado(nuevo);

    if(canMinValida && canValida && costoValido && precDetValido && precMayValido && nombreValido && estadoValido){

        Producto nuevoProducto(asignarID(),can,canMin,costo,precDet,precMay,nombre,nuevo);


        if(productos::validacionSemantica::validarLogicaProducto(nuevoProducto)){
        
            
            return nuevoProducto;


        }

    }


    return productos::Producto{};

}


bool productos::gestorProducto::agregarProductoArchivo(const Producto& producto){

    bool estado = false;

    if(productos::validaciones::validarProducto(producto) && productos::validacionSemantica::validarLogicaProducto(producto)){

        if(!productos::persistencia::validarExistenciaProducto(producto.nombre)){

            estado = true;

            productos::persistencia::agregarProductoAlArchivo(producto);

        }

    }

    return estado;
}

bool productos::gestorProducto::buscarYObtenerProducto(const int& id, Producto& producto){

    bool estado = false;

    if(productos::validaciones::validarCantidad(id)){

        estado = true;

        productos::persistencia::buscarYObtenerProducto(id,producto);

    }


    return estado;
}

bool productos::gestorProducto::modificarProducto(const int& id, const std::string& modificacion, const MODIFICAR& campo){

    bool estado = false, campoValido = false;

    if(productos::validaciones::validarCantidad(id) && productos::validaciones::validarModificarEnum(campo)){

        campoValido = productos::validaciones::validarCampos(campo,modificacion);

        if(campoValido){

            estado = true;

            productos::persistencia::modificarProductoArchivo(id,modificacion,campo);

        }

    }


    return estado;

}

bool productos::gestorProducto::eliminarProducto(const Producto& producto){

    bool estado = false;


    if(productos::validaciones::validarProducto(producto) && productos::validacionSemantica::validarLogicaProducto(producto)){


        if(productos::persistencia::validarExistenciaProducto(producto.nombre)){
            
            estado = true;
            productos::persistencia::eliminarProductoArchivo(producto.id);
        
        }

    }

    return estado;

}


void productos::gestorProducto::mostrarProductos(){
    productos::persistencia::mostrarProducto();
}

void productos::gestorProducto::mostrarProductos(const int& id){

    if(productos::validaciones::validarCantidad(id)){
        productos::persistencia::mostrarProducto(id);
    }


}