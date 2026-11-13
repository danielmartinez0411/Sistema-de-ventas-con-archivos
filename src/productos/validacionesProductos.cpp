#include <productos/validacionesProductos.h>
#include <productos/auxiliarProductos.h>
#include <iostream>
#include <regex>

bool productos::validaciones::validarCantidad(const int& cantidad){
    return (cantidad >= 0) ? true : false;
}

bool productos::validaciones::validarCantidad(const double& cantidad){
    return (cantidad >= 0) ? true : false;
}


bool productos::validaciones::patronRegexNombreProducto(const std::string& nombre){

    std::regex patronNombre(R"(^[a-zA-Z][a-zA-Z0-9]{3,14}$)");

    return std::regex_match(nombre,patronNombre);
}



bool productos::validaciones::validarNombre(const std::string& nombre){

    if(nombre.empty()){
        return false;
    }

    return productos::validaciones::patronRegexNombreProducto(nombre);
}

bool productos::validaciones::validarEstado(const ESTADO& estado){
    return (estado == ESTADO::agotado || estado == ESTADO::disponible || estado == ESTADO::pocasUnidades) ? true : false;
}


bool productos::validaciones::validarTodasLasCantidad(const Producto& producto){

    bool idValido = false , canValida = false, canMinValida = false, costoValido = false , precDetValido = false ,precMayValido = false;


    idValido = productos::validaciones::validarCantidad(producto.id);

    canValida = productos::validaciones::validarCantidad(producto.cantidad);

    canMinValida = productos::validaciones::validarCantidad(producto.cantidadMinima);

    costoValido = productos::validaciones::validarCantidad(producto.costo);

    precDetValido = productos::validaciones::validarCantidad(producto.precioDetalle);

    precMayValido = productos::validaciones::validarCantidad(producto.precioPorMayor);


    return idValido && canValida && canMinValida && costoValido && precDetValido && precMayValido;

}

bool productos::validaciones::validarProducto(const productos::Producto& producto){

    bool estadoValido = false,nombreValido = false,cantidadValida = false;

    cantidadValida = productos::validaciones::validarTodasLasCantidad(producto);

   estadoValido = productos::validaciones::validarEstado(producto.estado);

   nombreValido = productos::validaciones::validarNombre(producto.nombre);

   return estadoValido && nombreValido && cantidadValida;


}

bool productos::validaciones::validarCampos(const MODIFICAR& campo, const std::string& modificacion){

    bool campoValido = false;

    std::stringstream cambio;

    switch(campo){

        case MODIFICAR::cantidad :{

            int can;

            cambio << modificacion;

            cambio >> can;


            campoValido = validarCantidad(can);

            break;
        }

        case MODIFICAR::cantidadMinima :{

            int canMin;

            cambio << modificacion;

            cambio >> canMin;


            campoValido = validarCantidad(canMin);

            break;
        }

        case MODIFICAR::costo :{


            double costo;

            cambio << modificacion;

            cambio >> costo;


            campoValido = validarCantidad(costo);

            break;
        }

        case MODIFICAR::precioDetalle :{

            double precioDet;

            cambio << modificacion;

            cambio >> precioDet;


            campoValido = validarCantidad(precioDet);

            break;
        }

        case MODIFICAR::precioPorMayor :{

            double precMay;

            cambio << modificacion;

            cambio >> precMay;


            campoValido = validarCantidad(precMay);
            

            break;
        }

        case MODIFICAR::nombre :{

            campoValido = validarNombre(modificacion);

            break;
        }

        case MODIFICAR::estado :{

            campoValido = validarEstado(productos::auxiliar::convertirTextoAEstado(modificacion));

            break;
        }



    }

    return campoValido;
}


bool productos::validaciones::validarModificarEnum(const MODIFICAR& campo){

    bool campoValido = false;

    switch(campo){

        case MODIFICAR::cantidad :{

            campoValido = true;

            break;
        }

        case MODIFICAR::cantidadMinima :{

            campoValido = true;

            break;
        }

        case MODIFICAR::costo :{


            campoValido = true;

            break;
        }

        case MODIFICAR::precioDetalle :{

            campoValido = true;

            break;
        }

        case MODIFICAR::precioPorMayor :{


            campoValido = true;
            

            break;
        }

        case MODIFICAR::nombre :{

            campoValido = true;

            break;
        }

        case MODIFICAR::estado :{

            campoValido = true;

            break;
        }


    }

    return campoValido;
}