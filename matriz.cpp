#include "matriz.h"

matriz::matriz(int z, std::string n)
{
    capa = z;
    nombre = n;
    filas = new listafil();
    columnas = new listacol();
}

void matriz::insertar(int f, int c)
{
    /*
        yaExiste == 0 --> Significa que no existe
        yaExiste == 1 --> Significa que ya existe
    */
    if(buscar(f,c) == 0)
    {
        nodomatriz *nuevo = new nodomatriz(f,c,capa);
        nodofil *auxF = filas->buscar(f);
        nodocol *auxC = columnas->buscar(c);
        
        //Asignar en filas;
        if(auxF == NULL)
        {
            auxF = new nodofil(f);
            filas->insertar(f);
            auxF = filas->buscar(f);
            auxF->der = nuevo;
        } else 
        {
            //Va antes del primero
            if(nuevo->columna < auxF->der->columna)
            {
                nuevo->der = auxF->der;
                auxF->der->izq = nuevo;
                auxF->der = nuevo;
            } else
            {
                nodomatriz *auxM = auxF->der;
                while (auxM->der != NULL)
                {
                    if(nuevo->columna < auxM->der->columna)
                    {
                        nuevo->der = auxM->der;
                        auxM->der->izq = nuevo;
                        nuevo->izq = auxM;
                        auxM->der = nuevo;
                        break;
                    }
                    auxM = auxM->der;
                }
                auxM->der = nuevo;
                nuevo->izq = auxM;   
            }
        }

        //Asignar en columnas
        if(auxC == NULL)
        {
            auxC = new nodocol(c);
            columnas->insertar(c);
            auxC = columnas->buscar(c);
            auxC->abajo = nuevo;
        } else
        {
            if(nuevo->fila < auxC->abajo->fila)
            {
                nuevo->abajo = auxC->abajo;
                auxC->abajo->arriba = nuevo;
                auxC->abajo = nuevo;
            } else
            {
                nodomatriz *auxM = auxC->abajo;
                while (auxM->abajo != NULL)
                {
                    if (nuevo->fila < auxM->abajo->fila)
                    {
                        nuevo->abajo = auxM->abajo;
                        auxM->abajo->arriba = nuevo;
                        nuevo->arriba = auxM;
                        auxM->abajo = nuevo;
                        break;
                    }
                }
                auxM->abajo = nuevo;
                nuevo->arriba = auxM;
            }
        }
    } else
    {
        std::cout << "Si existe" << std::endl;
    }
    
}

nodomatriz* matriz::buscar(int f, int c)
{
    nodofil *auxF = filas->inicio;
    while (auxF != NULL)
    {
        if (auxF->fil == f)
        {
            nodomatriz *auxM = auxF->der;
            while(auxM != NULL)
            {
                if(auxM->columna == c)
                {
                    return auxM;
                }
                auxM = auxM->der;
            }
        }
        auxF = auxF->sig;
    }
    return NULL;
}

void matriz::graficar()
{
    std::string rut = "Capa_" + nombre + ".dot";
    std::string img = "Capa_" + nombre + ".png";
    std::string com = "neato -Tpng " + rut + " -o " + img;
    std::string dis = "eog " + img;
    
    FILE *f;
    f = fopen(rut.c_str(),"w+");
    if(f)
    {
        fprintf(f,"digraph matriz{\r\n");
        fprintf(f,"00000000[label=\"Matriz\",pos=\"0,0!\", color=\"gray\", shape=\"box\"];\r\n");
        if (filas->inicio != NULL && columnas->inicio != NULL)
        {
            fprintf(f,"\"00000000\"->\"F%i\";\r\n",filas->inicio->fil);
            fprintf(f,"\"00000000\"->\"C%i\";\r\n",columnas->inicio->col);
            generarCeldas(&f);
        }
        fprintf(f,"}");
        fclose(f);
        system(com.c_str());
        system(dis.c_str());
    }
}

void matriz::generarCeldas(FILE **f)
{
    //Filas
    nodofil *auxF = filas->inicio;
    while(auxF != NULL)
    {
        fprintf((*f),"\"F%i\"[label=\"F%i\", style=\"filled\", pos=\"0,%i!\", color=\"honeydew1\", shape=\"box\"];\r\n",auxF->fil,auxF->fil,(0-auxF->fil));
        auxF =auxF->sig;
    }
    auxF = filas->inicio;
    if(auxF != NULL)
    {
        if(auxF->sig != NULL)
        {
            fprintf((*f),"\"F%i\"",auxF->fil);
            auxF = auxF->sig;
            while (auxF != NULL)
            {
                fprintf((*f),"->\"F%i\"",auxF->fil);
                auxF = auxF->sig;
            }
            fprintf((*f),"\r\n");
        }
    }
    
    //Columnas
    nodocol *auxC = columnas->inicio;
    while(auxC != NULL)
    {
        fprintf((*f),"\"C%i\"[label=\"C%i\", style=\"filled\", pos=\"%i,0!\", color=\"honeydew1\", shape=\"box\"];\r\n",auxC->col,auxC->col,(auxC->col));
        auxC =auxC->sig;
    }
    auxC = columnas->inicio;
    if(auxC != NULL)
    {
        if(auxC->sig != NULL)
        {
            fprintf((*f),"\"C%i\"",auxC->col);
            auxC = auxC->sig;
            while (auxC != NULL)
            {
                fprintf((*f),"->\"C%i\"",auxC->col);
                auxC = auxC->sig;
            }
            fprintf((*f),"\r\n");
        }
    }

    //Celdas
    auxF = filas->inicio;
    if(auxF != NULL)
    {
        while(auxF != NULL)
        {
            nodomatriz *auxM = auxF->der;
            while(auxM != NULL)
            {
                fprintf((*f),"\"%p\"[label=\"%i,%i\", style=\"filled\", pos=\"%i,%i!\", shape=\"box\"];\r\n", auxM,auxM->fila,auxM->columna,auxM->columna,(0-auxM->fila));
                auxM = auxM->der;
            }
            auxF = auxF->sig;
        }
    }
    auxF = filas->inicio;
    while(auxF != NULL)
    {
        nodomatriz *auxM = auxF->der;
        fprintf((*f),"\"F%i\"",auxF->fil);
        while(auxM != NULL)
        {
            fprintf((*f),"->\"%p\"",auxM);
            auxM = auxM->der;
        }
        fprintf((*f),"\n[dir=both];\r\n");
        auxF = auxF->sig;
    }
    auxC = columnas->inicio;
    while(auxC != NULL)
    {
        nodomatriz *auxM = auxC->abajo;
        fprintf((*f),"\"C%i\"",auxC->col);
        while(auxM != NULL)
        {
            fprintf((*f),"->\"%p\"",auxM);
            auxM = auxM->der;
        }
        fprintf((*f),"\n[dir=both];\r\n");
        auxC = auxC->sig;
    }
}