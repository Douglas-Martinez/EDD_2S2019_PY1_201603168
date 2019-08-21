#ifndef NODOABB_H
#define NODOABB_H

#include "listacapas.h"

#include <string>

using namespace std;

class nodoabb
{
    public:
        string nombre;
        int dimH;
        int dimW;
        int pixH;
        int pixW;
        listacapas *listaC;
        nodoabb *ni, *nd;

        nodoabb(string n, int dh, int dw, int ph, int pw, listacapas *l)
        {
            nombre = n;
            dimH = dh;
            dimW = dw;
            pixH = ph;
            pixW = pw;
            listaC = l;
            ni = NULL;
            nd = NULL;
        }
};

#endif // NODOABB_H
