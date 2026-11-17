#pragma once
#include "ventas/ventas.h"
#include <string>


namespace ventas{

    namespace serializacion{


        std::string convertirVentaALinea(const ventas::Venta& venta);

        Venta convertirLineaAVenta(const std::string& linea);




    }



}