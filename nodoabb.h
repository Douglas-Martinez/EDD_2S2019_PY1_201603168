#ifndef NODOABB_H
#define NODOABB_H

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
        //listaCapas listaC;
        nodoabb *ni, *nd;

        nodoabb(string n, int dh, int dw, int ph, int pw)
        {
            nombre = n;
            dimH = dh;
            dimW = dw;
            pixH = ph;
            pixW = pw;
            //listaC = lc;
            ni = NULL;
            nd = NULL;
        }
};

#endif // NODOABB_H
