#ifndef LISTACIRCULAR_H
#define LISTACIRCULAR_H

#include "nodocircular.h"

class listacircular
{
    public:
        nodocircular *primero;
        nodocircular *ultimo;

        listacircular();
        void insertar(nodocircular *nuevo);
        void graficar();
};

#endif // LISTACIRCULAR_H