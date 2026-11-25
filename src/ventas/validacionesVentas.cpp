#include <ventas/validacionesVentas.h>
#include <productos/retornar.h>
#include <usuarios/autenticacion.h>
#include <usuarios/funcionalidades.h>
#include <ventas/auxiliarVentas.h>
#include <string>
#include <sstream>

/*

    Validaciones Logicas


*/




bool ventas::validacionesLogicas::validarCantidadVenta(const int& productoID, const int& canVenta){


    int cantidadProducto = productos::retornar::retornarCantidad(productoID);

    return (cantidadProducto >= canVenta) ? true : false;

}


bool ventas::validacionesLogicas::validarPrecioVenta(const int& productoID, const double& precio){

    double costo = productos::retornar::retornarCosto(productoID);


    return (costo <= precio) ? true : false;
}



/*


    Validaciones de sintaxis




*/



bool ventas::validaciones::validarEstadoVenta(const ESTADO& estado){
    return (estado == ESTADO::exitosa || estado == ESTADO::cancelada) ? true : false;
}





bool ventas::validaciones::validarID(const int& ventaID){
    return (ventaID > 0) ? true : false;
}




bool ventas::validaciones::validarTotal(const float& ventaTotal){
    return (ventaTotal >= 0) ? true : false;
}




bool ventas::validaciones::validarVenta(const Venta& venta){

    bool estadoValido = ventas::validaciones::validarEstadoVenta(venta.estado);

    bool idValido = ventas::validaciones::validarID(venta.id);

    bool totalValido = ventas::validaciones::validarTotal(venta.total);

    return estadoValido && idValido && totalValido;
}


bool ventas::validaciones::validarEnumModificar(const MODIFICAR& modificar){

    return (modificar == MODIFICAR::estadoVenta || modificar == MODIFICAR::nombreUsuario || modificar == MODIFICAR::totalVenta) ? true : false;
}




bool ventas::validaciones::validarCampos(const std::string& modificacion, const MODIFICAR& campo){

    bool estado = false;


    if(ventas::validaciones::validarEnumModificar(campo)){

        switch(campo){
    
            case MODIFICAR::nombreUsuario :{
    
                int id = usuarios::funcionalidades::obtenerIdConNombre(modificacion);
    
    
                usuarios::Usuario nuevo;
    
                usuarios::gestorUsuario gestor;
    
                gestor.buscarYObtenerUsuario(id,nuevo);
    
    
                if(usuarios::autenticacion::usuarioExiste(nuevo)){
                    estado = true;
                }
    
                break;
            }
    
            case MODIFICAR::estadoVenta : {
    
                ventas::ESTADO nuevo = ventas::auxiliar::convertirTextoAEstado(modificacion);
    
                if(ventas::validaciones::validarEstadoVenta(nuevo)){
                    estado = true;
                }
    
                break;
            }
    
            case MODIFICAR::totalVenta : {
    
                float venta = 0;
    
                std::stringstream ss(modificacion);
    
                ss >> venta;
    
                if(ventas::validaciones::validarTotal(venta)){
                    estado = true;
                }
                break;
            }
    
    
    
        }

    }


    return estado;
}