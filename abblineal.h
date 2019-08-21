#ifndef ABBLINEAL_H
#define ABBLINEAL_H

#include "nodoabblineal.h"

class abblineal
{
    public:
        nodoabblineal *primero;
        nodoabblineal *ultimo;
        
        abblineal();
        void insertar(nodoabblineal *n);
};

#endif // ABBLINEAL_H