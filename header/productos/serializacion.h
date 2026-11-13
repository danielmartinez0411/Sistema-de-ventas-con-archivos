#pragma once
#include "productos.h"
#include <string>

namespace productos{

    namespace serializacion{

        productos::Producto convertirLineaAProducto(const std::string& linea);

        std::string convertirProductoALinea(const Producto& producto);



    }


}