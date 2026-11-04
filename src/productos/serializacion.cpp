#include "productos/serializacion.h"
#include <sstream>



productos::Producto productos::serializacion::convertirLineaAProducto(const std::string& linea){

    std::stringstream ss(linea);

    std::string campoId, campoCan, campoCanMin, campoCosto, campoPrec, campoPrecMay, campoNombre, campoEstado;

    std::getline(ss,campoId,',');
    std::getline(ss,campoCan,',');
    std::getline(ss,campoCanMin,',');
    std::getline(ss,campoCosto,',');
    std::getline(ss,campoPrec,',');
    std::getline(ss,campoPrecMay,',');
    std::getline(ss,campoNombre,',');
    std::getline(ss,campoEstado);

    int id;

    std::stringstream cambio(campoId);

    cambio >> id;


    /*
    
        Encontrar la forma de convertir cada dato en su tipo para crear la serializacion.

        idea actual: utilizar el operador >>-
    
    
    */


}