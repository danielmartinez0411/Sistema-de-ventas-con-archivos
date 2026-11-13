#include "productos/auxiliarProductos.h"
#include <string>


productos::ESTADO productos::auxiliar::convertirTextoAEstado(const std::string& texto){
    
    productos::ESTADO nuevo;

    if(texto == "Disponible"){
        nuevo = productos::ESTADO::disponible;
    }
 
    if(texto == "Agotado"){
        nuevo = productos::ESTADO::agotado;
    }
 
    if(texto == "Pocas Unidades"){
        nuevo = productos::ESTADO::pocasUnidades;
    }
    
    return nuevo;
}


std::string productos::auxiliar::estadoATexto(const ESTADO& estado){

    std::string texto;


    switch(estado){
        case ESTADO::agotado : texto = "Agotado"; break; 
        case ESTADO::disponible : texto = "Disponible"; break; 
        case ESTADO::pocasUnidades : texto = "Pocas Unidades"; break; 
    }
    
    return texto;
}

productos::ESTADO productos::auxiliar::enteroAEstado(const int& estado){

    productos::ESTADO nuevo;

    switch(estado){

        case 1: nuevo = productos::ESTADO::disponible; break;
        case 2: nuevo = productos::ESTADO::pocasUnidades; break;
        case 3: nuevo = productos::ESTADO::agotado; break;


    }

    return nuevo;
}