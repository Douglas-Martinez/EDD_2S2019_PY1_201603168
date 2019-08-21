#include "listalineal.h"

#include <iostream>

listalineal::listalineal()
{
    primero = NULL;
    ultimo = NULL;
}

void listalineal::insertar(nodolineal *nuevo)
{
    if(primero == NULL)
    {
        primero = nuevo;
        ultimo = nuevo;
    } else
    {
        ultimo->sig = nuevo;
        ultimo = nuevo;
    }   
}

nodolineal* listalineal::buscar(int p)
{
    nodolineal *tmp = primero;
    while(tmp != NULL)
    {
        if(tmp->pos == p)
        {
            return tmp;
        }
        tmp = tmp->sig;
    }
    return NULL;
}

void listalineal::graficar()
{
    std::string rut = "Exports/" + nombre + "/" + nombre + "_L.dot";
    std::string img = "Exports/" + nombre + "/" + nombre + "_L.png";
    std::string com = "dot -Tpng " + rut + " -o " + img;
    std::string dis = "eog " + img;
    
    FILE *f;
    f = fopen(rut.c_str(),"w+");
    if(f)
    {
        fprintf(f,"digraph matriz{\r\n");
        fprintf(f,"rankdir=LR;\r\n");
        nodolineal *aux = primero;
        while (aux != NULL)
        {
            fprintf(f,"\"%p\"[label=\"%i - %s\", style=\"filled\", shape=\"box\"];\r\n",aux,aux->pos,aux->colorH.c_str());
            aux = aux->sig;
        }
        aux = primero;
        if(aux != NULL)
        {
            if(aux->sig != NULL)
            {
                fprintf(f,"\"%p\"",aux);
                aux = aux->sig;
                while (aux != NULL)
                {
                    fprintf(f,"->\"%p\"",aux);
                    aux = aux->sig;
                }
                fprintf(f,"\r\n");
            }
        }
        fprintf(f,"}");
        fclose(f);
        system(com.c_str());
        //system(dis.c_str());
    }
}