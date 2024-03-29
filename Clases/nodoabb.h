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
        int fr;
        int fg;
        int fb;
        int totFil;
        int totCol;
        listacapas *listaC;
        nodoabb *ni, *nd;

        nodoabb(string n, int dh, int dw, int ph, int pw, listacapas *l);
        void generar();
        void generar2();
};

#endif // NODOABB_H
