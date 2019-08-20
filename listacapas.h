#ifndef LISTACAPAS_H
#define LISTACAPAS_H

#include "nodolistacapa.h"
#include "listalineal.cpp"

//#include <string>

class listacapas
{
    public:
        nodolistacapa *inicio;
        matriz *todo;
        listalineal *linealizada;

        listacapas(std::string nomb);
        void insertar(nodolistacapa *nuevo);
        void graficar_capas();
        void sobreponer();
        void linealizar();
};

#endif // LISTACAPAS_H