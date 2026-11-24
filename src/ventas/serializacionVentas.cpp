#include <string>
#include <sstream>
#include <iostream>
#include <ventas/serializacionVentas.h>
#include <usuarios/funcionalidades.h>
#include <ventas/auxiliarVentas.h>

ventas::Venta ventas::serializacion::convertirLineaAVenta(const std::string& linea){

    std::stringstream ss(linea);

    int id = 0;
    float total;
    std::string campoNom,campoId,campoTotal,campoEstado,nombre, estado;

    std::getline(ss,campoId,',');
    std::getline(ss,campoNom,',');
    std::getline(ss,campoTotal,',');
    std::getline(ss,campoEstado);

    std::stringstream cambio;

    cambio << campoId << " " << campoNom << " " << campoTotal << " " << campoEstado;

    cambio >> id >> nombre >> total >> estado;

    usuarios::Usuario nuevo = usuarios::funcionalidades::obtenerUsuarioConNombre(nombre);

    ventas::ESTADO nuevoEstado = ventas::auxiliar::convertirTextoAEstado(estado);

    ventas::Venta nuevaVenta(id,nuevo,total,nuevoEstado);

    return nuevaVenta;
}

std::string ventas::serializacion::convertirVentaALinea(const Venta& venta){

    std::stringstream ss;

    ss << venta.id << "," << venta.usuario.nombre << "," << venta.total << "," << ventas::auxiliar::convertirEstadoATexto(venta.estado) << "\n";

    return ss.str();
}