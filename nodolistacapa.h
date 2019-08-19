#ifndef NODOLISTACAPA_H
#define NODOLISTACAPA_H

#include "matriz.h"

#include <string>

class nodolistacapa
{
    public:
        int id;
        std::string nombre;
        matriz *capa;
        nodolistacapa *sig;

        nodolistacapa(int i, std::string n, matriz *m)
        {
            id = i;
            nombre = n;
            capa = m;
            sig = NULL;
        }
};

#endif // NODOLISTACAPA_H