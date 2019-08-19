#include "listafil.h"

#include <iostream>

listafil::listafil()
{
    inicio = NULL;
    //tam = 0;
}

void listafil::insertar(int f)
{
    nodofil *nuevo = new nodofil(f);
    if(inicio == NULL)
    {
        inicio = nuevo;
    } else if(nuevo->fil < inicio->fil)
    {
        nuevo->sig = inicio;
        inicio = nuevo;
    } else
    {
        nodofil *actual = inicio;
        while((actual->sig != NULL) && (nuevo->fil > actual->fil))
        {
            actual = actual->sig;
        }

        nuevo->sig = actual->sig;
        actual->sig = nuevo;

    }
}

nodofil* listafil::buscar(int f)
{
    nodofil *tmp = inicio;
    while(tmp != NULL)
    {
        if(tmp->fil == f)
        {
            return tmp;
        }
        tmp = tmp->sig;
    }
    return NULL;
}