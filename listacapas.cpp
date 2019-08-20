#include "listacapas.h"

listacapas::listacapas(std::string nomb)
{
    inicio = NULL;
    todo = new matriz(-1,nomb);
    linealizada = new listalineal();
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
        aux->capa->graficar(0);
        aux = aux->sig;
    }
}

void listacapas::sobreponer()
{
    nodolistacapa *tmp = inicio;
    while (tmp != NULL)
    {
        nodofil *auxF = tmp->capa->filas->inicio;
        while(auxF != NULL)
        {
            nodomatriz *auxM = auxF->der;
            while(auxM != NULL)
            {
                nodomatriz *otronuevo = new nodomatriz(auxM->fila,auxM->columna,auxM->capa);
                todo->poner(otronuevo);
                auxM = auxM->der;
            }
            auxF = auxF->sig;
        }
        tmp = tmp->sig;
    }
}

void listacapas::linealizar()
{
    linealizada->nombre = todo->nombre;
    sobreponer();
    int x = 0;
    int y = 0;
    
    nodofil *auxF = todo->filas->inicio;
    nodocol *auxC = todo->columnas->inicio;
    while(auxF != NULL)
    {
        y = auxF->fil;
        auxF = auxF->sig;
    }
    while(auxC != NULL)
    {
        x = auxC->col;
        auxC = auxC->sig;
    }
    //lineal por filas = i*columnas + j
    for (int q = 0; q < y; q++)
    {
        for (int w = 0; w < x; w++)
        {
            int pos = q*x+w;
            linealizada->insertar(new nodolineal(pos,q,w,"Nada"));
        }   
    }
    //Buscar y cambiar
    auxF = todo->filas->inicio;
    while(auxF != NULL)
    {
        nodomatriz *auxM = auxF->der;
        while(auxM != NULL)
        {
            int pos = (auxM->fila-1) * x + (auxM->columna)-1;
            std::string color = "Pos: " + std::to_string(pos) + " (" + std::to_string(auxM->fila) + "," + std::to_string(auxM->columna) + ") Color: #AlgoHexadecimal";
            nodolineal *bus = linealizada->buscar(pos);
            bus->colorH = color;
            auxM = auxM->der;
        }
        auxF = auxF->sig;
    }
}