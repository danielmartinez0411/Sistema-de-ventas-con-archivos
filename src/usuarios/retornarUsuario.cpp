#include "usuarios/retornarUsuario.h"
#include <string>


std::string usuarios::retornar::retornarNombre(const int& id){

    usuarios::gestorUsuario nuevo;
    usuarios::Usuario nuevoUsuario;

    nuevo.buscarYObtenerUsuario(id,nuevoUsuario);

    return nuevoUsuario.nombre;
}

std::string usuarios::retornar::retornarClave(const int& id){

    usuarios::gestorUsuario nuevo;
    usuarios::Usuario nuevoUsuario;

    nuevo.buscarYObtenerUsuario(id,nuevoUsuario);

    return nuevoUsuario.clave;
}

usuarios::ROL usuarios::retornar::retornarRol(const int& id){

    usuarios::gestorUsuario nuevo;
    usuarios::Usuario nuevoUsuario;

    nuevo.buscarYObtenerUsuario(id,nuevoUsuario);

    return nuevoUsuario.rol;
}