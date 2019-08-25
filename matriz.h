#ifndef MATRIZ_H
#define MATRIZ_H

#include "listafil.cpp"
#include "listacol.cpp"

#include <string>

class matriz
{
    public:
        int capa;
        std::string nombre;
        listacol *columnas;
        listafil *filas;

        matriz(int z, std::string n);
        void insertar(int f, int c, int r, int g, int b);
        void poner(nodomatriz *n);
        std::string rgb_h(int r, int g, int b);
        nodomatriz *buscar(int f, int c);

        void graficar(int n,std::string car);
        void generarCeldas(FILE **f);

        void filNegativo();
        void filGris();
        void filMX(int nc);
        void filMY(int nf);
        void filMXY(int nf, int nc);
        void filCollage(int f, int c, int totF, int totC);
        void filMosaico();
};

#endif // MATRIZ_H