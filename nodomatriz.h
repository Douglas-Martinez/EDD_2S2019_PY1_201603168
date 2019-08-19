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
        //nodomatriz *frente;
        //nodomatriz *atras;

        nodomatriz(int f, int c, int z)
        {
            fila = f;
            columna = c;
            capa = z;
            //r = red;
            //g = green;
            //blue = b;

            arriba = NULL;
            abajo = NULL;
            izq = NULL;
            der = NULL;
            //frente = NULL;
            //atras = NULL;
        }
};

#endif // NODOMATRIZ_H