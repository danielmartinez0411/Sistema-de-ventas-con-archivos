#pragma once
#include <string>

namespace Usuarios{

    enum class ROL{
        normal,
        admin
    };

    enum class RETORNAR{
        nombre,
        clave,
        rol
    };


    struct Usuario{

        int id = 0;
        std::string clave = "";
        std::string nombre = "";
        ROL rol;

            Usuario(const int& userId, const std::string& userClav, const std::string& userNom, const ROL& userRol){
                id = userId;
                clave = userClav;
                nombre = userNom;
                rol = userRol;
            }


    };



    class gestorUsuario{

        public:

            /*
            


                Funciones Auxiliares
            
            
            
            */


        
            inline int asignarID();
        
            inline ROL asignarRol(const int& rol);

            inline ROL textoARol(const std::string& rol);

            inline std::string rolATexto(ROL rol);

            int mayorID();

            bool validarExistencia(const std::string& clave, const std::string& nombre);

            inline bool usuarioEncontrado(const std::streampos& posicion);
            
            
            /*  
            
            
            
            Funciones Clave
            
            
            
            */
           
           std::streampos busquedaPorId(const int& id);
           
           void agregarUsuario(const std::string& userClave, const std::string& userNombre, const int& userRol);
           
           void mostrarUsuarios();
           
           void modificarUsuario(const int& id, const std::string& campoViejo, const std::string& campoNuevo);
           
           void modificarUsuario(const int& id, const ROL& rolNuevo);
           
           void eliminarUsuario(const int& id);
           
           

            /*
            
            
            
                Funciones de conexion
            
            
            
            */




           bool validarAdmin(const int& id);

           std::string retornar(const int& id, const RETORNAR& estado);

           int retornarId(const std::string& nombre, const std::string& clave);



        };
        

}