#include <ventas/auxiliarVentas.h>
#include <string>

ventas::ESTADO ventas::auxiliar::convertirEnteroAEstado(const int& estado){
    return static_cast<ventas::ESTADO>(estado-1);
}

ventas::ESTADO ventas::auxiliar::convertirTextoAEstado(const std::string& nombre){

    ventas::ESTADO nuevo;

    if(nombre == "Exitosa"){
        nuevo = ESTADO::exitosa;
    }else{
        nuevo = ESTADO::cancelada;
    }

    return nuevo;
}

std::string ventas::auxiliar::convertirEstadoATexto(const ESTADO& estado){
    return (estado == ESTADO::exitosa) ? "Exitosa" : "Cancelada";
}