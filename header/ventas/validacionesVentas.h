#pragma once
#include <ventas/ventas.h>



namespace ventas{


    namespace validaciones{


        bool validarCantidadVenta(const int& productoID, const int& canVenta);

        bool validarPrecioVenta(const int& productoID, const double& precioVenta);

        bool validarEstadoVenta(const ESTADO& estado);



    }


}