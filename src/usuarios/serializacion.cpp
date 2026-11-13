#include "usuarios/serializacion.h"
#include "usuarios/auxiliar.h"
#include <sstream>
#include <string>


usuarios::Usuario usuarios::serializacion::convertirLineaAUsuario(const std::string& linea){
    
    std::stringstream ss(linea);

    std::string campoId, campoClave, campoNom, campoRol;

    int id;

    std::getline(ss,campoId,',');
    std::getline(ss,campoClave,',');
    std::getline(ss,campoNom,',');
    std::getline(ss,campoRol);

    std::stringstream cambio(campoId);

    cambio >> id;


    usuarios::Usuario nuevoUsuario(id,campoClave,campoNom, usuarios::auxiliar::convertirTextoARol(campoRol));


    return nuevoUsuario;
}


std::string usuarios::serializacion::convertirUsuarioALinea(const Usuario& user){

    std::stringstream ss;

    ss << user.id << "," <<user.clave << "," << user.nombre << "," << usuarios::auxiliar::convertirRolATexto(user.rol) << "\n";

    return ss.str();

}