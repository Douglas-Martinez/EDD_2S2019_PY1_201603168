#ifndef LISTAFIL_H
#define LISTAFIL_H

#include "nodofil.h"

class listafil
{
    public:
        //int tam;
        nodofil *inicio;

        listafil();

        void insertar(int f);
        nodofil* buscar(int f);
        
};

#endif // LISTAFIL_H