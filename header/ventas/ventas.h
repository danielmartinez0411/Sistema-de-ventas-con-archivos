#pragma once
#include <vector>
#include <string>
#include "usuarios/user.h"
#include "productos/productos.h"



namespace ventas{


    enum class ESTADO{
        exitosa,
        cancelada
    };


    enum class PRODUCTO{
        porMayor,
        alDetalle
    };

    enum class MODIFICAR{
        nombreUsuario,
        totalVenta,
        estadoVenta
    };


    struct Venta{

        int id = 0;
        usuarios::Usuario usuario;
        float total = 0;
        ESTADO estado;


            Venta(){
                id = 0;
                usuario = {};
                total = -1;
                estado = ESTADO::cancelada;
            }

            Venta(const int& ventaID, const usuarios::Usuario& user, const float& totalVenta, const ESTADO& estadoVenta){
                id = ventaID;
                usuario = user;
                total = totalVenta;
                estado = estadoVenta;
            }




    };

    
    class gestorVentas{

        public:

        int asignarID();

        Venta crearVenta(const usuarios::Usuario& usuario, const ESTADO& estado);

        bool agregarVenta(const Venta& venta);

        bool buscarYObtenerVenta(const Venta& ventaOriginal, Venta& venta);

        bool modificarVenta(const Venta& venta, const std::string& modificacion, const MODIFICAR& campo);

        bool eliminarVenta(const Venta& venta);

        void mostrarVentas();

        void mostrarVentas(const Venta& venta);
        

    };









}