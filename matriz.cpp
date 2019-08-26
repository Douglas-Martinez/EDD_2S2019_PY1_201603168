#include "matriz.h"

#include <cmath>

matriz::matriz(int z, std::string n)
{
    capa = z;
    nombre = n;
    filas = new listafil();
    columnas = new listacol();
}

void matriz::insertar(int f, int c, int r, int g, int b)
{
    /*
        yaExiste == 0 --> Significa que no existe
        yaExiste == 1 --> Significa que ya existe
    */
    if(buscar(f,c) == 0)
    {
        nodomatriz *nuevo = new nodomatriz(f,c,capa,r,g,b);
        nodofil *auxF = filas->buscar(f);
        nodocol *auxC = columnas->buscar(c);
        
        //Asignar en filas;
        if(auxF == NULL)
        {
            auxF = new nodofil(f);
            filas->insertar(f);
            auxF = filas->buscar(f);
            auxF->der = nuevo;
        } else 
        {
            //Va antes del primero
            if(nuevo->columna < auxF->der->columna)
            {
                nuevo->der = auxF->der;
                auxF->der->izq = nuevo;
                auxF->der = nuevo;
            } else
            {
                nodomatriz *auxM = auxF->der;
                while (auxM->der != NULL)
                {
                    if(nuevo->columna < auxM->der->columna)
                    {
                        nuevo->der = auxM->der;
                        auxM->der->izq = nuevo;
                        nuevo->izq = auxM;
                        auxM->der = nuevo;
                        break;
                    }
                    auxM = auxM->der;
                }
                auxM->der = nuevo;
                nuevo->izq = auxM;   
            }
        }

        //Asignar en columnas
        if(auxC == NULL)
        {
            auxC = new nodocol(c);
            columnas->insertar(c);
            auxC = columnas->buscar(c);
            auxC->abajo = nuevo;
        } else
        {
            if(nuevo->fila < auxC->abajo->fila)
            {
                nuevo->abajo = auxC->abajo;
                auxC->abajo->arriba = nuevo;
                auxC->abajo = nuevo;
            } else
            {
                nodomatriz *auxM = auxC->abajo;
                while (auxM->abajo != NULL)
                {
                    if (nuevo->fila < auxM->abajo->fila)
                    {
                        nuevo->abajo = auxM->abajo;
                        auxM->abajo->arriba = nuevo;
                        nuevo->arriba = auxM;
                        auxM->abajo = nuevo;
                        break;
                    }
                    auxM = auxM->abajo;
                }
                auxM->abajo = nuevo;
                nuevo->arriba = auxM;
            }
        }
    } else
    {
        std::cout << "Si existe" << std::endl;
    }   
}

nodomatriz* matriz::buscar(int f, int c)
{
    nodofil *auxF = filas->inicio;
    while (auxF != NULL)
    {
        if (auxF->fil == f)
        {
            nodomatriz *auxM = auxF->der;
            while(auxM != NULL)
            {
                if(auxM->columna == c)
                {
                    return auxM;
                }
                auxM = auxM->der;
            }
        }
        auxF = auxF->sig;
    }
    return NULL;
}

void matriz::graficar(int n,std::string car)
{
    std::string rut = "Capa_" + nombre + ".dot";
    std::string img = "Capa_" + nombre + ".png";
    std::string com = "neato -Tpng " + rut + " -o " + img;
    std::string dis = "eog " + img;
    
    FILE *f;
    f = fopen(rut.c_str(),"w+");
    if(f)
    {
        fprintf(f,"digraph matriz{\r\n");
        fprintf(f,"00000000[label=\"Matriz\",pos=\"0,0!\", style=\"filled\", fontcolor=\"white\", color=\"black\", shape=\"box\"];\r\n");
        if (filas->inicio != NULL && columnas->inicio != NULL)
        {
            fprintf(f,"\"00000000\"->\"F%i\";\r\n",filas->inicio->fil);
            fprintf(f,"\"00000000\"->\"C%i\";\r\n",columnas->inicio->col);
            generarCeldas(&f);
        }
        fprintf(f,"}");
        fclose(f);
        system(com.c_str());
        system(dis.c_str());
    }
}

void matriz::generarCeldas(FILE **f)
{
    //Filas
    nodofil *auxF = filas->inicio;
    while(auxF != NULL)
    {
        fprintf((*f),"\"F%i\"[label=\"F%i\", style=\"solid\", pos=\"0,%i!\", shape=\"box\"];\r\n",auxF->fil,auxF->fil,(0-auxF->fil));
        auxF =auxF->sig;
    }
    auxF = filas->inicio;
    if(auxF != NULL)
    {
        if(auxF->sig != NULL)
        {
            fprintf((*f),"\"F%i\"",auxF->fil);
            auxF = auxF->sig;
            while (auxF != NULL)
            {
                fprintf((*f),"->\"F%i\"",auxF->fil);
                auxF = auxF->sig;
            }
            fprintf((*f),"\r\n");
        }
    }
    
    //Columnas
    nodocol *auxC = columnas->inicio;
    while(auxC != NULL)
    {
        fprintf((*f),"\"C%i\"[label=\"C%i\", style=\"solid\", pos=\"%i,0!\", shape=\"box\"];\r\n",auxC->col,auxC->col,auxC->col+auxC->col);
        auxC =auxC->sig;
    }
    auxC = columnas->inicio;
    if(auxC != NULL)
    {
        if(auxC->sig != NULL)
        {
            fprintf((*f),"\"C%i\"",auxC->col);
            auxC = auxC->sig;
            while (auxC != NULL)
            {
                fprintf((*f),"->\"C%i\"",auxC->col);
                auxC = auxC->sig;
            }
            fprintf((*f),"\r\n");
        }
    }

    //Celdas
    auxF = filas->inicio;
    if(auxF != NULL)
    {
        while(auxF != NULL)
        {
            nodomatriz *auxM = auxF->der;
            while(auxM != NULL)
            {
                fprintf((*f),"\"%p\"[label=\"%s\", style=\"filled\", pos=\"%i,%i!\", shape=\"box\"];\r\n", auxM,rgb_h(auxM->r,auxM->g,auxM->b).c_str(),auxM->columna+auxM->columna,(0-auxM->fila));
                auxM = auxM->der;
            }
            auxF = auxF->sig;
        }
    }
    auxF = filas->inicio;
    while(auxF != NULL)
    {
        nodomatriz *auxM = auxF->der;
        fprintf((*f),"\"F%i\"",auxF->fil);
        while(auxM != NULL)
        {
            fprintf((*f),"->\"%p\"",auxM);
            auxM = auxM->der;
        }
        fprintf((*f),"\n[dir=both];\r\n");
        auxF = auxF->sig;
    }
    auxC = columnas->inicio;
    while(auxC != NULL)
    {
        nodomatriz *auxM = auxC->abajo;
        fprintf((*f),"\"C%i\"",auxC->col);
        while(auxM != NULL)
        {
            fprintf((*f),"->\"%p\"",auxM);
            auxM = auxM->abajo;
        }
        fprintf((*f),"\n[dir=both];\r\n");
        auxC = auxC->sig;
    }
}

void matriz::poner(nodomatriz *n)
{
    nodomatriz *b = buscar(n->fila,n->columna);
    if(b == 0)
    {
        nodomatriz *nuevo = n;
        nodofil *auxF = filas->buscar(n->fila);
        nodocol *auxC = columnas->buscar(n->columna);
        
        //Asignar en filas;
        if(auxF == NULL)
        {
            auxF = new nodofil(n->fila);
            filas->insertar(n->fila);
            auxF = filas->buscar(n->fila);
            auxF->der = nuevo;
        } else 
        {
            //Va antes del primero
            if(nuevo->columna < auxF->der->columna)
            {
                nuevo->der = auxF->der;
                auxF->der->izq = nuevo;
                auxF->der = nuevo;
            } else
            {
                nodomatriz *auxM = auxF->der;
                while (auxM->der != NULL)
                {
                    if(nuevo->columna < auxM->der->columna)
                    {
                        nuevo->der = auxM->der;
                        auxM->der->izq = nuevo;
                        nuevo->izq = auxM;
                        auxM->der = nuevo;
                        break;
                    }
                    auxM = auxM->der;
                }
                auxM->der = nuevo;
                nuevo->izq = auxM;   
            }
        }

        //Asignar en columnas
        if(auxC == NULL)
        {
            auxC = new nodocol(n->columna);
            columnas->insertar(n->columna);
            auxC = columnas->buscar(n->columna);
            auxC->abajo = nuevo;
        } else
        {
            if(nuevo->fila < auxC->abajo->fila)
            {
                nuevo->abajo = auxC->abajo;
                auxC->abajo->arriba = nuevo;
                auxC->abajo = nuevo;
            } else
            {
                nodomatriz *auxM = auxC->abajo;
                while (auxM->abajo != NULL)
                {
                    if (nuevo->fila < auxM->abajo->fila)
                    {
                        nuevo->abajo = auxM->abajo;
                        auxM->abajo->arriba = nuevo;
                        nuevo->arriba = auxM;
                        auxM->abajo = nuevo;
                        break;
                    }
                    auxM = auxM->abajo;
                }
                auxM->abajo = nuevo;
                nuevo->arriba = auxM;
            }
        }
    } else
    {
        b->capa = n->capa;
        b->r = n->r;
        b->g = n->g;
        b->b = n->b;
    }   
}

std::string matriz::rgb_h(int r, int g, int b)
{
    std::string res;

    char rh[255];
    sprintf(rh,"%.2X", r);
    res.append(rh);

    char gh[255];
    sprintf(gh,"%.2X", g);
    res.append(gh);

    char bh[255];
    sprintf(bh,"%.2X", b);
    res.append(bh);

    return "#" + res;
}

void matriz::filNegativo()
{
    nodofil *auxF = filas->inicio;
    while(auxF != NULL)
    {
        nodomatriz *auxM = auxF->der;
        while(auxM != NULL)
        {
            auxM->r = 255 - auxM->r;
            auxM->g = 255 - auxM->g;
            auxM->b = 255 - auxM->b;
            auxM = auxM->der;
        }
        auxF = auxF->sig;
    }
}

void matriz::filGris()
{
    nodofil *auxF = filas->inicio;
    while(auxF != NULL)
    {
        nodomatriz *auxM = auxF->der;
        while(auxM != NULL)
        {
            float g = auxM->r*0.2125 + auxM->g*0.7154 + auxM->b*0.0721;
            int gs = round(g);
            auxM->r = gs;
            auxM->g = gs;
            auxM->b = gs;
            auxM = auxM->der;
        }
        auxF = auxF->sig;
    }
}

void matriz::filMX(int nc)
{
    matriz *mx = new matriz(capa,nombre);
    nodofil *auxF = filas->inicio;
    nodocol *auxC = columnas->inicio;
    
    int c = nc;
    while(auxF != NULL)
    {
        nodomatriz *auxM = auxF->der;
        while(auxM != NULL)
        {
            mx->insertar(auxM->fila,(c-(auxM->columna-1)),auxM->r,auxM->g,auxM->b);
            auxM = auxM->der;
        }
        auxF = auxF->sig;
    }
    filas = NULL;
    columnas = NULL;
    filas = mx->filas;
    columnas = mx->columnas;
}

void matriz::filMY(int nf)
{
    matriz *mx = new matriz(capa,nombre);
    nodofil *auxF = filas->inicio;
    nodocol *auxC = columnas->inicio;
    
    int f = nf;
    while(auxF != NULL)
    {
        nodomatriz *auxM = auxF->der;
        while(auxM != NULL)
        {
            mx->insertar(f-(auxM->fila-1),auxM->columna,auxM->r,auxM->g,auxM->b);
            auxM = auxM->der;
        }
        auxF = auxF->sig;
    }
    filas = NULL;
    columnas = NULL;
    filas = mx->filas;
    columnas = mx->columnas;
}

void matriz::filMXY(int nf, int nc)
{
    matriz *mx = new matriz(capa,nombre);
    nodofil *auxF = filas->inicio;
    nodocol *auxC = columnas->inicio;
    
    int f = nf;
    int c = nc;
    while(auxF != NULL)
    {
        nodomatriz *auxM = auxF->der;
        while(auxM != NULL)
        {
            mx->insertar(f-(auxM->fila-1),(c-(auxM->columna-1)),auxM->r,auxM->g,auxM->b);
            auxM = auxM->der;
        }
        auxF = auxF->sig;
    }
    filas = NULL;
    columnas = NULL;
    filas = mx->filas;
    columnas = mx->columnas;
}

void matriz::filCollage(int f, int c, int nf, int nc)
{
    matriz *mx = new matriz(capa,nombre);
    nodofil *auxF = filas->inicio;
    
    int tf = nf;
    int tc = nc;
    for (int i = 0; i < f; i++)
    {
        for (int j = 0; j < c; j++)
        {
            auxF = filas->inicio;
            while(auxF != NULL)
            {
                nodomatriz *auxM = auxF->der;
                while(auxM != NULL)
                {
                    mx->insertar((nf*i)+auxM->fila,(nc*j)+auxM->columna,auxM->r,auxM->g,auxM->b);
                    auxM = auxM->der;
                }
                auxF = auxF->sig;
            }
        }   
    }
    filas = NULL;
    columnas = NULL;
    filas = mx->filas;
    columnas = mx->columnas;
}

void matriz::filMosaico(int totF, int totC, matriz *base)
{
    matriz *nuevamatriz = new matriz(base->capa,base->nombre);
                
    nodofil *auxFN = base->filas->inicio;
    while (auxFN != NULL)
    {
        nodomatriz *auxM = auxFN->der;
        while (auxM != NULL)
        {
            nuevamatriz->insertar(auxM->fila,auxM->columna,auxM->r,auxM->g,auxM->b);
            auxM = auxM->der;
        }
        auxFN = auxFN->sig;
    }
    nuevamatriz->llenar(totF,totC);

    matriz *mx = new matriz(capa,nombre);
    //nodofil *auxF = filas->inicio;
    nodofil *auxF = nuevamatriz->filas->inicio;

    for (int i = 0; i < totF; i++)
    {
        for (int j = 0; j < totC; j++)
        {
            if(nuevamatriz->buscar(i+1,j+1) != NULL)
            {
                auxF = nuevamatriz->filas->inicio;
                nodomatriz *temp = nuevamatriz->buscar(i+1,j+1);
                while(auxF != NULL)
                {
                    nodomatriz *auxM = auxF->der;
                    while(auxM != NULL)
                    {
                        mx->insertar((totF*i)+auxM->fila,(totC*j)+auxM->columna,(temp->r + auxM->r)/2,(temp->g + auxM->g)/2,(temp->b + auxM->b)/2);
                        auxM = auxM->der;
                    }
                    auxF = auxF->sig;
                }
            }
        }   
    }
    filas = NULL;
    columnas = NULL;
    filas = mx->filas;
    columnas = mx->columnas;
}

void matriz::llenar(int f, int c)
{
    matriz *mx = new matriz(capa,nombre);
    for (int i = 0; i < f; i++)
    {
        for (int j = 0; j < c; j++)
        {
            nodomatriz *aux = buscar(i+1,j+1);
            if(aux == NULL)
            {
                mx->insertar(i+1,j+1,51,51,51);
            } else
            {
                mx->insertar(aux->fila,aux->columna,aux->r,aux->g,aux->b);
            }
        }
    }
    filas = NULL;
    columnas = NULL;
    filas = mx->filas;
    columnas = mx->columnas;
}

void matriz::xFilas()
{
    std::string rut = "Filas_" + nombre + ".dot";
    std::string img = "Filas_" + nombre + ".png";
    std::string com = "dot -Tpng " + rut + " -o " + img;
    std::string dis = "eog " + img;

    FILE *f;
    f = fopen(rut.c_str(),"w+");
    if(f)
    {
        fprintf(f,"digraph Filas{\r\n");
        fprintf(f,"rankdir=LR;\r\n");
        if(filas != NULL)
        {
            nodofil *auxF = filas->inicio;
            nodomatriz *auxM = auxF->der;
            while(auxF != NULL)
            {
                auxM = auxF->der;
                nodomatriz *auxM = auxF->der;
                while(auxM != NULL)
                {
                    fprintf(f,"\"%p\"[label=\"(%i, %i) | %i-%i-%i\", style=\"filled\", shape=\"box\", fillcolor=\"beige\"];\r\n",auxM,auxM->fila,auxM->columna,auxM->r,auxM->g,auxM->b);
                    auxM = auxM->der;
                }
                auxF = auxF->sig;
            }
            int l = 0;
            auxF = filas->inicio;
            auxM = auxF->der;
            fprintf(f,"\"%p\"",auxM);
            auxM = auxM->der;
            while(auxF != NULL)
            {
                if(l == 0)
                {
                    l = 1;
                } else if(l == 1)
                {
                    auxM = auxF->der;
                }

                while(auxM != NULL)
                {
                    fprintf(f,"->\"%p\"",auxM);
                    auxM = auxM->der;
                }
                auxF = auxF->sig;
            }
        } else
        {
            fprintf(f,"\"Capa Vacia\";\r\n");
        }
        
        fprintf(f,"}");
        fclose(f);
        system(com.c_str());
        system(dis.c_str());
    }
}

void matriz::xColumnas()
{
    std::string rut = "Columnas_" + nombre + ".dot";
    std::string img = "Columnas_" + nombre + ".png";
    std::string com = "dot -Tpng " + rut + " -o " + img;
    std::string dis = "eog " + img;

    FILE *f;
    f = fopen(rut.c_str(),"w+");
    if(f)
    {
        fprintf(f,"digraph Columnas{\r\n");
        fprintf(f,"rankdir=TB;\r\n");
        if(filas != NULL)
        {
            nodocol *auxC = columnas->inicio;
            nodomatriz *auxM = auxC->abajo;
            while(auxC != NULL)
            {
                auxM = auxC->abajo;
                nodomatriz *auxM = auxC->abajo;
                while(auxM != NULL)
                {
                    fprintf(f,"\"%p\"[label=\"(%i, %i) | %i-%i-%i\", style=\"filled\", shape=\"box\", fillcolor=\"beige\"];\r\n",auxM,auxM->fila,auxM->columna,auxM->r,auxM->g,auxM->b);
                    auxM = auxM->abajo;
                }
                auxC = auxC->sig;
            }
            int l = 0;
            auxC = columnas->inicio;
            auxM = auxC->abajo;
            fprintf(f,"\"%p\"",auxM);
            auxM = auxM->abajo;
            while(auxC != NULL)
            {
                if(l == 0)
                {
                    l = 1;
                } else if(l == 1)
                {
                    auxM = auxC->abajo;
                }
                
                while(auxM != NULL)
                {
                    fprintf(f,"->\"%p\"",auxM);
                    auxM = auxM->abajo;
                }
                auxC = auxC->sig;
            }
        } else
        {
            fprintf(f,"\"Capa Vacia\";\r\n");
        }
        fprintf(f,"}");
        fclose(f);
        system(com.c_str());
        system(dis.c_str());
    }
}