#include "listacircular.h"
#include <fstream>

listacircular::listacircular()
{
    primero = NULL;
    ultimo = NULL;
}

void listacircular::insertar(nodocircular *nuevo)
{
    if(primero == NULL)
    {
        nuevo->id = 1;
        nuevo->sig = nuevo;
        nuevo->ant = nuevo;
        primero = nuevo;
        ultimo = nuevo;
    } else
    {
        nuevo->id = ultimo->id + 1;
        nuevo->sig = primero;
        nuevo->ant = ultimo;
        ultimo->sig = nuevo;
        primero->ant = nuevo;
        ultimo = nuevo;
    }
}

void listacircular::graficar()
{
    FILE *f = fopen("ListaFiltros.dot","w+");
    fprintf(f,"digraph Lista_Filtros{\r\n");
    fprintf(f,"node[shape=record];\r\n");
    fprintf(f,"rankdir=LR;\r\n");

    nodocircular *aux = primero;
    if(aux == NULL)
    {
        fprintf(f,"\t\"No hay filtros\"\r\n");
    } else 
    {
        if(primero == ultimo && primero != NULL)
        {
            fprintf(f,"\t\"%p\"[label=\"%s\"];\r\n",aux,aux->filtro.c_str());
            fprintf(f,"\t\"%p\"->\"%p\"\r\n",aux,aux->sig);
            fprintf(f,"\t\"%p\"->\"%p\"\r\n",aux,aux->ant);
        } else
        {
            do
            {
                fprintf(f,"\t\"%p\"[label=\"%s\"];\r\n",aux,aux->filtro.c_str());
                aux = aux->sig;
            } while (aux != primero);
            aux = primero;
            do
            {
                fprintf(f,"\t\"%p\"->\"%p\"\r\n",aux,aux->sig);
                fprintf(f,"\t\"%p\"->\"%p\"\r\n",aux,aux->ant);
                aux = aux->sig;
            } while (aux != primero);
        }
        
    }
    fprintf(f,"label = \"Filtros\"\r\n");
    fprintf(f,"}");
    fclose(f);
    system("dot -Tpng ListaFiltros.dot -o ListaFiltros.png");
    system("eog ListaFiltros.png");
}