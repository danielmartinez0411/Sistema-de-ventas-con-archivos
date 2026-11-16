#include "productos/productos.h"
#include <string>


namespace productos{

    namespace retornar{


        int retornarCantidad(const int& id);

        int retornarCantidadMinima(const int& id);

        double retornarCosto(const int& id);

        double retornarPrecioDetalle(const int& id);

        double retornarPrecioMayoreo(const int& id);

        std::string retornarNombre(const int& id);

        productos::ESTADO retornarEstado(const int& id);




    }





}