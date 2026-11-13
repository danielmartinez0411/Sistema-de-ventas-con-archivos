#include <usuarios/user.h>
#include <usuarios/validaciones.h>
#include <usuarios/auxiliar.h>
#include <usuarios/serializacion.h>
#include <usuarios/persistencia.h>
#include <iostream>


int usuarios::gestorUsuario::asignarID(){
    return usuarios::persistencia::mayorID() + 1;
}


usuarios::Usuario usuarios::gestorUsuario::crearUsuario(const std::string& nombre, const std::string& clave, const int& userRol){

    bool nombreValido = false, claveValida = false, rolValido = false;

    usuarios::ROL nuevo = usuarios::auxiliar::convertirEnteroARol(userRol);
    
    if(usuarios::validaciones::validarNombreUsuario(nombre)){
        nombreValido = true;
    }
    
    if(usuarios::validaciones::validarClaveUsuario(clave)){
        claveValida = true;
    }
    
    if(usuarios::validaciones::validarRolUsuario(nuevo)){
        rolValido = true;
    }

    if(nombreValido == true && claveValida == true && rolValido == true){
        int id = asignarID();


        usuarios::Usuario nuevoUsuario(id,clave,nombre,nuevo);


        return nuevoUsuario;
    }

    return usuarios::Usuario{};
}

bool usuarios::gestorUsuario::agregarUsuario(const Usuario& usuario){

    bool estado = false;


    if(usuarios::validaciones::validarUsuario(usuario)){


        if(!usuarios::persistencia::validarExistenciaUsuario(usuario.nombre,usuario.clave)){

            estado = true;
    
            usuarios::persistencia::agregarUsuarioAlArchivo(usuario);
            
        }

    }


    return estado;
}

bool usuarios::gestorUsuario::modificarUsuario(const Usuario& usuario, const std::string& modificacion, const CAMPO& campo){

    bool estado = false;

    if(usuarios::validaciones::validarUsuario(usuario) && usuarios::persistencia::validarExistenciaUsuario(usuario.nombre,usuario.clave)){

        bool campoValido =  usuarios::validaciones::validarCampos(campo,modificacion);


        if(campoValido == true){

            estado = true;

            CAMPO nuevo = campo;

            usuarios::persistencia::modificarArchivo(usuario.id,modificacion,nuevo);

            return estado;
        }


    }


    return estado;
}


bool usuarios::gestorUsuario::buscarYObtenerUsuario(const int& userID, Usuario& usuario){


    bool estado = false;

    if(usuarios::validaciones::validarIdUsuario(userID)){
        
        estado = true;
        usuarios::persistencia::buscarYObtenerUsuario(userID,usuario);
    }

    return estado;

}

void usuarios::gestorUsuario::mostrarUsuarios(){
    usuarios::persistencia::mostrarUsuarios();
}

void usuarios::gestorUsuario::mostrarUsuarios(const Usuario& usuario){

    if(usuarios::validaciones::validarUsuario(usuario) && usuarios::persistencia::validarExistenciaUsuario(usuario.nombre,usuario.clave)){


        usuarios::persistencia::mostrarUsuarios(usuario.id);


    }




}

bool usuarios::gestorUsuario::eliminarUsuario(const Usuario& usuario){

    bool estado = false;

    if(usuarios::validaciones::validarUsuario(usuario) && usuarios::persistencia::validarExistenciaUsuario(usuario.nombre,usuario.clave)){
        estado = true;
        usuarios::persistencia::eliminarUsuarioArchivo(usuario.id);
    }

    return estado;
}