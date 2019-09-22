#ifndef ABB_H
#define ABB_H

#include "nodoabb.cpp"
#include "abblineal.cpp"

#include <string>

using namespace std;

class abb
{
    public:
        nodoabb *raiz;
        abblineal *trasversalIN;
        abblineal *trasversalPRE;
        abblineal *trasversalPOST;

        abb()
        {
            raiz = NULL;
            trasversalIN = new abblineal();
            trasversalPRE = new abblineal();
            trasversalPOST = new abblineal();
        }
        void insertar(string n, int dh, int dw, int ph, int pw, listacapas *l);
        void insertar(nodoabb *r, string n, int dh, int dw, int ph, int pw, listacapas *l);
        nodoabb* buscar(nodoabb *r, string n);

        void graficar();
        void nodo(nodoabb *r, FILE **f);
        void link(nodoabb *r, FILE **f);
        void grafIN();
        void grafPRE();
        void grafPOST();
        void recorridoIN(nodoabb* r);
        void recorridoPRE(nodoabb* r);
        void recorridoPOST(nodoabb* r);
};

#endif // ABB_H
