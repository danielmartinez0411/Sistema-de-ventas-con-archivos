#include "usuarios/persistencia.h"
#include <usuarios/serializacion.h>
#include <usuarios/auxiliar.h>
#include <fstream>
#include <cstdlib>
#include <iostream>

bool usuarios::persistencia::inicializarArchivo(){

    std::ifstream archivo("txt/usuarios.txt");
    
    if(!archivo.good()){
        
        archivo.close();

        std::ofstream archivoNuevo("txt/usuarios.txt");

        archivoNuevo.close();

    }

    return true;
}


bool usuarios::persistencia::agregarUsuarioAlArchivo(const Usuario& usuario){

    std::ofstream archivo("txt/usuarios.txt", std::ios_base::app);


    std::string linea  = usuarios::serializacion::convertirUsuarioALinea(usuario);

    if(archivo << linea << "\n"){
        return true;
    }

    archivo.close();
    return false;
}

bool usuarios::persistencia::buscarYObtenerUsuario(const int& id, Usuario& usuario){

    std::ifstream archivo("txt/usuarios.txt");

    std::string linea;

    while(std::getline(archivo,linea)){

        usuarios::Usuario nuevo = usuarios::serializacion::convertirLineaAUsuario(linea);
        
        if(nuevo.id == id){
            usuario = nuevo;
            return true;
        }

    }

    archivo.close();
    return false;
}

bool usuarios::persistencia::eliminarUsuarioArchivo(const int& id){

    std::ifstream archivoOriginal("txt/usuarios.txt");

    std::ofstream archivoCopia("txt/usuariosTemporal.txt");

    std::string linea;
    
    bool resultado = false;

    while(std::getline(archivoOriginal,linea)){

        usuarios::Usuario nuevo = usuarios::serializacion::convertirLineaAUsuario(linea);

        if(nuevo.id != id){
            archivoCopia << linea << "\n";
        }

    }

    archivoCopia.close();
    archivoOriginal.close();

    if(std::remove("txt/usuarios.txt") == 0){
        
        if(std::rename("txt/usuariosTemporal.txt","txt/usuarios.txt") == 0){

            resultado = true;
        
        }
    } 

    return resultado;
}


bool usuarios::persistencia::modificarArchivo(const int& id, const std::string& modificacion, usuarios::CAMPO& campo){

    std::ifstream archivoOriginal("txt/usuarios.txt");
    std::ofstream archivoCopia("txt/usuarioTemporal.txt");

    std::string linea;

    bool resultado = false;

    while(std::getline(archivoOriginal,linea)){

        usuarios::Usuario nuevo = usuarios::serializacion::convertirLineaAUsuario(linea);

        if(nuevo.id != id){
            archivoCopia << linea << "\n";
        }else{

            switch(campo){

                case CAMPO::rol :{

                    archivoCopia << nuevo.id << "," << nuevo.clave << "," << nuevo.nombre << "," << modificacion << "\n";

                    break;
                }

                case CAMPO::nombre : {

                    archivoCopia << nuevo.id << "," << nuevo.clave << "," << modificacion << "," << usuarios::auxiliar::convertirRolATexto(nuevo.rol) << "\n";

                    break;
                }

                case CAMPO::clave : {

                    archivoCopia << nuevo.id << "," << modificacion << "," << nuevo.nombre << "," << usuarios::auxiliar::convertirRolATexto(nuevo.rol) << "\n";

                    break;
                }

            }

        }

    }

    archivoCopia.close();
    archivoOriginal.close();

    if(std::remove("txt/usuarios.txt") == 0){
        
        if(std::rename("txt/usuarioTemporal.txt","txt/usuarios.txt") == 0){

            resultado = true;
        
        }
    } 

    return resultado;
}


bool usuarios::persistencia::validarExistenciaUsuario(const std::string& nombre, const std::string& clave){
    
    std::ifstream archivo("txt/usuarios.txt");

    std::string linea;

    while(std::getline(archivo,linea)){


        usuarios::Usuario nuevo = usuarios::serializacion::convertirLineaAUsuario(linea);

        if(nuevo.clave == clave && nuevo.nombre == nombre){
            return true;
        }



    }

    archivo.close();

    return false;
}

int usuarios::persistencia::mayorID(){

    std::ifstream archivo("txt/usuarios.txt");

    std::string linea;

    int mayor = 0;

    while(std::getline(archivo,linea)){

        usuarios::Usuario nuevo = usuarios::serializacion::convertirLineaAUsuario(linea);

        if(nuevo.id > mayor){
            mayor = nuevo.id;
        }

    }

    return mayor;
}


void usuarios::persistencia::mostrarUsuarios(){

    std::ifstream archivo("txt/usuarios.txt");

    std::string linea;

    while(std::getline(archivo,linea)){
        usuarios::Usuario nuevo = usuarios::serializacion::convertirLineaAUsuario(linea);


        std::cout<<"\n";
        std::cout<<"\nID: "<<nuevo.id<<std::endl;
        std::cout<<"\nNombre: "<<nuevo.nombre<<std::endl;
        std::cout<<"\nClave: "<<nuevo.clave<<std::endl;
        std::cout<<"\nRol: "<< usuarios::auxiliar::convertirRolATexto(nuevo.rol) <<std::endl;
        std::cout<<"\n";

    }


}

void usuarios::persistencia::mostrarUsuarios(const int& id){

    std::ifstream archivo("txt/usuarios.txt");

    std::string linea;

    while(std::getline(archivo,linea)){

        usuarios::Usuario nuevo = usuarios::serializacion::convertirLineaAUsuario(linea);

        if(nuevo.id == id){
            
            std::cout<<"\n";
            std::cout<<"\nID: "<<nuevo.id<<std::endl;
            std::cout<<"\nNombre: "<<nuevo.nombre<<std::endl;
            std::cout<<"\nClave: "<<nuevo.clave<<std::endl;
            std::cout<<"\nRol: " << usuarios::auxiliar::convertirRolATexto(nuevo.rol) <<std::endl;
            std::cout<<"\n";

            break;
        }

    }


}