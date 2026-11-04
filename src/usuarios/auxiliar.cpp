#include "usuarios/auxiliar.h"
#include "usuarios/user.h"

usuarios::ROL usuarios::auxiliar::convertirTextoARol(const std::string& userRol){
    return (userRol == "Admin") ? ROL::admin : ROL::normal;
}

std::string usuarios::auxiliar::convertirRolATexto(const ROL& userRol){
    return (userRol == ROL::admin) ? "Admin" : "Normal";
}

usuarios::ROL usuarios::auxiliar::convertirEnteroARol(const int& rol){
    usuarios::ROL nuevo;

    nuevo = static_cast<usuarios::ROL>(rol-1);

    return nuevo;
}