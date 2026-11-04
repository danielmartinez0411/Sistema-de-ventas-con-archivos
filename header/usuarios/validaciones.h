#pragma once
#include "user.h"
#include <string>

namespace usuarios{

    namespace validaciones{

        bool validarNombreUsuario(const std::string& nombre);

        bool validarClaveUsuario(const std::string& clave);

        bool validarLongitudClave(const std::string& clave);

        bool validarRolUsuario(const int& userRol);
        
        bool validarRolUsuario(const ROL& userRol);

        bool validarIdUsuario(const int& id);

        bool patronRegexNombre(const std::string& nombre);

        bool patronRegexClave(const std::string& clave);

        bool validarUsuario(const Usuario& usuario);


    }


}