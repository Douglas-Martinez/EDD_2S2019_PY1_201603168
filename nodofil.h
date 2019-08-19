#ifndef NODOFIL_H
#define NODOFIL_H

#include "nodomatriz.h"
#include <iostream>

class nodofil
{
    public:
        int fil;
        nodofil *sig;
        nodomatriz *der;

        nodofil(int f)
        {
            fil = f;
            sig = NULL;
            der = NULL;
        }
};

#endif // NODOFIL_H