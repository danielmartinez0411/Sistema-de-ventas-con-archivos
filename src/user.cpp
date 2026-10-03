#include "user.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>


/*
=============================================================


FUNCIONES AUXILIARES


=============================================================
*/


inline bool Usuarios::gestorUsuario::usuarioEncontrado(const std::streampos& posicion){
    return (posicion == -1) ? false : true;
}



int Usuarios::gestorUsuario::mayorID(){

    std::ifstream archivo("txt/usuario.txt");

    int mayor = 0, id = 0;

    std::string campoId,campoClav,campoNom,campoRol,linea;

    while(std::getline(archivo,linea)){

        std::stringstream ss(linea);

        std::getline(ss,campoId,',');
        std::getline(ss,campoClav,',');
        std::getline(ss,campoNom,',');
        std::getline(ss,campoRol);

        id = std::stoi(campoId);

        if(id > mayor){
            mayor = id;
        }





    }


    archivo.close();
    return mayor;

}




inline int Usuarios::gestorUsuario::asignarID(){

    return mayorID() + 1;

}


inline Usuarios::ROL Usuarios::gestorUsuario::asignarRol(const int& numeroRol ){

    Usuarios::ROL rol;

    rol = static_cast<Usuarios::ROL>(numeroRol-1);


    return rol;

}


inline std::string Usuarios::gestorUsuario::rolATexto(ROL rol){
    return (rol == Usuarios::ROL::admin) ? "Admin" : "Normal";

}


inline Usuarios::ROL Usuarios::gestorUsuario::textoARol(const std::string& rol){
   return (rol == "Admin") ? ROL::admin : ROL::normal;
}




bool Usuarios::gestorUsuario::validarExistencia(const std::string& clave, const std::string& nombre){

    std::ifstream archivo("txt/usuario.txt");

    std::string campoId,campoClav,campoNom,campoRol,linea;

    while(std::getline(archivo,linea)){

        std::stringstream ss(linea);

        std::getline(ss,campoId,',');
        std::getline(ss,campoClav,',');
        std::getline(ss,campoNom,',');
        std::getline(ss,campoRol);

        if(campoClav == clave || campoNom == nombre){
            return true;
        }





    }







    archivo.close();
    return false;

}


/*
=============================================================


FUNCIONES CLAVE


=============================================================
*/


std::streampos Usuarios::gestorUsuario::busquedaPorId(const int& id){

    std::ifstream archivo("txt/usuario.txt");

    std::streampos posicion;

    std::string campoId,campoClav,campoNom,campoRol,linea;

    int userID;

    while(archivo){

        posicion = archivo.tellg();

        std::getline(archivo,linea);

        std::stringstream ss(linea);
        
        std::getline(ss,campoId,',');
        std::getline(ss,campoClav,',');
        std::getline(ss,campoNom,',');
        std::getline(ss,campoRol);
        
        std::stringstream string(campoId);
        string >> userID;

        if(id == userID){
            return posicion;
        }



    }

    archivo.close();
    return -1;

}



void Usuarios::gestorUsuario::agregarUsuario(const std::string& userClave, const std::string& userNombre, const int& userRol){

    std::ofstream archivo("txt/usuario.txt", std::ios_base::app);

    if(validarExistencia(userClave,userNombre) == false){

        
            int userId = gestorUsuario::asignarID();
            Usuarios::ROL rolUsuario = asignarRol(userRol);
        
            Usuarios::Usuario nuevo(userId,userClave,userNombre,rolUsuario);
        
            archivo << nuevo.id << "," << nuevo.clave << "," << nuevo.nombre <<"," << rolATexto(nuevo.rol) <<"\n";


    }else{
        std::cout<<"\n\t=======ALERTA======="<<std::endl;
        std::cout<<"\tEL USUARIO YA EXISTE"<<std::endl;
    }


    archivo.close();
}

void Usuarios::gestorUsuario::mostrarUsuarios(){

    std::ifstream archivo("txt/usuario.txt");

    std::string linea, campoId, campoClave,campoNom,campoRol;

    while(std::getline(archivo,linea)){

        std::stringstream ss(linea);

        std::getline(ss,campoId,',');
        std::getline(ss,campoClave,',');
        std::getline(ss,campoNom,',');
        std::getline(ss,campoRol);


        std::cout<<"\nID: "<<campoId;
        std::cout<<"\nClave: "<<campoClave;
        std::cout<<"\nNombre: "<<campoNom;
        std::cout<<"\nRol: "<<campoRol<<std::endl;
        std::cout<<"\n";



    }


    archivo.close();
}


void Usuarios::gestorUsuario::modificarUsuario(const int& id, const std::string& campoViejo, const std::string& campoNuevo){

    std::ifstream archivoOriginal("txt/usuario.txt");
    std::ofstream archivoCopia("txt/temporal.txt");

    std::streampos posicion = busquedaPorId(id);

    if(usuarioEncontrado(posicion)){


        std::string campoId,campoClav,campoNom,campoRol,linea;
    
        bool encontrado = false;
    
        int userId;
    
    
        while(std::getline(archivoOriginal,linea)){
    
            std::stringstream ss(linea);
    
            std::getline(ss,campoId,',');
            std::getline(ss,campoClav,',');
            std::getline(ss,campoNom,',');
            std::getline(ss,campoRol);
    
    
            userId = std::stoi(campoId);
    
    
            if(userId == id){
                encontrado = true;
            }else{
                archivoCopia << campoId << "," << campoClav << "," << campoNom << "," << campoRol << "\n";
            }
    
    
            if(encontrado == true){
    
                archivoCopia << campoId << ",";
                
                
                
                if(campoViejo == campoClav){
                    archivoCopia << campoNuevo << ",";
                }else{
                    archivoCopia << campoClav << ",";
                }
    
    
    
    
                if(campoViejo == campoNom){
                    archivoCopia << campoNuevo << ",";
                }else{
                    archivoCopia << campoNom << ",";
                }
    
    
    
    
    
                archivoCopia << campoRol << "\n";
                encontrado = false;
    
            }
    
    
    
        }
    
    
    
        archivoCopia.close();
        archivoOriginal.close();
    
        std::remove("txt/usuario.txt");
        std::rename("txt/temporal.txt","txt/usuario.txt");


    }else{
        std::cout<<"\n\t=========ALERTA=========="<<std::endl;
        std::cout<<"\tEL USUARIO NO EXISTE"<<std::endl;
    }






}



void Usuarios::gestorUsuario::modificarUsuario(const int& id, const ROL& rolNuevo){

    std::ifstream archivoOriginal("txt/usuario.txt");
    std::ofstream archivoCopia("txt/temporal.txt");

    std::streampos posicion = busquedaPorId(id);

    if(usuarioEncontrado(posicion)){


        std::string campoId,campoClav,campoNom, campoRol,linea;
    
        int userId;
        bool encontrado = false;
    
        while(std::getline(archivoOriginal,linea)){
    
    
            std::stringstream ss(linea);
    
            std::getline(ss,campoId,',');
            std::getline(ss,campoClav,',');
            std::getline(ss,campoNom,',');
            std::getline(ss,campoRol);
    
            userId = std::stoi(campoId);
    
    
            if(userId == id){
                encontrado = true;
            }else{
                archivoCopia << campoId << "," << campoClav << "," << campoNom << "," << campoRol << "\n";
            }
    
            if(encontrado == true){
    
                archivoCopia << campoId << "," << campoClav << "," << campoNom << "," << rolATexto(rolNuevo) << "\n";
    
    
    
                encontrado = false;
    
    
            }
    
    
    
    
    
    
    
    
    
        }
    
    
        archivoCopia.close();
        archivoOriginal.close();
    
        std::remove("txt/usuario.txt");
        std::rename("txt/temporal.txt","txt/usuario.txt");



    }else{
        std::cout<<"\n\t=========ALERTA=========="<<std::endl;
        std::cout<<"\tEL USUARIO NO EXISTE"<<std::endl;
    }




}



void Usuarios::gestorUsuario::eliminarUsuario(const int& id){

    std::ifstream archivoOriginal("txt/usuario.txt");
    std::ofstream archivoCopia("txt/temporal.txt");


    std::streampos posicion = busquedaPorId(id);


    if(usuarioEncontrado(posicion)){


            std::string campoId, campoClav,campoNom,campoRol,linea;

            int userID;

            while(std::getline(archivoOriginal,linea)){

                std::stringstream ss(linea);

                std::getline(ss,campoId,',');
                std::getline(ss,campoClav,',');
                std::getline(ss,campoNom,',');
                std::getline(ss,campoRol);


                userID = std::stoi(campoId);

                if(userID != id){

                    archivoCopia << campoId << "," << campoClav << "," << campoNom << "," << campoRol << "\n";

                }




            }


            archivoCopia.close();
            archivoOriginal.close();


            std::remove("txt/usuario.txt");
            std::rename("txt/temporal.txt","txt/usuario.txt");

    }else{

        std::cout<<"\n\t=========ALERTA=========="<<std::endl;
        std::cout<<"\tEL USUARIO NO EXISTE"<<std::endl;

    }







}





/*
=============================================================



    FUNCIONES DE CONEXION

    

=============================================================
*/



bool Usuarios::gestorUsuario::validarAdmin(const int& id){

    std::ifstream archivo("txt/usuario.txt");

    std::streampos posicion = busquedaPorId(id);

    if(usuarioEncontrado(posicion)){

        bool esAdmin  = false;

        archivo.seekg(posicion);

        std::string campoId, campoClav, campoNom, campoRol, linea;

        std::stringstream string;

        string << id;

        while(std::getline(archivo,linea)){

            std::stringstream ss(linea);

            std::getline(ss,campoId,',');
            std::getline(ss,campoClav,',');
            std::getline(ss,campoNom,',');
            std::getline(ss,campoRol);


            if(campoId != string.str()){
                break;
            }

            Usuarios::ROL rol = textoARol(campoRol);


            if(rol == Usuarios::ROL::admin){
                esAdmin = true;
            }




        }


        archivo.close();
        return esAdmin;



    }else{

        std::cout<<"\n\t=========ALERTA=========="<<std::endl;
        std::cout<<"\tEL USUARIO NO EXISTE"<<std::endl;
        return false;

    }
    
    
    



}

std::string Usuarios::gestorUsuario::retornar(const int& id, const RETORNAR& estado){

    std::ifstream archivo("txt/usuario.txt");

    std::streampos posicion = busquedaPorId(id);

    if(usuarioEncontrado(posicion)){

        archivo.seekg(posicion);

        std::string campoId,campoClav,campoNom,campoRol,linea, dato;
        
        std::stringstream cambio;

        cambio << id;


        while(std::getline(archivo,linea) && campoId != cambio.str()){
            std::stringstream ss(linea);

            std::getline(ss,campoId,',');
            std::getline(ss,campoClav,',');
            std::getline(ss,campoNom,',');
            std::getline(ss,campoRol);
            
            
        }
        
        switch(estado){
            case RETORNAR::nombre : dato = campoNom; break;
            case RETORNAR::clave : dato = campoClav; break;
            case RETORNAR::rol : dato = campoRol; break;
        }
        
        return dato;

    }else{

        std::cout<<"\n\t=========ALERTA=========="<<std::endl;
        std::cout<<"\tEL USUARIO NO EXISTE"<<std::endl;
        return "USUARIO NO ENCONTRADO";

    }




}


int Usuarios::gestorUsuario::retornarId(const std::string& nombre, const std::string& clave){
    
    std::ifstream archivo("txt/usuario.txt");

    std::string campoId,campoClav,campoNom,campoRol,linea;
    bool encontrado = false;

    int id = 0;

    while(std::getline(archivo,linea) && encontrado == false){

        std::stringstream ss(linea);

        std::getline(ss,campoId,',');
        std::getline(ss,campoClav,',');
        std::getline(ss,campoNom,',');
        std::getline(ss,campoRol);

        if(campoClav == clave && campoNom == nombre){
            encontrado = true;
        }




    }

    
    if(encontrado == true){
        id = std::stoi(campoId);
        return id;
    }else{
        std::cout<<"\n\t=========ALERTA=========="<<std::endl;
        std::cout<<"\tEL USUARIO NO EXISTE"<<std::endl;
        return -1;
    }



}