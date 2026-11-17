#pragma once
#include <ventas/ventas.h>

namespace ventas{

    namespace auxiliar{

        ventas::ESTADO convertirEnteroAEstado(const int& estado);

        ventas::ESTADO convertirTextoAEstado(const std::string& estado);

        std::string convertirEstadoATexto(const ESTADO& estado);


    }


}