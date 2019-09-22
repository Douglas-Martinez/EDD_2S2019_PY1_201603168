#ifndef LISTAFIL_H
#define LISTAFIL_H

#include "nodofil.h"

class listafil
{
    public:
        nodofil *inicio;
        listafil();
        void insertar(int f);
        nodofil* buscar(int f);
        
};

#endif // LISTAFIL_H