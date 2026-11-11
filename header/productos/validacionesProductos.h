#pragma once
#include "productos/productos.h"



namespace productos{

    namespace validaciones{


        bool validarCantidad(const int& cantidad);

        bool validarCantidad(const double& cantidad);

        bool patronRegexNombreProducto(const std::string& nombre);

        bool validarNombre(const std::string& nombre);

        bool validarEstado(const ESTADO& estado);
        
        bool validarTodasLasCantidad(const Producto& producto);

        bool validarProducto(const Producto& producto);




    }




}
