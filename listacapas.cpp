#include "listacapas.h"

listacapas::listacapas()
{
    inicio = NULL;
}

void listacapas::insertar(nodolistacapa *nuevo)
{
    if(inicio == NULL)
    {
        inicio = nuevo;
    } else
    {
        if(nuevo->id < inicio->id)
        {
            nuevo->sig = inicio;
            inicio = nuevo;
        } else
        {
            nodolistacapa *actual, *anterior;
            actual = anterior = inicio;
            while((actual->sig != NULL) && (nuevo->id > actual->id))
            {
                anterior = actual;
                actual = actual->sig;
            }
            if(nuevo->id > actual->id)
            {
                anterior = actual;
            }
            nuevo->sig = anterior->sig;
            anterior->sig = nuevo;
        }
        
    }
    
}

void listacapas::graficar_capas()
{
    nodolistacapa *aux = inicio;
    while(aux != NULL)
    {
        aux->capa->graficar();
        aux = aux->sig;
    }
}