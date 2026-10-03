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


        /*
        

            FUNCIONES CLAVE


        
        */  

        void crearVenta(const Usuarios::Usuario& user);




    };









}