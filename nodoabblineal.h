#ifndef NODOABBLINEAL_H
#define NODOABBLINEAL_H

#include <string>

class nodoabblineal
{
    public:
        int pos;
        std::string nombre;
        nodoabblineal *sig;

        nodoabblineal()
        {
            pos = 0;
            nombre = "";
            sig = NULL;
        }
};

#endif // NODOABBLINEAL_H