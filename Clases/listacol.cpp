#include "listacol.h"

listacol::listacol()
{
    inicio = NULL;
}

void listacol::insertar(int c)
{
    nodocol *nuevo = new nodocol(c);
    if(inicio == NULL)
    {
        inicio = nuevo;
    } else if(nuevo->col < inicio->col)
    {
        nuevo->sig = inicio;
        inicio = nuevo;
    } else
    {
        nodocol *actual, *anterior;
        actual = anterior = inicio;
        while((actual->sig != NULL) && (nuevo->col > actual->col))
        {
            anterior = actual;
            actual = actual->sig;
        }
        if(nuevo->col > actual->col)
        {
            anterior = actual;
        }
        nuevo->sig = anterior->sig;
        anterior->sig = nuevo;
    }
}

nodocol* listacol::buscar(int c)
{
    nodocol *tmp = inicio;
    while(tmp != NULL)
    {
        if(tmp->col == c)
        {
            return tmp;
        }
        tmp = tmp->sig;
    }
    return NULL;
}