#ifndef NODOCIRCULAR_H
#define NODOCIRCULAR_H

#include "nodoabb.h"

#include <string>

class nodocircular
{
    public:
        int id;
        std::string filtro;
        std::string capa;
        
        nodoabb *fil;
        nodocircular *sig;
        nodocircular *ant;

        nodocircular()
        {
            id = -1;
            filtro = "";
            capa = "";
            fil = NULL;
            sig = NULL;
            ant = NULL;
        }
};

#endif // NODOCIRCULAR_H