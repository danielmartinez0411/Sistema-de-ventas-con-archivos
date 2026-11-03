#pragma once
#include "user.h"


namespace usuarios{

    namespace serializacion{

        usuarios::Usuario convertirLineaAUsuario(const std::string& linea);

        std::string convertirUsuarioALinea(const Usuario& user);

        

    }


}