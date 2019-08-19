#ifndef LISTACAPAS_H
#define LISTACAPAS_H

#include "nodolistacapa.h"

class listacapas
{
    public:
        nodolistacapa *inicio;
        listacapas();
        void insertar(nodolistacapa *nuevo);
        void graficar_capas();
};

#endif // LISTACAPAS_H