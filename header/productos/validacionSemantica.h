#pragma once
#include "productos/productos.h"

namespace productos{

    namespace validacionSemantica{


        bool validarCantidadYCantidadMinima(const int& canMin, const int& can);

        bool validarPrecioDetYPrecioMay(const double& precDet, const double& precMay);

        bool validarCostoYPrecio(const double& costo, const double& precioDet, const double& precMay);

        bool validarLogicaProducto(const Producto& producto);


    }



}