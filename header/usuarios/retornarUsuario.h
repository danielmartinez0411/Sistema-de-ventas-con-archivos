#include "usuarios/user.h"
#include <string>


namespace usuarios{


    namespace retornar{

        std::string retornarNombre(const int& id);

        std::string retornarClave(const int& id);

        usuarios::ROL retornarRol(const int& id);



    }



}