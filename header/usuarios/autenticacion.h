#pragma once
#include "usuarios/validaciones.h"
#include "usuarios/user.h"

namespace usuarios{

    namespace autenticacion{

        bool iniciarSesion(const Usuario& user);

        bool esAdmin(const Usuario& user);



    }




}