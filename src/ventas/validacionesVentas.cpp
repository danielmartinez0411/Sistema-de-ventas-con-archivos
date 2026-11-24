#include <ventas/validacionesVentas.h>
#include <productos/retornar.h>


bool ventas::validaciones::validarCantidadVenta(const int& productoID, const int& canVenta){


    int cantidadProducto = productos::retornar::retornarCantidad(productoID);

    return (cantidadProducto >= canVenta) ? true : false;

}


bool ventas::validaciones::validarPrecioVenta(const int& productoID, const double& precio){

    double costo = productos::retornar::retornarCosto(productoID);


    return (costo <= precio) ? true : false;
}

bool ventas::validaciones::validarEstadoVenta(const ESTADO& estado){
    return (estado == ESTADO::exitosa || estado == ESTADO::cancelada) ? true : false;
}