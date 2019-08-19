#ifndef NODOCOL_H
#define NODOCOL_H

#include "nodomatriz.h"

#include <iostream>

class nodocol
{
    public:
        int col;
        nodocol *sig;
        nodomatriz *abajo;
        
        nodocol(int c)
        {
            col = c;
            sig = NULL;
            abajo = NULL;
        }
};

#endif // NODOCOL_H