#pragma once
#include <vector>
#include <string>
#include "user.h"
#include "productos.h"



namespace Ventas{


    enum class ESTADO{
        exitosa,
        cancelada
    };

    struct Venta{

        int id = 0;
        Usuarios::Usuario usuario;
        float total = 0;
        ESTADO estado;
        std::vector<Productos::Producto> productos;


            Venta(const Usuarios::Usuario user, const ESTADO& estadoVenta):
            usuario(user), estado(estadoVenta){}




    };

    
    class gestorVentas{

        public:

        /*
        
        
            FUNCIONES AUXILIARES
        
        
        
        */

        int mayorID();

        inline int asignarId();

        std::string estadoATexto(ESTADO estado);

        inline bool validarVenta(const std::streampos& posicion);

        void mostrarProductos(const std::string& campoProductos);


        /*
        

            FUNCIONES CLAVE


        
        */  

        std::streampos busquedaPorId(const int& ventaID);

        void crearVenta(const std::string& userNombre, const std::string& userClave);

        void agregarProductos(const int& ventaID, const int& productoID);

        void mostrarVenta();


        /*
        
        
        NECESITO CREAR:

        FUNCION QUE CALCULE EL TOTAL, PARA CUANDO VAYA AGREGAR PRODUCTOS

        FUNCIONES QUE RECIBA LA LINEA CAMPOPRODUCTO Y LA DESCONSTRUYA PASO A PASO PARA MOSTRARLA EN PANTALLA

        MOSTRAR LAS VENTAS EN PANTALLA

        MOSTRAR POR ESTADO

        MODIFICAR VENTAS

        MODIFICAR ESTADOS

        ELIMINAR VENTAS

        ETC.
        
        
        
        
        */




    };









}