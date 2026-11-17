#include <usuarios/user.h>
#include <usuarios/funcionalidades.h>



int usuarios::funcionalidades::obtenerIdConNombre(const std::string& nombreUsuario){

    usuarios::gestorUsuario nuevo;

    int cantidad = nuevo.asignarID(), id = 0;

    for(int i = 0; i < cantidad; i++){

        usuarios::Usuario usuario;

        nuevo.buscarYObtenerUsuario(i+1,usuario);


        if(usuario.nombre == nombreUsuario){

            id = usuario.id;
            return id;
        }




    }

    return id;

}


usuarios::Usuario usuarios::funcionalidades::obtenerUsuarioConNombre(const std::string& nombreUsuario){


    int id = usuarios::funcionalidades::obtenerIdConNombre(nombreUsuario);


    if(id != 0){

        usuarios::Usuario nuevo;
        usuarios::gestorUsuario gestor;

        gestor.buscarYObtenerUsuario(id,nuevo);


        return nuevo;



    }else{
        return usuarios::Usuario{};
    }



}