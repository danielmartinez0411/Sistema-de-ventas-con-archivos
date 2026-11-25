#pragma once
#include <ventas/ventas.h>



namespace ventas{

    namespace persistencia{

        bool inicializarArchivo();

        bool agregarVentaArchivo(const Venta& venta);

        bool buscarYObtenerVenta(const int& ventaID, Venta& venta);

        bool modificarVenta(const int& ventaID, const std::string& modificacion, const MODIFICAR& campo);

        bool eliminarVenta(const int& ventaID);

        void mostrarVenta();

        void mostrarVenta(const int& ventaID);

        std::string modificarSwitch(const Venta& venta, const std::string& modificacion, const MODIFICAR& campo);

        int mayorID();
    }




}