#include "abblineal.h"

abblineal::abblineal()
{
    primero = NULL;
    ultimo = NULL;
}

void abblineal::insertar(nodoabblineal *n)
{
    if(primero == NULL)
    {
        n->pos = 1;
        primero = n;
        ultimo = n;
    } else 
    {
        n->pos = ultimo->pos+1;
        ultimo->sig = n;
        ultimo = n;
    }
}