#include "productos/validacionSemantica.h"
#include "productos/productos.h"


bool productos::validacionSemantica::validarCantidadYCantidadMinima(const int& canMin, const int& can){
    return (can > canMin);
}

bool productos::validacionSemantica::validarCostoYPrecio(const double& costo, const double& precDet, const double& precMay){
    return (precDet > costo && precMay > costo);
}

bool productos::validacionSemantica::validarPrecioDetYPrecioMay(const double& precDet, const double& precMay){
    return (precDet > precMay);
}

bool productos::validacionSemantica::validarLogicaProducto(const Producto& producto){

    bool cantidadValida = false, costoValido = false, preciosValidos = false;

    preciosValidos = validarPrecioDetYPrecioMay(producto.precioDetalle, producto.precioPorMayor);

    cantidadValida = validarCantidadYCantidadMinima(producto.cantidadMinima,producto.cantidad);

    costoValido = validarCostoYPrecio(producto.costo,producto.precioDetalle,producto.precioPorMayor);


    return cantidadValida && costoValido && preciosValidos;

}