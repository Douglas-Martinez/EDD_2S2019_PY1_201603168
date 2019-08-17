#ifndef ABB_H
#define ABB_H

#include "nodoabb.h"

#include <string>

using namespace std;

class abb
{
    public:
        nodoabb *raiz;

        abb()
        {
            raiz = NULL;
        }
        void insertar(string n, int dh, int dw, int ph, int pw);
        void insertar(nodoabb *r, string n, int dh, int dw, int ph, int pw);
        nodoabb* buscar(nodoabb *r, string n);

        void graficar();
        void nodo(nodoabb *r, FILE **f);
        void link(nodoabb *r, FILE **f);
        void recorridoIN(nodoabb* r);
        void recorridoPRE(nodoabb* r);
        void recorridoPOST(nodoabb* r);
};

#endif // ABB_H
