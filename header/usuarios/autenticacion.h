#pragma once
#include "usuarios/validaciones.h"
#include "usuarios/user.h"

namespace usuarios{

    namespace autenticacion{

        bool usuarioExiste(const Usuario& user);

        bool esAdmin(const Usuario& user);



    }




}