#include "usuarios/autenticacion.h"
#include "usuarios/persistencia.h"
#include "usuarios/validaciones.h"

bool usuarios::autenticacion::iniciarSesion(const Usuario& user){

    bool estado = false;


    if(usuarios::validaciones::validarUsuario(user) && usuarios::persistencia::validarExistenciaUsuario(user.nombre,user.clave)){
        estado = true;
    }

    return estado;
}

bool usuarios::autenticacion::esAdmin(const Usuario& user){
    return (user.rol == usuarios::ROL::admin) ? true : false;
}