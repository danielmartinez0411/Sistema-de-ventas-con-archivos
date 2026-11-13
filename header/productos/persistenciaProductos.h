#pragma once
#include "productos/productos.h"



namespace productos{

    namespace persistencia{

        bool inicializarArchivo();

        bool agregarProductoAlArchivo(const Producto& producto);

        bool buscarYObtenerProducto(const int& id, Producto& producto);

        bool eliminarProductoArchivo(const int& id);

        bool modificarProductoArchivo(const int& id, const std::string& modificacion, const productos::MODIFICAR& campo);

        std::string modificarSwitch(const Producto& producto, const std::string& modificacion, const MODIFICAR& campo);

        bool validarExistenciaProducto(const std::string& nombre);

        int mayorID();

        void mostrarProducto();

        void mostrarProducto(const int& id);







    }



}