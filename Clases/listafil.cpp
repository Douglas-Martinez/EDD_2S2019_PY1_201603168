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
        nodofil *actual, *anterior;
        actual = anterior = inicio;
        while((actual->sig != NULL) && (nuevo->fil > actual->fil))
        {
            anterior = actual;
            actual = actual->sig;
        }
        if(nuevo->fil > actual->fil)
        {
            anterior = actual;
        }
        nuevo->sig = anterior->sig;
        anterior->sig = nuevo;
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