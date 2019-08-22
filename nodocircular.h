#ifndef NODOCIRCULAR_H
#define NODOCIRCULAR_H

#include "nodoabb.h"

#include <string>

class nodocircular
{
    public:
        std::string filtro;
        std::string capa;
        
        nodoabb *fil;
        nodocircular *sig;
        nodocircular *ant;

        nodocircular()
        {
            filtro = "";
            capa = "";
            fil = NULL;
            sig = NULL;
            ant = NULL;
        }
};

#endif // NODOCIRCULAR_H