#include "ventas.h"
#include "productos.h"
#include "user.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>


/*
================================================================


    FUNCIONES AUXILIARES


================================================================
*/

int Ventas::gestorVentas::mayorID(){

    std::ifstream archivo("txt/ventas.txt");

    int id = 0, mayor = 0;

    std::string campoId, campoUsuario, campoTotal, campoEstado, campoProducto, linea;

    
    while(std::getline(archivo,linea)){

        std::stringstream ss(linea);

        std::getline(ss,campoId,',');
        std::getline(ss,campoUsuario,',');
        std::getline(ss,campoTotal,',');
        std::getline(ss,campoEstado,',');
        std::getline(ss,campoProducto);

        id = std::stoi(campoId);

        if(id > mayor){
            mayor = id;
        }


    }


    archivo.close();
    return mayor;
}

inline int Ventas::gestorVentas::asignarId(){
    return mayorID() + 1;
}

std::string Ventas::gestorVentas::estadoATexto(const ESTADO& estado){

    std::string texto;


    switch(estado){
        case ESTADO::exitosa : return texto = "Exitosa"; break;
        case ESTADO::cancelada : return texto ="Cancelada"; break;
    }

    return texto;
}


std::string Ventas::gestorVentas::productoATexto(const PRODUCTO& estado){

    std::string texto;

    switch(estado){
        case PRODUCTO::alDetalle : texto = "DETALLE"; break;
        case PRODUCTO::porMayor : texto = "MAYOREO"; break;
    }

    return texto;

}


Productos::BUSCAR Ventas::gestorVentas::productoABuscar(const PRODUCTO& estado){

    Productos::BUSCAR nuevo;
    
    switch(estado){
        case PRODUCTO::alDetalle : nuevo = Productos::BUSCAR::precioDetalle; break;
        case PRODUCTO::porMayor : nuevo = Productos::BUSCAR::precioMayor; break;
    }


    return nuevo;
}

inline Ventas::PRODUCTO Ventas::gestorVentas::booleanoAProducto(const bool& estado){
    return (estado == true) ? Ventas::PRODUCTO::porMayor : Ventas::PRODUCTO::alDetalle;
}

inline bool Ventas::gestorVentas::validarVenta(const std::streampos& posicion){
    return (posicion == -1) ? false : true;
}


void Ventas::gestorVentas::mostrarProductos(const int& ventaID){

    std::vector<std::string> productos = obtenerProductos(ventaID);

    int productoId = 0, cantidad = 0;

    float subTotal = 0, precio = 0;

    bool porMayor = false;

    Productos::gestorProducto nuevo;

    for(const auto& n : productos){

        productoId = nuevo.obtenerIdConNombre(n);

        cantidad = calcularCantidad(ventaID,productoId);

        
        porMayor = validarPorMayorArchivo(ventaID,productoId);

        (porMayor) ? precio = nuevo.retornarTotal(productoId,Productos::BUSCAR::precioMayor) :precio = nuevo.retornarTotal(productoId,Productos::BUSCAR::precioDetalle);

        subTotal = cantidad * precio;


        std::cout<<"\n"<<"ID: "<<productoId<<" Nombre Producto: "<<n<<" Precio: "<<precio<<" Cantidad: "<<cantidad<<" Sub Total: "<<subTotal<<std::endl;



    }


    std::cout<<"\n\tTotal Venta: "<<totalVenta(ventaID)<<std::endl;


}

int Ventas::gestorVentas::calcularCantidad(const int& ventaId, const int& productoId){

    std::string nombre = obtenerNombreArchivoVenta(ventaId);

    int cantidad = 0, id = 0;

    std::ifstream archivo(nombre);

    std::string campoVentaId, campoProductoId, campoNombre, campoPrecio, campoEstado, linea;

    while(std::getline(archivo,linea)){

        std::stringstream ss(linea);


        std::getline(ss,campoVentaId,',');
        std::getline(ss,campoProductoId,',');
        std::getline(ss,campoNombre,',');
        std::getline(ss,campoPrecio,',');
        std::getline(ss,campoEstado);


        std::stringstream cambio(campoProductoId);

        cambio >> id;

        if(id == productoId){
            cantidad++;
        }


    }

   return cantidad;
}


std::vector<std::string> Ventas::gestorVentas::obtenerProductos(const int& ventaID){

    std::vector<std::string> productos;

    std::string nombre = obtenerNombreArchivoVenta(ventaID);

    std::ifstream archivo(nombre);

    std::string campoVentaId,campoProductoId, campoNombre, campoPrecio, campoEstado, linea;

    
    while(std::getline(archivo,linea)){
        
        bool encontrado = false;

        std::stringstream ss(linea);

        std::getline(ss,campoVentaId,',');
        std::getline(ss,campoProductoId,',');
        std::getline(ss,campoNombre,',');
        std::getline(ss,campoPrecio,',');
        std::getline(ss,campoEstado);

        if(productos.empty()){
            productos.push_back(campoNombre);
        }


        for(int i = 0; i < productos.size();i++){


            if(productos[i] == campoNombre){
                encontrado = true;
            }


        }


        if(!encontrado){
            productos.push_back(campoNombre);
        }


    }




    return productos;

}



std::streampos Ventas::gestorVentas::validarSiProductoExiste(const int& ventaID, const int& productoID){

    std::string nombre = obtenerNombreArchivoVenta(ventaID);
    
    std::ifstream archivo(nombre);
    
    std::string linea, id,campoVentaID, campoProductoID, campoNombre, campoPrecio, campoEstado;
    
    std::stringstream cambio;
    
    std::streampos posicion;
    
    cambio << productoID;
    
    cambio >> id;
    
    while(archivo){
        
        posicion = archivo.tellg();
        
        std::getline(archivo,linea);
        
        std::stringstream ss(linea);
        
        
        std::getline(ss,campoVentaID,',');
        std::getline(ss,campoProductoID,',');
        std::getline(ss,campoNombre,',');
        std::getline(ss,campoPrecio,',');
        std::getline(ss,campoEstado);
        
        
        if(campoProductoID == id){
            return posicion;
        }
        
        
        
        
    }
    
    
    
    archivo.close();
    return -1;
    
    
}


inline std::string Ventas::gestorVentas::obtenerNombreArchivoVenta(const int& ventaID){
    std::string texto = "txt/ventas/venta"+ std::to_string(ventaID) + ".txt";
    return texto;
}


bool Ventas::gestorVentas::validarSiArchivoExiste(const int& ventaID){

    bool encontrado = false;

    std::string nombre = obtenerNombreArchivoVenta(ventaID);

    std::ifstream archivo(nombre);

    if(archivo.is_open()){
        encontrado = true;
    }

    return encontrado;
}


/*
================================================================


FUNCIONES CLAVE


================================================================
*/

void Ventas::gestorVentas::crearArchivo(const int& id){
    
    std::string nombre = obtenerNombreArchivoVenta(id);
    
    std::ofstream archivo(nombre, std::ios_base::app);
    
    archivo.close();
    
}



void Ventas::gestorVentas::crearVenta(const std::string& userNombre, const std::string& userClave){
    
    
    Usuarios::gestorUsuario nuevo;
    
    if(nuevo.validarExistencia(userClave,userNombre)){
        
        std::ofstream archivo("txt/ventas.txt", std::ios_base::app);
        
        int id = asignarId();
        
        archivo << id << "," << userNombre << "," << estadoATexto(ESTADO::exitosa) << "\n"; 
        
        
        crearArchivo(id);
        
        archivo.close();
        
    }else{
        std::cout<<"========ERROR: EL USUARIO NO EXISTE======"<<std::endl;
    }
    
    
    
    
    
    
    
}

void Ventas::gestorVentas::agregarProductos(const int& ventasID, const int& productoID, const PRODUCTO& estado){

    bool existencia = validarSiArchivoExiste(ventasID);

    if(existencia == true){

        std::streampos posicion = validarSiProductoExiste(ventasID,productoID);
    
        if(posicion != -1){
    
            bool porMayor = validarPorMayorArchivo(ventasID,productoID);
    
            Ventas::PRODUCTO nuevo = booleanoAProducto(porMayor);
    
            if(nuevo == estado){
                agregarProductosArchivo(ventasID,productoID,estado);
            }else{
                std::cout<<"No se puede agregar un producto con estado distinto al que tiene en el archivo"<<std::endl;
            }
    
    
    
        }else{
    
            agregarProductosArchivo(ventasID,productoID,estado);
    
    
    
        }

    }else{
        std::cout<<"No existe el archivo que esta buscando"<<std::endl;
    }
    

}

void Ventas::gestorVentas::mostrarVenta(){
    
    std::ifstream archivo("txt/ventas.txt");
    
    
    std::string campoId, campoUser, campoTotal, campoEstado, linea;

    int id = 0;
    
    while(std::getline(archivo,linea)){
        
        std::stringstream ss(linea);
        
        std::getline(ss,campoId,',');
        std::getline(ss,campoUser,',');
        std::getline(ss,campoEstado);
        
        
        std::cout<<"\nVenta ID: "<<campoId<<std::endl;
        std::cout<<"Nombre Usuario: "<<campoUser<<std::endl;
        std::cout<<"Estado venta: "<<campoEstado<<std::endl;
        std::cout<<"\n\tProductos "<<std::endl;
        
        std::stringstream cambio(campoId);

        cambio >> id;


        mostrarProductos(id);
        
        std::cout<<"\n";
        
    }


    archivo.close();
    
    
}



float Ventas::gestorVentas::totalVenta(const int& ventaID){
    
    float total = 0, precio = 0;
    int cantidad = 0, productoId = 0;
    
    Productos::gestorProducto nuevo;
    
    bool porMayor = false;
    
    std::vector<std::string> productos = obtenerProductos(ventaID);
    
    
    for(const auto& n : productos){
        
        productoId = nuevo.obtenerIdConNombre(n);
        
        cantidad = calcularCantidad(ventaID,productoId);
        
        porMayor = validarPorMayorArchivo(ventaID,productoId);

        (porMayor) ? precio = nuevo.retornarTotal(productoId,Productos::BUSCAR::precioMayor) : precio = nuevo.retornarTotal(productoId,Productos::BUSCAR::precioDetalle);
        
        total += precio * cantidad;
        
        
        
    }
    
    
    
    
    return total;
    
    
}


void Ventas::gestorVentas::agregarProductosArchivo(const int& ventaID, const int& productoID, const PRODUCTO& estado){

    std::string nombre = obtenerNombreArchivoVenta(ventaID);

    std::ofstream archivo(nombre, std::ios_base::app);

    Productos::gestorProducto nuevo;

    std::string nombreProducto = nuevo.retornarNombre(productoID);

    Productos::BUSCAR buscar = productoABuscar(estado);
    
    float precio = nuevo.retornarTotal(productoID,buscar);


    archivo << ventaID <<  "," << productoID << "," <<nombreProducto << ",$" << precio << "," << productoATexto(estado) << "\n";


}


bool Ventas::gestorVentas::validarPorMayorArchivo(const int& ventaID, const int& productoID){

    std::streampos posicion = validarSiProductoExiste(ventaID,productoID);

    if(posicion != -1){

        std::string nombre = obtenerNombreArchivoVenta(ventaID);

        std::ifstream archivo(nombre);

        archivo.seekg(posicion);

        std::string linea, campoVentaID, campoProductoID, campoNombre, campoPrecio, campoEstado;

        std::getline(archivo,linea);

        std::stringstream ss(linea);


        std::getline(ss,campoVentaID,',');
        std::getline(ss,campoProductoID,',');
        std::getline(ss,campoNombre,',');
        std::getline(ss,campoPrecio,',');
        std::getline(ss,campoEstado);


        if(campoEstado == "MAYOREO"){
            return true;
        }else{
            return false;
        }


    }else{
        std::cout<<"El producto no existe, att validarpormayorarchivo"<<std::endl;
        return false;
    }




}


void Ventas::gestorVentas::eliminarProducto(const int& ventaID, const int& productoId){

    bool existencia = validarSiArchivoExiste(ventaID);


    if(existencia == true){



        std::string nombre = obtenerNombreArchivoVenta(ventaID);
    
        std::ifstream archivoOriginal(nombre);
        std::ofstream archivoCopia("txt/ventas/temporal.txt");
    
        int id = 0;
    
        std::string linea, campoVentaId, campoProductoId, campoNombre, campoPrecio, campoEstado;
    
        while(std::getline(archivoOriginal,linea)){
    
    
            std::stringstream ss(linea);
    
    
            std::getline(ss,campoVentaId,',');
            std::getline(ss,campoProductoId,',');
            std::getline(ss,campoNombre,',');
            std::getline(ss,campoPrecio,',');
            std::getline(ss,campoEstado);
    
    
    
            std::stringstream cambio(campoProductoId);
    
            cambio >> id;
    
            if(productoId != id){
                archivoCopia << campoVentaId << "," << campoProductoId << "," << campoNombre << "," << campoPrecio << "," << campoEstado << "\n"; 
            }
    
    
    
    
    
        }
    
        archivoCopia.close();
        archivoOriginal.close();
    
    
        std::remove(nombre.c_str());
        std::rename("txt/ventas/temporal.txt",nombre.c_str());


    }else{
        std::cout<<"Eliminar producto dice: La venta no existe"<<std::endl;
    }





}


void Ventas::gestorVentas::eliminarVenta(const int& ventaID){


    bool existencia = validarSiArchivoExiste(ventaID);

    if(existencia == true){

        std::ifstream archivoOriginal("txt/ventas.txt");
        std::ofstream archivoCopia("txt/temporal.txt");


        std::string linea, campoId, campoUser, campoEstado;

        int id = 0;

        while(std::getline(archivoOriginal,linea)){

            std::stringstream ss(linea);

            std::getline(ss,campoId,',');
            std::getline(ss,campoUser,',');
            std::getline(ss,campoEstado);


            std::stringstream cambio(campoId);

            cambio >> id;

            if(id != ventaID){
                archivoCopia << campoId << "," << campoUser << "," << campoEstado << "\n";
            }
            


        }

        archivoOriginal.close();
        archivoCopia.close();

        std::string nombre = obtenerNombreArchivoVenta(ventaID);

        std::remove("txt/ventas.txt");
        std::rename("txt/temporal.txt","txt/ventas.txt");
        std::remove(nombre.c_str());

        



    }else{
        std::cout<<"Eliminar venta dice: No existe la venta"<<std::endl;
    }










}