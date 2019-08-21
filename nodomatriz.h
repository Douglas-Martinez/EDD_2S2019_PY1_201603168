#ifndef NODOMATRIZ_H
#define NODOMATRIZ_H

#include <iostream>

class nodomatriz
{
    public:
        int fila;
        int columna;
        int capa;
        int r;
        int g;
        int b;
        nodomatriz *arriba;
        nodomatriz *abajo;
        nodomatriz *izq;
        nodomatriz *der;

        nodomatriz(int f, int c, int z, int red, int green, int blue)
        {
            fila = f;
            columna = c;
            capa = z;
            r = red;
            g = green;
            b = blue;

            arriba = NULL;
            abajo = NULL;
            izq = NULL;
            der = NULL;
        }
};

#endif // NODOMATRIZ_H