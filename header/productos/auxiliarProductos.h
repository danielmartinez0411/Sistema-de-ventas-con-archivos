#pragma once
#include "productos/productos.h"
#include <string>


namespace productos{

    namespace auxiliar{

        productos::ESTADO convertirTextoAEstado(const std::string& texto);

        std::string estadoATexto(const ESTADO& estado);

    }





}