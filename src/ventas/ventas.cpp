#include <ventas/ventas.h>
#include <ventas/validacionesVentas.h>
#include <usuarios/validaciones.h>
#include <ventas/persistenciaVentas.h>
#include <usuarios/autenticacion.h>


int ventas::gestorVentas::asignarID(){
    return ventas::persistencia::mayorID() + 1;
}


ventas::Venta ventas::gestorVentas::crearVenta(const usuarios::Usuario& usuario, const ESTADO& estado){

    
    
    if(usuarios::validaciones::validarUsuario(usuario) && ventas::validaciones::validarEstadoVenta(estado)){
        
        int id = asignarID();

        ventas::Venta nuevo(id,usuario,0,estado);


        return nuevo;
    }


    return ventas::Venta{};
}

bool ventas::gestorVentas::buscarYObtenerVenta(const Venta& ventaOriginal, Venta& venta){

    bool estado = false;


    if(usuarios::autenticacion::usuarioExiste(ventaOriginal.usuario) && ventas::validaciones::validarVenta(ventaOriginal)){

        estado = ventas::persistencia::buscarYObtenerVenta(ventaOriginal.id,venta);
    }

    return estado;
}



bool ventas::gestorVentas::agregarVenta(const Venta& venta){

    bool estado = false;


    if(usuarios::autenticacion::usuarioExiste(venta.usuario) && ventas::validaciones::validarVenta(venta)){


        estado = ventas::persistencia::agregarVentaArchivo(venta);


    }

    return estado;
}



bool ventas::gestorVentas::eliminarVenta(const Venta& venta){

    bool estado = false;

    if(usuarios::autenticacion::usuarioExiste(venta.usuario) && ventas::validaciones::validarVenta(venta)){

        estado = ventas::persistencia::eliminarVenta(venta.id);
    }
    return estado;
}


bool ventas::gestorVentas::modificarVenta(const Venta& venta, const std::string& modificacion, const MODIFICAR& campo){

    bool estado = false;


    if(usuarios::autenticacion::usuarioExiste(venta.usuario) && ventas::validaciones::validarVenta(venta)){


        if(ventas::validaciones::validarEnumModificar(campo)){


            if(ventas::validaciones::validarCampos(modificacion,campo)){
    
                estado = ventas::persistencia::modificarVenta(venta.id,modificacion,campo);
    
    
            }
    
    
    
        }







    }

    
    return estado;
}


void ventas::gestorVentas::mostrarVentas(){
    ventas::persistencia::mostrarVenta();
}

void ventas::gestorVentas::mostrarVentas(const Venta& venta){

    if(usuarios::autenticacion::usuarioExiste(venta.usuario) && ventas::validaciones::validarVenta(venta)){


        ventas::persistencia::mostrarVenta(venta.id);



    }




}