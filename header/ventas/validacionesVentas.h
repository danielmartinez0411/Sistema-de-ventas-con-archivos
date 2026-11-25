#pragma once
#include <ventas/ventas.h>
#include <string>



namespace ventas{

    namespace validacionesLogicas{

        bool validarCantidadVenta(const int& productoID, const int& canVenta);
    
        bool validarPrecioVenta(const int& productoID, const double& precioVenta);


    }


    namespace validaciones{



        bool validarEstadoVenta(const ESTADO& estado);

        bool validarID(const int& ventaID);

        bool validarTotal(const float& ventaTotal);

        bool validarVenta(const Venta& venta);

        bool validarCampos(const std::string& modificacion, const MODIFICAR& campo);

        bool validarEnumModificar(const MODIFICAR& modificar);


    }


}