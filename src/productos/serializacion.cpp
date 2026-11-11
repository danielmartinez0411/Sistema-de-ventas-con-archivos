#include "productos/serializacion.h"
#include "productos/auxiliarProductos.h"
#include <sstream>
#include <string>
#include <iostream>


productos::Producto productos::serializacion::convertirLineaAProducto(const std::string& linea){

    std::stringstream ss(linea);

    std::string campoNombre, campoEstado, campoId, campoCan, campoCanMin, campoCosto, campoPrecDet, campoPrecMay;
    int id = 0, can = 0,canMin = 0;
    double costo = 0,precDet = 0,precMay = 0;

    std::getline(ss,campoId,',');
    std::getline(ss,campoCan,',');
    std::getline(ss,campoCanMin,',');
    std::getline(ss,campoCosto,',');
    std::getline(ss,campoPrecDet,',');
    std::getline(ss,campoPrecMay,',');
    std::getline(ss,campoNombre,',');
    std::getline(ss,campoEstado);


    std::stringstream cambio;

    cambio << campoId << " " << campoCan << " " << campoCanMin  <<" " << campoCosto << " " << campoPrecDet << " " << campoPrecMay;


    cambio >> id >> can >> canMin >> costo >> precDet >> precMay;


    productos::Producto nuevo(id,can,canMin,costo,precDet,precMay,campoNombre,productos::auxiliar::convertirTextoAEstado(campoEstado));


    return nuevo;


}