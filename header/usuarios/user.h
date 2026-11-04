#pragma once
#include <string>

namespace usuarios{

    enum class ROL{
        normal,
        admin
    };

    enum class CAMPO{
        nombre,
        clave,
        rol
    };


    struct Usuario{

        int id;
        std::string clave;
        std::string nombre;
        ROL rol;

            Usuario(const int& userId, const std::string& userClav, const std::string& userNom, const ROL& userRol){
                id = userId;
                clave = userClav;
                nombre = userNom;
                rol = userRol;
            }

            Usuario(){
                id = 0;
                clave = "";
                nombre = "";
                rol = ROL::normal;
            }


    };



    class gestorUsuario{

        public:

            int asignarID();

            Usuario crearUsuario(const std::string& nombre, const std::string& clave, const int& userRol);

            bool agregarUsuario(const Usuario& usuario);

            bool modificarUsuario(const Usuario& user, const std::string& modificacion, const CAMPO& campo);

            bool buscarYObtenerUsuario(const int& userID, Usuario& usuario);

            void mostrarUsuarios();

            void mostrarUsuarios(const Usuario& user);

            bool eliminarUsuario(const Usuario& user);


        };
        

}