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
                total = 0;
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

        /*
        
        
            FUNCIONES AUXILIARES
        
        
        
        */

        int mayorID();

        inline int asignarId();

        std::string estadoATexto(const ESTADO& estado);

        ESTADO textoAEstado(const std::string& estado);

        std::string productoATexto(const PRODUCTO& estado);

        //Productos::BUSCAR productoABuscar(const PRODUCTO& estado);

        //inline Ventas::PRODUCTO booleanoAProducto(const bool& estado);

        inline bool validarVenta(const std::streampos& posicion);

        void mostrarProductos(const int& ventaID);

        int calcularCantidad(const int& ventaId, const int& productoId);

        std::vector<std::string> obtenerProductos(const int& ventaId);
        
        void agregarProductosArchivo(const int& ventaID,const int& productoID, const PRODUCTO& estado);

        std::streampos validarSiProductoExiste(const int& ventaID, const int& productoID);

        inline std::string obtenerNombreArchivoVenta(const int& ventaID);

        bool validarSiArchivoExiste(const int& ventaID);
        
        
        /*
        
        
        FUNCIONES CLAVE
        
        
        
        */  
       void crearVenta(const std::string& userNombre, const std::string& userClave);
       
       void agregarProductos(const int& ventaID, const int& productoID, const PRODUCTO& estado);
       
       void mostrarVenta();
       
       float totalVenta(const int& ventaID);
       
       void crearArchivo(const int& id);
       
       bool validarPorMayorArchivo(const int& ventaID, const int& productoID);

       void eliminarProducto(const int& ventaID, const int& productoId);

       void eliminarVenta(const int& ventaID);

       void mostrarPorEstado(const ESTADO& estado);

       void modificarEstado(const int& ventaID, const ESTADO& nuevoEstado);
       
       /*
        
        
        NECESITO CREAR:

        FUNCION QUE CALCULE EL TOTAL, PARA CUANDO VAYA AGREGAR PRODUCTOS * hecho

        MOSTRAR LAS VENTAS EN PANTALLA * hecho

        MOSTRAR POR ESTADO * hecho

        MODIFICAR VENTAS

        MODIFICAR ESTADOS

        ELIMINAR VENTAS * hecho

        ETC.
        
        
        
        
        */




    };









}