#pragma once
#include <string>


namespace productos{

    enum class ESTADO{
        disponible,
        agotado,
        pocasUnidades
    };

    enum class BUSCAR{
        precioDetalle,
        precioMayor
    };

    enum class MODIFICAR{
        nombre,
        cantidad,
        cantidadMinima,
        costo,
        precioDetalle,
        precioPorMayor,
        estado
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


            Producto(){
                id = 0;
                cantidad = 0;
                cantidadMinima = 0;
                costo = 0;
                precioDetalle = 0;
                precioPorMayor = 0;
                nombre = "";
                estado = ESTADO::agotado;
            }


    };

    class gestorProducto{

        public:

        int asignarID();

        Producto crearProducto(const int& can, const int& canMin, const double& costo, const double& precDet, const double& precMay, const std::string& nombre, const int& estadoProducto);

        bool agregarProductoArchivo(const Producto& producto);

        bool buscarYObtenerProducto(const int& id, Producto& producto);

        bool modificarProducto(const int& id, const std::string& modificacion, const MODIFICAR& campo);

        bool eliminarProducto(const Producto& producto);

        void mostrarProductos();
    
        void mostrarProductos(const int& id);


    };




}