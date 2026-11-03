#pragma once
#include "user.h"

namespace usuarios{

    namespace auxiliar{

        usuarios::ROL convertirTextoARol(const std::string& userRol);
    
        std::string convertirRolATexto(const ROL& userRol);

        usuarios::ROL convertirEnteroARol(const int& rol);

    }
}