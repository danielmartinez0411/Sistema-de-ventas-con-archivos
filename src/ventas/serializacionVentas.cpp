#include <string>
#include <sstream>
#include <ventas/serializacionVentas.h>
#include <usuarios/funcionalidades.h>
#include <ventas/auxiliarVentas.h>

ventas::Venta ventas::serializacion::convertirLineaAVenta(const std::string& linea){

    std::stringstream ss(linea);

    int id = 0;
    float total;
    std::string nombre, estado;
    
    ss >> id;

    std::getline(ss,nombre,',');

    ss >> total >> estado;


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