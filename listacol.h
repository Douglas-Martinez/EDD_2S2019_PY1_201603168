#ifndef LISTACOL_H
#define LISTACOL_H

#include "nodocol.h"

class listacol
{
    public:
        nodocol *inicio;

        listacol();

        void insertar(int c);
        nodocol* buscar(int c);
};

#endif // LISTACOL_h