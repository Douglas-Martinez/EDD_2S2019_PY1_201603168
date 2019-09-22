#ifndef LISTALINEAL_H
#define LISTALINEAL_H

#include "nodolineal.h"

class listalineal
{
    public:
        nodolineal *primero;
        nodolineal *ultimo;
        std::string nombre;
        int totF;
        int totC;

        listalineal();
        void insertar(nodolineal *nuevo);
        nodolineal* buscar(int p);
        void graficar();
};

#endif // LISTALINEAL_H