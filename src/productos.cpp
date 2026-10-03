#include <productos.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>



/*
================================================================


    FUNCIONES AUXILIARES


================================================================
*/


inline bool Productos::gestorProducto::productoEncontrado(std::streampos posicion){
    return (posicion == -1) ? false : true;
}


int Productos::gestorProducto::mayorID(){
    std::ifstream archivo("txt/productos.txt");

    int id = 0, mayor = 0;

    std::string campoId, campoCan, campoCanMin, campoCost, campoPrecDet, campoPrecMay, campoNom, campoEstado, linea;

    while(std::getline(archivo, linea)){
        
        std::stringstream ss(linea);

        std::getline(ss,campoId,',');
        std::getline(ss,campoCan,',');
        std::getline(ss,campoCanMin,',');
        std::getline(ss,campoCost,',');
        std::getline(ss,campoPrecDet,',');
        std::getline(ss,campoPrecMay,',');
        std::getline(ss,campoNom,',');
        std::getline(ss,campoEstado,',');


        id = std::stoi(campoId);

        if(id > mayor){
            mayor = id;
        }


    }


    archivo.close();
    return mayor;

}

inline int Productos::gestorProducto::asignarID(){
    return mayorID() + 1;
}

inline Productos::ESTADO Productos::gestorProducto::asignarEstado(const int& can){
    return (can > 0) ? ESTADO::disponible : ESTADO::agotado;
}


bool Productos::gestorProducto::validarExistencia(const std::string& nom){

    std::ifstream archivo("txt/productos.txt");
    bool encontrado = false;

    std::string campoId, campoCan,campoCanMin, campoCost, campoPrecDet, campoPrecMayor, campoNom, campoEstado, linea;

    while(std::getline(archivo,linea)){

        std::stringstream ss(linea);

        std::getline(ss,campoId,',');
        std::getline(ss,campoCan,',');
        std::getline(ss,campoCanMin,',');
        std::getline(ss,campoCost,',');
        std::getline(ss,campoPrecDet,',');
        std::getline(ss,campoPrecMayor,',');
        std::getline(ss,campoNom,',');
        std::getline(ss,campoEstado);

        if(nom == campoNom){
            encontrado = true;
            break;
        }







    }

    archivo.close();
    return encontrado;

}


std::string Productos::gestorProducto::estadoATexto(const ESTADO& estado){

    std::string texto;

    switch(estado){
        case ESTADO::agotado: texto = "Agotado"; break;
        case ESTADO::disponible: texto = "Disponible"; break;
        case ESTADO::pocasUnidades:texto = "Pocas Unidades"; break;
    }


    return texto;

}

/*
=============================================================


    FUNCIONES CLAVE


=============================================================
*/


std::streampos Productos::gestorProducto::busquedaPorId(const int& id){

    std::ifstream archivo("txt/productos.txt");

    std::streampos posicion;

    std::string campoId, campoCan, campoCanMin, campoCost, campoPrecDet, campoPrecMayor, campoNom, campoEstado, linea;


    int userID;

    while(archivo){

        posicion = archivo.tellg();

        std::getline(archivo,linea);


        std::stringstream ss(linea);

        std::getline(ss,campoId,',');
        std::getline(ss,campoCan,',');
        std::getline(ss,campoCanMin,',');
        std::getline(ss,campoCost,',');
        std::getline(ss,campoPrecDet,',');
        std::getline(ss,campoPrecMayor,',');
        std::getline(ss,campoNom,',');
        std::getline(ss,campoEstado);


        std::stringstream string(campoId);


        string >> userID;

        if(userID == id){
            archivo.close();
            return posicion;
        }








    }


    archivo.close();
    return -1;


}




void Productos::gestorProducto::agregarProducto(const int& can, const int& canMin, const double& cost, const double& precDet, const double& precMayor, const std::string& nom){

    std::ofstream archivo("txt/productos.txt",std::ios_base::app);

    if(validarExistencia(nom) == false){

        Productos::ESTADO estadoNuevo = asignarEstado(can);
        int id = asignarID();

        Producto nuevo(id,can,canMin,cost,precDet,precMayor,nom,estadoNuevo);
        
        archivo << nuevo.id << "," << nuevo.cantidad << "," << nuevo.cantidadMinima << "," << nuevo.costo << "," << nuevo.precioDetalle << "," << nuevo.precioPorMayor << "," << nuevo.nombre << "," << estadoATexto(nuevo.estado) << "\n";

        



    }else{
        std::cout<<"\n\t==========ALERTA============"<<std::endl;
        std::cout<<"\tEL PRODUCTO YA EXISTE"<<std::endl;
    }

    archivo.close();

}


void Productos::gestorProducto::mostrarProductos(){
    std::ifstream archivo("txt/productos.txt");


    std::string campoId, campoCan, campoCanMin,campoCost, campoPrecDet,campoPrecMayor,campoNom,campoEstado, linea;

    while(std::getline(archivo,linea)){

        std::stringstream ss(linea);

        std::getline(ss,campoId,',');
        std::getline(ss,campoCan,',');
        std::getline(ss,campoCanMin,',');
        std::getline(ss,campoCost,',');
        std::getline(ss,campoPrecDet,',');
        std::getline(ss,campoPrecMayor,',');
        std::getline(ss,campoNom,',');
        std::getline(ss,campoEstado);

        std::cout<<"\nID: "<<campoId;
        std::cout<<"\nNombre: "<<campoNom;
        std::cout<<"\nEstado: "<<campoEstado;
        std::cout<<"\nPrecio Detalle: "<<campoPrecDet;
        std::cout<<"\nPrecio Al Por Mayor: "<<campoPrecMayor;
        std::cout<<"\nCosto: "<<campoCost;
        std::cout<<"\nCantidad: "<<campoCan;
        std::cout<<"\nCantidad Minima: "<<campoCanMin << std::endl;
        std::cout<<"\n";






    }

    archivo.close();



}


void Productos::gestorProducto::mostrarProductos(const int& id){

    std::ifstream archivo("txt/productos.txt");

    std::streampos posicion = busquedaPorId(id);


    if(productoEncontrado(posicion)){

        archivo.seekg(posicion);


        std::string campoId,campoCan,campoCanMin,campoCost,campoPrecDet,campoPrecMayor,campoNom,campoEstado, linea;

        std::stringstream string;

        string << id;



        while(std::getline(archivo,linea)){


            std::stringstream ss(linea);
    
            std::getline(ss,campoId,',');
            std::getline(ss,campoCan,',');
            std::getline(ss,campoCanMin,',');
            std::getline(ss,campoCost,',');
            std::getline(ss,campoPrecDet,',');
            std::getline(ss,campoPrecMayor,',');
            std::getline(ss,campoNom,',');
            std::getline(ss,campoEstado);
    
    
            if(campoId != string.str()){
                break;
            }
    
            std::cout<<"\nID: "<<campoId;
            std::cout<<"\nNombre: "<<campoNom;
            std::cout<<"\nEstado: "<<campoEstado;
            std::cout<<"\nPrecio Detalle: "<<campoPrecDet;
            std::cout<<"\nPrecio Al Por Mayor: "<<campoPrecMayor;
            std::cout<<"\nCosto: "<<campoCost;
            std::cout<<"\nCantidad: "<<campoCan;
            std::cout<<"\nCantidad Minima: "<<campoCanMin << std::endl;
            std::cout<<"\n";





        }

        archivo.close();



    }else{
        std::cout<<"\n\t==========ALERTA============"<<std::endl;
        std::cout<<"\tEL PRODUCTO NO EXISTE"<<std::endl;
    }



}


void Productos::gestorProducto::mostrarProductosPrecio(const double& precio, const BUSCAR& busqueda){
    std::ifstream archivo("txt/productos.txt");

    std::string campoId, campoCan, campoCanMin,campoCost,campoPrecDet,campoPrecMayor,campoNom,campoEstado,linea;

    std::stringstream cambio;

    bool encontrado = false;

    cambio << precio;

    while(std::getline(archivo,linea)){




        std::stringstream ss(linea);

        std::getline(ss,campoId,',');
        std::getline(ss,campoCan,',');
        std::getline(ss,campoCanMin,',');
        std::getline(ss,campoCost,',');
        std::getline(ss,campoPrecDet,',');
        std::getline(ss,campoPrecMayor,',');
        std::getline(ss,campoNom,',');
        std::getline(ss,campoEstado);



        switch(busqueda){





            case Productos::BUSCAR::precioDetalle :{

                if(cambio.str() == campoPrecDet){
                    int userID = std::stoi(campoId);
                    encontrado = true;
                    mostrarProductos(userID);
                }


                break;
            } 




            case Productos::BUSCAR::precioMayor :{

                if(cambio.str() == campoPrecMayor){
                    int userID = std::stoi(campoId);
                    encontrado = true;
                    mostrarProductos(userID);
                }


                break;
            }






        }




    }

    archivo.close();


    if(encontrado == false){
        std::cout<<"\n\t==========ALERTA============"<<std::endl;
        std::cout<<"\tNO HAY PRODUCTOS DE ESE PRECIO"<<std::endl;
    }


}


void Productos::gestorProducto::mostrarRangoDePrecios(const double& precInicial, const double& precFinal, const BUSCAR& busqueda){

    std::ifstream archivo("txt/productos.txt");

    std::stringstream convertir;

    convertir << precInicial <<" "<< precFinal;

    std::string rangoMin, rangoMax;

    convertir >> rangoMin >> rangoMax;

    std::string campoId, campoCan, campoCanMin, campoCost, campoPrecDet, campoPrecMayor, campoNom, campoEstado, linea;

    bool encontrado = false;
    
    
    while(std::getline(archivo,linea)){

        std::stringstream ss(linea);

        std::getline(ss,campoId,',');
        std::getline(ss,campoCan,',');
        std::getline(ss,campoCanMin,',');
        std::getline(ss,campoCost,',');
        std::getline(ss,campoPrecDet,',');
        std::getline(ss,campoPrecMayor,',');
        std::getline(ss,campoNom,',');
        std::getline(ss,campoEstado);


        switch(busqueda){

            case BUSCAR::precioDetalle : {

                if(campoPrecDet >= rangoMin && campoPrecDet <= rangoMax){
                    encontrado = true;
                    int userID = std::stoi(campoId);
                    mostrarProductos(userID);
                }




                break;
            }


            case BUSCAR::precioMayor : {

                if(campoPrecMayor >= rangoMin && campoPrecMayor <= rangoMax){
                    encontrado = true;
                    int userID = std::stoi(campoId);
                    mostrarProductos(userID);
                }


                break;
            }




        }





    }

    archivo.close();

    if(encontrado == false){
        std::cout<<"\n\t===============ALERTA================="<<std::endl;
        std::cout<<"\tNO HAY PRODUCTOS DE ESE RANGO DE PRECIO"<<std::endl;

    }




}

void Productos::gestorProducto::busquedaPorNombre(const std::string& nombreProducto){

    std::ifstream archivo("txt/productos.txt");

    bool encontrado = false;


    std::string campoId, campoCan, campoCanMin, campoCost, campoPrecDet, campoPrecMayor, campoNom, campoEstado, linea;


    while(std::getline(archivo,linea) && encontrado == false){

        std::stringstream ss(linea);

        std::getline(ss,campoId,',');
        std::getline(ss,campoCan,',');
        std::getline(ss,campoCanMin,',');
        std::getline(ss,campoCost,',');
        std::getline(ss,campoPrecDet,',');
        std::getline(ss,campoPrecMayor,',');
        std::getline(ss,campoNom,',');
        std::getline(ss,campoEstado);


        if(campoNom == nombreProducto){

            int productoID = std::stoi(campoId);
            mostrarProductos(productoID);
            encontrado = true;
        }




    }

    archivo.close();



    if(encontrado == false){
        std::cout<<"\n\t===============ALERTA================="<<std::endl;
        std::cout<<"\t\tESE PRODUCTO NO EXISTE"<<std::endl;
    }



}




void Productos::gestorProducto::modificarProducto(const int& id, const std::string& campoViejo, const std::string& campoNuevo){

    std::ifstream archivoOriginal("txt/productos.txt");
    std::ofstream archivoCopia("txt/temporal.txt");

    std::streampos posicion = busquedaPorId(id);

    if(productoEncontrado(posicion)){

        int userId;

        bool encontrado = false;

        std::string campoId, campoCan, campoCanMin, campoCost, campoPrecDet, campoPrecMayor, campoNom, campoEstado, linea;

        while(std::getline(archivoOriginal,linea) && encontrado != true){

            std::stringstream ss(linea);

            std::getline(ss,campoId,',');
            std::getline(ss,campoCan,',');
            std::getline(ss,campoCanMin,',');
            std::getline(ss,campoCost,',');
            std::getline(ss,campoPrecDet,',');
            std::getline(ss,campoPrecMayor,',');
            std::getline(ss,campoNom,',');
            std::getline(ss,campoEstado);

            userId = std::stoi(campoId);

            if(userId == id){
                encontrado = true;
            }else{
                archivoCopia << campoId << "," << campoCan << "," << campoCanMin << "," << campoCost << "," << campoPrecDet << "," << campoPrecMayor << "," << campoNom << "," << campoEstado << "\n";
            }

            if(encontrado == true){

                archivoCopia << campoId << ",";

                if(campoViejo == campoCan){
                    archivoCopia << campoNuevo << ",";
                }else{
                    archivoCopia << campoCan << ",";
                }


                if(campoViejo == campoCanMin){
                    archivoCopia << campoNuevo << ",";
                }else{
                    archivoCopia << campoCanMin << ",";
                }

                if(campoViejo == campoCost){
                    archivoCopia << campoNuevo << ",";
                }else{
                    archivoCopia << campoCost << ",";
                }

                if(campoViejo == campoPrecDet){
                    archivoCopia << campoNuevo << ",";
                }else{
                    archivoCopia << campoPrecDet << ",";
                }

                if(campoViejo == campoPrecMayor){
                    archivoCopia << campoNuevo << ",";
                }else{
                    archivoCopia << campoPrecMayor << ",";
                }

                if(campoViejo == campoNom){
                    archivoCopia << campoNuevo << ",";
                }else{
                    archivoCopia << campoNom << ",";
                }

                archivoCopia << campoEstado << "\n";

                encontrado = false;




            }


        }

        archivoOriginal.close();
        archivoCopia.close();

        std::remove("txt/productos.txt");
        std::rename("txt/temporal.txt","txt/productos.txt");





    }else{
        std::cout<<"\n\t===============ALERTA================="<<std::endl;
        std::cout<<"\t\tESE PRODUCTO NO EXISTE"<<std::endl;
    }






}


void Productos::gestorProducto::eliminarProducto(const int& id){

    std::streampos posicion = busquedaPorId(id);

    if(productoEncontrado(posicion)){

        std::ifstream archivoOriginal("txt/productos.txt");
        std::ofstream archivoCopia("txt/temporal.txt");

        int userId;

        std::string campoId, campoCan, campoCanMin, campoCost, campoPrecDet, campoPrecMayor, campoNom, campoEstado, linea;

        while(std::getline(archivoOriginal,linea)){

            std::stringstream ss(linea);

            std::getline(ss,campoId,',');
            std::getline(ss,campoCan,',');
            std::getline(ss,campoCanMin,',');
            std::getline(ss,campoCost,',');
            std::getline(ss,campoPrecDet,',');
            std::getline(ss,campoPrecMayor,',');
            std::getline(ss,campoNom,',');
            std::getline(ss,campoEstado);


            userId = std::stoi(campoId);


            if(userId != id){


                archivoCopia << campoId << "," << campoCan << "," << campoCanMin << "," << campoCost << "," << campoPrecDet << "," << campoPrecMayor << "," << campoNom << "," << campoEstado << "\n";



            }





        }

        archivoCopia.close();
        archivoOriginal.close();


        std::remove("txt/productos.txt");
        std::rename("txt/temporal.txt","txt/productos.txt");



    }else{

        std::cout<<"\n\t===============ALERTA================="<<std::endl;
        std::cout<<"\t\tESE PRODUCTO NO EXISTE"<<std::endl;

    }








}



/*
=============================================================


    FUNCIONES EXTRA


=============================================================
*/




int Productos::gestorProducto::obtenerIdConNombre(const std::string& nombre){

    std::ifstream archivo("txt/productos.txt");

    int idProducto = 0;
    
    std::string campoId, campoCan, campoCanMin, campoCost, campoPrecDet, campoPrecMayor, campoNom, campoEstado, linea;


    while(std::getline(archivo,linea)){

        std::stringstream ss(linea);

        std::getline(ss,campoId,',');
        std::getline(ss,campoCan,',');
        std::getline(ss,campoCanMin,',');
        std::getline(ss,campoCost,',');
        std::getline(ss,campoPrecDet,',');
        std::getline(ss,campoPrecMayor,',');
        std::getline(ss,campoNom,',');
        std::getline(ss,campoEstado);


        if(campoNom == nombre){
            idProducto = std::stoi(campoId);
            return idProducto;
        }







    }

    archivo.close();
    return -1;



}


std::string Productos::gestorProducto::obtenerNombreConId(const int& id){

    std::streampos posicion = busquedaPorId(id);

    if(productoEncontrado(posicion)){

        std::ifstream archivo("txt/productos.txt");

        std::string campoId, campoCan, campoCanMin, campoCost, campoPrecDet, campoPrecMayor, campoNom, campoEstado, linea;

        int productoID;

    
        while(std::getline(archivo, linea)){

            std::stringstream ss(linea);


            std::getline(ss,campoId,',');
            std::getline(ss,campoCan,',');
            std::getline(ss,campoCanMin,',');
            std::getline(ss,campoCost,',');
            std::getline(ss,campoPrecDet,',');
            std::getline(ss,campoPrecMayor,',');
            std::getline(ss,campoNom,',');
            std::getline(ss,campoEstado);


            productoID = std::stoi(campoId);

            if(productoID == id){
                archivo.close();
                return campoNom;
            }






        }

        archivo.close();






    }else{
        std::cout<<"\n\t===============ALERTA================="<<std::endl;
        std::cout<<"\t\tESE PRODUCTO NO EXISTE"<<std::endl;
        return "ERROR: Producto no encontrado";
    }




}