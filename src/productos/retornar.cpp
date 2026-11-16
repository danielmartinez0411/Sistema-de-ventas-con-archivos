#include "productos/retornar.h"
#include "productos/productos.h"


int productos::retornar::retornarCantidad(const int& id){
    
    productos::Producto nuevo;
    productos::gestorProducto nuevoGestor;

    nuevoGestor.buscarYObtenerProducto(id,nuevo);

    return nuevo.cantidad;
}

int productos::retornar::retornarCantidadMinima(const int& id){
    
    productos::Producto nuevo;
    productos::gestorProducto nuevoGestor;

    nuevoGestor.buscarYObtenerProducto(id,nuevo);

    return nuevo.cantidadMinima;
}

double productos::retornar::retornarCosto(const int& id){

    productos::Producto nuevo;
    productos::gestorProducto nuevoGestor;

    nuevoGestor.buscarYObtenerProducto(id,nuevo);

    return nuevo.costo;
}

double productos::retornar::retornarPrecioDetalle(const int& id){

    productos::Producto nuevo;
    productos::gestorProducto nuevoGestor;

    nuevoGestor.buscarYObtenerProducto(id,nuevo);

    return nuevo.precioDetalle;
}

double productos::retornar::retornarPrecioMayoreo(const int& id){

    productos::Producto nuevo;
    productos::gestorProducto nuevoGestor;

    nuevoGestor.buscarYObtenerProducto(id,nuevo);

    return nuevo.precioPorMayor;
}

std::string productos::retornar::retornarNombre(const int& id){

    productos::Producto nuevo;
    productos::gestorProducto nuevoGestor;

    nuevoGestor.buscarYObtenerProducto(id,nuevo);

    return nuevo.nombre;
}

productos::ESTADO productos::retornar::retornarEstado(const int& id){

    productos::Producto nuevo;
    productos::gestorProducto nuevoGestor;

    nuevoGestor.buscarYObtenerProducto(id,nuevo);

    return nuevo.estado;

}