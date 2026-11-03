#pragma once
#include <usuarios/user.h>

namespace usuarios{

    namespace persistencia{

        bool inicializarArchivo();

        bool agregarUsuarioAlArchivo(const usuarios::Usuario& usuario);

        bool buscarYObtenerUsuario(const int& id, usuarios::Usuario& usuario);

        bool eliminarUsuarioArchivo(const int& id);

        bool modificarArchivo(const int& id, const std::string& modificacion, usuarios::CAMPO& campo);

        bool validarExistenciaUsuario(const std::string& nombre, const std::string& clave);

        int mayorID();

        void mostrarUsuarios();

        void mostrarUsuarios(const int& id);



    }



}