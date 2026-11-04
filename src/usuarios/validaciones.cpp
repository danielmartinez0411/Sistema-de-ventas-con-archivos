#include "usuarios/validaciones.h"
#include "usuarios/auxiliar.h"
#include <string>
#include <regex>
#include <iostream>

bool usuarios::validaciones::validarNombreUsuario(const std::string& nombre){

    if(nombre.empty()){
        return false;
    }

    return patronRegexNombre(nombre);

}


bool usuarios::validaciones::validarClaveUsuario(const std::string& clave){

    if(clave.empty()){
        return false;
    }

    if(!validarLongitudClave(clave)){
        return false;
    }


    return patronRegexClave(clave);

}


bool usuarios::validaciones::validarLongitudClave(const std::string& clave){

    int cantidad = 0;

    for(const auto& n : clave){
        cantidad++;
    }

    return (cantidad > 5) ? true : false;

}


bool usuarios::validaciones::validarRolUsuario(const int& userRol){

    ROL rol;

    rol = usuarios::auxiliar::convertirEnteroARol(userRol);

    return (rol == ROL::admin || rol == ROL::normal) ? true : false;
}

bool usuarios::validaciones::validarRolUsuario(const ROL& userRol){
    return (userRol == ROL::admin || userRol == ROL::normal) ? true : false;
}

bool usuarios::validaciones::validarIdUsuario(const int& id){
    return (id > 0) ? true : false;
}


bool usuarios::validaciones::patronRegexNombre(const std::string& nombre){

    std::regex patronNombre(R"(^[a-zA-Z][a-zA-Z0-9_]{5,14}$)");

    return std::regex_match(nombre,patronNombre);
}

bool usuarios::validaciones::patronRegexClave(const std::string& clave){

    std::regex patronClave(R"(^[a-zA-Z][a-zA-Z0-9_]{5,14}$)");

    return std::regex_match(clave,patronClave);
}

bool usuarios::validaciones::validarUsuario(const Usuario& usuario){

    bool nombreValido = false, claveValida = false, rolValido = false;

    if(usuarios::validaciones::validarNombreUsuario(usuario.nombre)){
        nombreValido = true;
    }

    if(usuarios::validaciones::validarClaveUsuario(usuario.clave)){
        claveValida = true;
    }

    if(usuarios::validaciones::validarRolUsuario(usuario.rol)){
        rolValido = true;
    }

    return (nombreValido == true && rolValido == true && claveValida == true) ? true : false;
}