#pragma once
#include <string>


namespace Productos{

    enum class ESTADO{
        disponible,
        agotado,
        pocasUnidades
    };

    enum class BUSCAR{
        precioDetalle,
        precioMayor
    };

    struct Producto{
        int id = 0;
        int cantidad = 0;
        int cantidadMinima = 0;
        double costo = 0;
        double precioDetalle = 0;
        double precioPorMayor = 0;
        std::string nombre = "";
        ESTADO estado = ESTADO::agotado;

            Producto(const int& userId, const int& can, const int& canMin, const double& cost, const double& precDet, const double& precMay, const std::string& nom, const ESTADO& estadoProd){
                
                id = userId;
                cantidad = can;
                cantidadMinima = canMin;
                costo = cost;
                precioDetalle = precDet;
                precioPorMayor = precMay;
                nombre = nom;
                estado = estadoProd;

            }


    };

    class gestorProducto{

        public:

        /*
        
        
            Funciones Auxiliares
        
        
        
        
        */

        inline bool productoEncontrado(std::streampos posicion);

        int mayorID();

        inline int asignarID();

        inline ESTADO asignarEstado(const int& can);

        bool validarExistencia(const std::string& nom);

        std::string estadoATexto(const ESTADO& estado);

        BUSCAR verificarPrecio(const int& id, const float& precio);

        
        /*
        
        
        
        FUNCIONES CLAVE
        
        
        
        */
       
       std::streampos busquedaPorId(const int& id);
       
       void agregarProducto(const int& can, const int& canMin, const double& cost, const double& precDet, const double& precMayor, const std::string& nom);
       
       void mostrarProductos();
       
       void mostrarProductos(const int& id);
       
       void mostrarProductosPrecio(const double& precio, const BUSCAR& busqueda);
       
       void mostrarRangoDePrecios(const double& precInicial, const double& precFinal, const BUSCAR& busqueda);

       void busquedaPorNombre(const std::string& nombreProducto);

       void modificarProducto(const int& id, const std::string& campoViejo, const std::string& campoNuevo);

       void eliminarProducto(const int& id);

        /*

            faltan las funciones de enlace / verificaciones de cantidad, estado, etc.

            eliminar productos.

            por el momento solo se me ocurren esas.

            ah, mostrar productos segun el estado, etc

        
        */

        int obtenerIdConNombre(const std::string& nombre);

        std::string obtenerNombreConId(const int& id);

        std::string retornarNombre(const int& id);

        float calcularTotal(const std::string& nombreProducto, const float& total, const BUSCAR& buscar);




    };




}