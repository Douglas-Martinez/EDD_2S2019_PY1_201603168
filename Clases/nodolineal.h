#ifndef NODOLINEAL_H
#define NODOLINEAL_H

#include <string>

class nodolineal
{
    public:
        int pos;
        int fil;
        int col;
        std::string colorH;
        nodolineal *sig;

        nodolineal(int p, int f, int c, std::string cH)
        {
            pos = p;
            fil = f;
            col = c;
            colorH = cH;
            sig = NULL;
        }
};

#endif // NODOLINEAL_H