#include "abb.h"

#include <iostream>
#include <string>

using namespace std;

void abb::insertar(string n, int dh, int dw, int ph, int pw, listacapas *l)
{
    if(raiz != NULL)
    {
        insertar(raiz,n,dh,dw,ph,pw,l);
    }
    else
    {
        raiz = new nodoabb(n,dh,dw,ph,pw,l);
    }
}

void abb::insertar(nodoabb *r, string n, int dh, int dw, int ph, int pw, listacapas *l)
{
    if(n < r->nombre)
    {
        if(r->ni != NULL)
        {
            insertar(r->ni,n,dh,dw,ph,pw,l);
        } else
        {
            //Aqui va si es por la izquierda
            r->ni = new nodoabb(n,dh,dw,ph,pw,l);
        }
    } else
    {
        if(r->nd != NULL)
        {
            insertar(r->nd,n,dh,dw,ph,pw,l);
        } else
        {
            //Aqui va si es por la derecha
            r->nd = new nodoabb(n,dh,dw,ph,pw,l);
        }
    }
}

nodoabb* abb::buscar(nodoabb *r, string n)
{
    nodoabb *aux = NULL;
    if(r != NULL)
    {
        if(r->nombre != n)
        {
            if(n < r->nombre)
            {
                aux = buscar(r->ni,n);
            } else
            {
                aux = buscar(r->nd,n);
            }
        } else
        {
            aux = r;
        }
    }
    return aux;
}

void abb::graficar()
{
    FILE *fichero = fopen("ABB.dot","w+");
    if(fichero)
    {
        fprintf(fichero,"digraph ABB {\r\n");
        fprintf(fichero,"node [shape=circle]\r\n");
        fprintf(fichero,"rankdir=\"TB\"\r\n");

        if(raiz == NULL)
        {
            fprintf(fichero,"\"Arbol vacio\";\r\n");
        } else
        {
            nodo(raiz,&fichero);
            link(raiz,&fichero);
        }
        fprintf(fichero,"label = \"Arbol ABB\";\r\n");
        fprintf(fichero,"}\r\n");
    } else
    {
        cout << "No se pudo abrir el archivo" << endl;
    }
    fclose(fichero);
    system("dot -Tpng ./ABB.dot -o ./ABB.png");
    system("eog ./ABB.png");
}

void abb::nodo(nodoabb *r, FILE **f)
{
    if(r != NULL)
    {
        fprintf((*f),"\"%p\"[label=\"%s\nDim:(%i,%i)\nPix:(%i,%i)\"];\r\n",r,r->nombre.c_str(),r->dimH,r->dimW,r->pixH,r->pixW);

    }
}

void abb::link(nodoabb *r, FILE **f)
{
    if(r != NULL)
    {
        if(r->ni != NULL)
        {
            fprintf((*f),"\"%p\"->\"%p\";\r\n",r,r->ni);
        }
        if(r->nd != NULL)
        {
            fprintf((*f),"\"%p\"->\"%p\";\r\n",r,r->nd);
        }
        nodo(r->ni,&(*f));
        nodo(r->nd,&(*f));
    }
}


void abb::recorridoIN(nodoabb *r)
{
    if(r != NULL)
    {
        recorridoIN(r->ni);
        cout << r->nombre << " -> ";
        recorridoIN(r->nd);
    }
}

void abb::recorridoPRE(nodoabb* r)
{
    if(r != NULL)
    {
        cout << r->nombre << " -> ";
        recorridoPRE(r->ni);
        recorridoPRE(r->nd);
    }
}

void abb::recorridoPOST(nodoabb* r)
{
    if(r != NULL)
    {
        recorridoPOST(r->ni);
        recorridoPOST(r->nd);
        cout << r->nombre << " -> ";
    }
}
