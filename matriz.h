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
        void insertar(int f, int c);
        nodomatriz *buscar(int f, int c);

        void graficar();
        void generarCeldas(FILE **f);
};

#endif // MATRIZ_H