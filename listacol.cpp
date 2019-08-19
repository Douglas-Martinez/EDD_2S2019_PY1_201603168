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
        nodocol *actual = inicio;
        while((actual->sig != NULL) && (nuevo->col > actual->col))
        {
            actual = actual->sig;
        }

        nuevo->sig = actual->sig;
        actual->sig = nuevo;

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