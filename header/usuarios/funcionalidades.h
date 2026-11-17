#pragma once
#include <usuarios/user.h>

namespace usuarios{

    namespace funcionalidades{

        int obtenerIdConNombre(const std::string& nombreUsuario);

        usuarios::Usuario obtenerUsuarioConNombre(const std::string& nombreUsuario);


    }



}