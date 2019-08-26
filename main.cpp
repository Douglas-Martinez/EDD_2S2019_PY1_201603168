#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Clases/abb.cpp"
#include "Clases/matriz.cpp"
#include "Clases/listacapas.cpp"
#include "Clases/listacircular.cpp"

using namespace std;

void menu();
void insert1();
void select2();
void filters3();
void editing4();
void export5();
void reports6();
int select();
nodoabb* selectIm();
nodoabb* selectFilter();
nodoabb* selectFilterNo();

static abb *arbolBin = new abb();
static nodoabb *selected = NULL;
static listacircular *filtros = new listacircular();

int main()
{
    cout << "Proyecto No. 1 - 201603168\n" << endl;
    menu();
    return 0;
}

void menu()
{
    string op = "";
    do
    {
        cout << "========== MENU ==========" << endl;
        cout << "1. Insert Image" << endl;
        cout << "2. Select Image" << endl;
        cout << "3. Apply Filters" << endl;
        cout << "4. Manual Editing" << endl;
        cout << "5. Export Image" << endl;
        cout << "6. Reports" << endl;
        cout << "7. Exit" << endl;
        cin >> op;
        cout << endl;

        if(op.compare("1") == 0)
        {
            insert1();
        } else if(op.compare("2") == 0)
        {
            if(arbolBin->raiz == NULL)
            {
                cout << "No hay imagenes importadas para poder seleccionar" << endl;
            } else 
            {
                select2();
                selected->listaC->sobreponer();
                filtros = new listacircular();
            }
        } else if(op.compare("3") == 0)
        {
            if(selected == NULL)
            {
                cout << "No hay una imagen seleccionada para poder continuar" << endl;
            } else
            {
                filters3();
            }
        } else if(op.compare("4") == 0)
        {
            if(selected == NULL)
            {
                cout << "No hay una imagen seleccionada para poder continuar" << endl;
            } else
            {
                editing4();
            }
        } else if(op.compare("5") == 0)
        {
            if(selected == NULL)
            {
                cout << "No hay una imagen seleccionada para poder continuar" << endl;
            } else
            {
                export5();
            }
        } else if(op.compare("6") == 0)
        {
            reports6();
        } else if(op.compare("7") == 0)
        {
            cout << "========== FIN ==========" << endl;
        } else
        {
            cout << "Wrong option, please try again." << endl;
            cout << endl;
        }
    } while (op.compare("7") != 0);
}

void insert1()
{
    cout << "========== IMAGEN ==========" << endl;
    string init = "";
    cout << "Ingresa la direccion de tu archivo inicial" << endl;
    cin >> init;
    cout << endl;
    ifstream archivo;
    archivo.open(init,ios::in);
    if(!archivo.fail())
    {
        string texto;
        string nombrei;
        string carpeta;

        stringstream n(init);
        getline(n,carpeta,'/');
        getline(n,nombrei,'.');
        int dh,dw, ph, pw;
        dh = dw = ph = pw = 0;
        listacapas *lista = new listacapas(nombrei);

        int con = 0;
        while(archivo.peek() != EOF)
        {
            getline(archivo,texto);
            if(con != 0)
            {
                stringstream ss(texto);
                string layer;
                string file;
                getline(ss,layer,',');
                getline(ss,file,'\n');
                
                if(layer == "0")
                {
                    string lineaC = "";
                    ifstream config;
                    string r2 = carpeta + "/" + file;
                    config.open(r2,ios::in);
                    int con2 = 0;
                    while(config.peek() != EOF)
                    {
                        getline(config,lineaC);
                        if(con2 != 0)
                        {
                            stringstream sss(lineaC);
                            string at = "";
                            string val = "";
                            getline(sss,at,',');
                            getline(sss,val,'\n');
                            if(at == "image_width")
                            {
                                dw = stoi(val);
                            } else if(at == "image_height")
                            {
                                dh = stoi(val);
                            } else if(at == "pixel_width")
                            {
                                pw = stoi(val);
                            } else if(at == "pixel_height")
                            {
                                ph = stoi(val);
                            }
                        }
                        con2++;
                    }
                } else
                {
                    int contF = 1;
                    int contC = 1;

                    ifstream im;
                    string rI = carpeta + "/" + file;
                    string lineaI = "";

                    string nI = "";
                    stringstream sni(file);
                    getline(sni,nI,'.');

                    matriz *m = new matriz(stoi(layer),nI);

                    im.open(rI,ios::in);
                    while(im.peek() != EOF)
                    {
                        getline(im,lineaI);
                        stringstream sss(lineaI);
                        string c;
                        while(getline(sss,c,','))
                        {
                            if((c != "x") && (c != "X") && (c != ""))
                            {
                                string r;
                                string g;
                                string b;
                                stringstream colores(c);
                                getline(colores,r,'-');
                                getline(colores,g,'-');
                                getline(colores,b,'\n');
                                int ir, ig, ib;
                                ir  = stoi(r);
                                ig  = stoi(g);
                                ib  = stoi(b);
                                m->insertar(contF,contC,ir,ig,ib);
                            }
                            contC++;
                        }
                        contC = 1;
                        contF++;
                    }
                    nodolistacapa *nuevo = new nodolistacapa(stoi(layer),nI,m);
                    lista->insertar(nuevo);
                }
            }
            con ++;
        }
        arbolBin->insertar(nombrei,dh,dw,ph,pw,lista);
        //cout << "Imagen ingresada\n" << endl;
        archivo.close();
    } else
    {
        cout << "No se pudo abrir el archivo" << endl;
    }
}

void select2()
{
    cout << "========== SELECCION ==========" << endl;   
    arbolBin->trasversalIN = new abblineal();
    arbolBin->recorridoIN(arbolBin->raiz);
    nodoabblineal *aux = arbolBin->trasversalIN->primero;
    while(aux != NULL)
    {
        cout << aux->pos << ". " << aux->nombre << endl;
        aux = aux->sig;
    }
    string op = "";
    string name = "";
    int si = 0;
    do
    {
        cout << "Elige un numero de imagen: ";
        cin >> op;
        aux = arbolBin->trasversalIN->primero;
        while(aux != NULL)
        {
            if(op == to_string(aux->pos))
            {
                name = aux->nombre;
                si = 1;
                break;
            }
            aux = aux->sig;
        }
        if(si == 0)
        {
            cout << "Opcion incorrecta\n" << endl;
        }
    } while (si != 1);
    selected = arbolBin->buscar(arbolBin->raiz,name);
    cout << "Imagen seleccionada: " << name << endl;
    cout << endl;
}

void filters3()
{
    string op = "";
    do
    {
        cout << "========== FILTROS ==========" << endl;
        cout << "1. Negative" << endl;
        cout << "2. Grayscale" << endl;
        cout << "3. Mirror" << endl;
        cout << "4. Collage" << endl;
        cout << "5. Mosaic" << endl;
        cin >> op;
        cout << endl;

        if(op == "1")
        {
            //N
            nodocircular *nuevo = new nodocircular();
            nuevo->filtro = "Negativo";
            nuevo->capa = selected->nombre;
            listacapas *nlist = new listacapas(selected->nombre);

            //Nueva Lista de Capas
            nodolistacapa *auxl = selected->listaC->inicio;
            while(auxl != NULL)
            {
                //Nueva Matriz
                matriz *nuevamatriz = new matriz(auxl->capa->capa,auxl->capa->nombre);
                
                nodofil *auxF = auxl->capa->filas->inicio;
                while (auxF != NULL)
                {
                    nodomatriz *auxM = auxF->der;
                    while (auxM != NULL)
                    {
                        nuevamatriz->insertar(auxM->fila,auxM->columna,auxM->r,auxM->g,auxM->b);
                        auxM = auxM->der;
                    }
                    auxF = auxF->sig;
                }
                //Nuevo nodo de capa
                nodolistacapa *nuevonodocapa = new nodolistacapa(auxl->id,auxl->nombre,nuevamatriz);
                //Inserto el nuevo nodo a la listanueva
                nlist->insertar(nuevonodocapa);
                auxl = auxl->sig;
            }
            
            int tipo = select();
            if(tipo == 1)
            {
                nodolistacapa *auxLC = nlist->inicio;
                while(auxLC != NULL)
                {
                    auxLC->capa->filNegativo();
                    auxLC = auxLC->sig;
                }
                nodoabb *nodoabbcopiadoparalalistadefiltros = new nodoabb("Negativo_Completo_" + selected->nombre,selected->dimH,selected->dimW,selected->pixH,selected->pixW,nlist);
                nodoabbcopiadoparalalistadefiltros->fr = 255 - nodoabbcopiadoparalalistadefiltros->fr;
                nodoabbcopiadoparalalistadefiltros->fg = 255 - nodoabbcopiadoparalalistadefiltros->fg;
                nodoabbcopiadoparalalistadefiltros->fb = 255 - nodoabbcopiadoparalalistadefiltros->fb;
                //nodoabbcopiadoparalalistadefiltros->generar();
                nuevo->fil = nodoabbcopiadoparalalistadefiltros;
            } else
            {
                int si = 0;
                matriz *sel;
                do
                {   
                    nodolistacapa *auxLC = nlist->inicio;
                    cout << "----- CAPAS -----" << endl;
                    string opc = "";
                    while(auxLC != NULL)
                    {
                        cout << auxLC->id << ". " << auxLC->nombre << endl;
                        auxLC = auxLC->sig;
                    }
                    cout << "Selecciona el numero de una capa: ";
                    cin >> opc;
                    cout << endl;
                    auxLC = nlist->inicio;
                    while(auxLC != NULL)
                    {
                        if(to_string(auxLC->id) == opc)
                        {
                            sel = auxLC->capa;
                            sel->filNegativo();
                            si = 1;
                            break;
                        }
                        auxLC = auxLC->sig;
                    }
                    if(si == 0)
                    {
                        cout << "La numero de capa elegida no coincide con alguna de las capas listadas previamente\n" << endl;
                    }
                } while (si != 1);
                nodoabb *nodoabbcopiadoparalalistadefiltros = new nodoabb("Negativo_Capa_" + sel->nombre + "_:" + selected->nombre,selected->dimH,selected->dimW,selected->pixH,selected->pixW,nlist);
                //nodoabbcopiadoparalalistadefiltros->generar();
                nuevo->fil = nodoabbcopiadoparalalistadefiltros;
            }
            //nodoabbcopiadoparalalistadefiltros->generar();
            //nuevo->fil = nodoabbcopiadoparalalistadefiltros;
            filtros->insertar(nuevo);
        } else if(op == "2")
        {
            //N
            nodocircular *nuevo = new nodocircular();
            nuevo->filtro = "GrayScale";
            nuevo->capa = selected->nombre;
            listacapas *nlist = new listacapas(selected->nombre);

            //Nueva Lista de Capas
            nodolistacapa *auxl = selected->listaC->inicio;
            while(auxl != NULL)
            {
                //Nueva Matriz
                matriz *nuevamatriz = new matriz(auxl->capa->capa,auxl->capa->nombre);
                
                nodofil *auxF = auxl->capa->filas->inicio;
                while (auxF != NULL)
                {
                    nodomatriz *auxM = auxF->der;
                    while (auxM != NULL)
                    {
                        nuevamatriz->insertar(auxM->fila,auxM->columna,auxM->r,auxM->g,auxM->b);
                        auxM = auxM->der;
                    }
                    auxF = auxF->sig;
                }
                //Nuevo nodo de capa
                nodolistacapa *nuevonodocapa = new nodolistacapa(auxl->id,auxl->nombre,nuevamatriz);
                //Inserto el nuevo nodo a la listanueva
                nlist->insertar(nuevonodocapa);
                auxl = auxl->sig;
            }
            
            int tipo = select();
            if(tipo == 1)
            {
                nodolistacapa *auxLC = nlist->inicio;
                while(auxLC != NULL)
                {
                    auxLC->capa->filGris();
                    auxLC = auxLC->sig;
                }
                nodoabb *nodoabbcopiadoparalalistadefiltros = new nodoabb("GrayScale_Completo_" + selected->nombre,selected->dimH,selected->dimW,selected->pixH,selected->pixW,nlist);
                //nodoabbcopiadoparalalistadefiltros->generar();
                nuevo->fil = nodoabbcopiadoparalalistadefiltros;
            } else
            {
                int si = 0;
                matriz *sel;
                do
                {   
                    nodolistacapa *auxLC = nlist->inicio;
                    cout << "----- CAPAS -----" << endl;
                    string opc = "";
                    while(auxLC != NULL)
                    {
                        cout << auxLC->id << ". " << auxLC->nombre << endl;
                        auxLC = auxLC->sig;
                    }
                    cout << "Selecciona el numero de una capa: ";
                    cin >> opc;
                    cout << endl;
                    auxLC = nlist->inicio;
                    while(auxLC != NULL)
                    {
                        if(to_string(auxLC->id) == opc)
                        {
                            sel = auxLC->capa;
                            sel->filGris();
                            si = 1;
                            break;
                        }
                        auxLC = auxLC->sig;
                    }
                    if(si == 0)
                    {
                        cout << "La numero de capa elegida no coincide con alguna de las capas listadas previamente\n" << endl;
                    }
                } while (si != 1);
                nodoabb *nodoabbcopiadoparalalistadefiltros = new nodoabb("GrayScale_Capa_" + sel->nombre + "_:" + selected->nombre,selected->dimH,selected->dimW,selected->pixH,selected->pixW,nlist);
                //nodoabbcopiadoparalalistadefiltros->generar();
                nuevo->fil = nodoabbcopiadoparalalistadefiltros;
            }
            //nodoabbcopiadoparalalistadefiltros->generar();
            //nuevo->fil = nodoabbcopiadoparalalistadefiltros;
            filtros->insertar(nuevo);
        } else if(op == "3")
        {
            int si2 = 0;
            string op2 = "";
            do
            {
                cout << "========== ESPEJO ==========" << endl;
                cout << "1. X-Mirror" << endl;
                cout << "2. Y-Mirror" << endl;
                cout << "3. Double Mirror" << endl;
                cin >> op2;
                cout << endl;
                if(op2 == "1")
                {
                    //N
                    nodocircular *nuevo = new nodocircular();
                    nuevo->filtro = "EspejoX";
                    nuevo->capa = selected->nombre;
                    listacapas *nlist = new listacapas(selected->nombre);

                    //Nueva Lista de Capas
                    nodolistacapa *auxl = selected->listaC->inicio;
                    while(auxl != NULL)
                    {
                        //Nueva Matriz
                        matriz *nuevamatriz = new matriz(auxl->capa->capa,auxl->capa->nombre);
                        
                        nodofil *auxF = auxl->capa->filas->inicio;
                        while (auxF != NULL)
                        {
                            nodomatriz *auxM = auxF->der;
                            while (auxM != NULL)
                            {
                                nuevamatriz->insertar(auxM->fila,auxM->columna,auxM->r,auxM->g,auxM->b);
                                auxM = auxM->der;
                            }
                            auxF = auxF->sig;
                        }
                        //Nuevo nodo de capa
                        nodolistacapa *nuevonodocapa = new nodolistacapa(auxl->id,auxl->nombre,nuevamatriz);
                        //Inserto el nuevo nodo a la listanueva
                        nlist->insertar(nuevonodocapa);
                        auxl = auxl->sig;
                    }

                    int nc = 0;
                    nodocol *aac = selected->listaC->todo->columnas->inicio;
                    while(aac != NULL)
                    {
                        nc = aac->col;
                        aac = aac->sig;
                    }

                    int tipo = select();
                    if(tipo == 1)
                    {
                        nodolistacapa *auxLC = nlist->inicio;
                        while(auxLC != NULL)
                        {
                            auxLC->capa->filMX(nc);
                            auxLC = auxLC->sig;
                        }
                        nodoabb *nodoabbcopiadoparalalistadefiltros = new nodoabb("EspejoX_Completo_" + selected->nombre,selected->dimH,selected->dimW,selected->pixH,selected->pixW,nlist);
                        //nodoabbcopiadoparalalistadefiltros->generar();
                        nuevo->fil = nodoabbcopiadoparalalistadefiltros;
                    } else
                    {
                        int si = 0;
                        matriz *sel;
                        do
                        {   
                            nodolistacapa *auxLC = nlist->inicio;
                            cout << "----- CAPAS -----" << endl;
                            string opc = "";
                            while(auxLC != NULL)
                            {
                                cout << auxLC->id << ". " << auxLC->nombre << endl;
                                auxLC = auxLC->sig;
                            }
                            cout << "Selecciona el numero de una capa: ";
                            cin >> opc;
                            cout << endl;
                            auxLC = nlist->inicio;
                            while(auxLC != NULL)
                            {
                                if(to_string(auxLC->id) == opc)
                                {
                                    sel = auxLC->capa;
                                    sel->filMX(nc);
                                    si = 1;
                                    break;
                                }
                                auxLC = auxLC->sig;
                            }
                            if(si == 0)
                            {
                                cout << "La numero de capa elegida no coincide con alguna de las capas listadas previamente\n" << endl;
                            }
                        } while (si != 1);
                        nodoabb *nodoabbcopiadoparalalistadefiltros = new nodoabb("EspejoX_Capa_" + sel->nombre + "_:" + selected->nombre,selected->dimH,selected->dimW,selected->pixH,selected->pixW,nlist);
                        //nodoabbcopiadoparalalistadefiltros->generar();
                        nuevo->fil = nodoabbcopiadoparalalistadefiltros;
                    }
                    //nodoabbcopiadoparalalistadefiltros->generar();
                    //nuevo->fil = nodoabbcopiadoparalalistadefiltros;
                    filtros->insertar(nuevo);
                } else if(op2 == "2")
                {
                    //N
                    nodocircular *nuevo = new nodocircular();
                    nuevo->filtro = "EspejoY";
                    nuevo->capa = selected->nombre;
                    listacapas *nlist = new listacapas(selected->nombre);

                    //Nueva Lista de Capas
                    nodolistacapa *auxl = selected->listaC->inicio;
                    while(auxl != NULL)
                    {
                        //Nueva Matriz
                        matriz *nuevamatriz = new matriz(auxl->capa->capa,auxl->capa->nombre);
                        
                        nodofil *auxF = auxl->capa->filas->inicio;
                        while (auxF != NULL)
                        {
                            nodomatriz *auxM = auxF->der;
                            while (auxM != NULL)
                            {
                                nuevamatriz->insertar(auxM->fila,auxM->columna,auxM->r,auxM->g,auxM->b);
                                auxM = auxM->der;
                            }
                            auxF = auxF->sig;
                        }
                        //Nuevo nodo de capa
                        nodolistacapa *nuevonodocapa = new nodolistacapa(auxl->id,auxl->nombre,nuevamatriz);
                        //Inserto el nuevo nodo a la listanueva
                        nlist->insertar(nuevonodocapa);
                        auxl = auxl->sig;
                    }

                    int nf = 0;
                    nodofil *aaf = selected->listaC->todo->filas->inicio;
                    while(aaf != NULL)
                    {
                        nf = aaf->fil;
                        aaf = aaf->sig;
                    }

                    int tipo = select();
                    if(tipo == 1)
                    {
                        nodolistacapa *auxLC = nlist->inicio;
                        while(auxLC != NULL)
                        {
                            auxLC->capa->filMY(nf);
                            auxLC = auxLC->sig;
                        }
                        nodoabb *nodoabbcopiadoparalalistadefiltros = new nodoabb("EspejoY_Completo_" + selected->nombre,selected->dimH,selected->dimW,selected->pixH,selected->pixW,nlist);
                        //nodoabbcopiadoparalalistadefiltros->generar();
                        nuevo->fil = nodoabbcopiadoparalalistadefiltros;
                    } else
                    {
                        int si = 0;
                        matriz *sel;
                        do
                        {   
                            nodolistacapa *auxLC = nlist->inicio;
                            cout << "----- CAPAS -----" << endl;
                            string opc = "";
                            while(auxLC != NULL)
                            {
                                cout << auxLC->id << ". " << auxLC->nombre << endl;
                                auxLC = auxLC->sig;
                            }
                            cout << "Selecciona el numero de una capa: ";
                            cin >> opc;
                            cout << endl;
                            auxLC = nlist->inicio;
                            while(auxLC != NULL)
                            {
                                if(to_string(auxLC->id) == opc)
                                {
                                    sel = auxLC->capa;
                                    sel->filMY(nf);
                                    si = 1;
                                    break;
                                }
                                auxLC = auxLC->sig;
                            }
                            if(si == 0)
                            {
                                cout << "La numero de capa elegida no coincide con alguna de las capas listadas previamente\n" << endl;
                            }
                        } while (si != 1);
                        nodoabb *nodoabbcopiadoparalalistadefiltros = new nodoabb("EspejoY_Capa_" + sel->nombre + "_:" + selected->nombre,selected->dimH,selected->dimW,selected->pixH,selected->pixW,nlist);
                        //nodoabbcopiadoparalalistadefiltros->generar();
                        nuevo->fil = nodoabbcopiadoparalalistadefiltros;
                    }

                    //nodoabbcopiadoparalalistadefiltros->generar();
                    //nuevo->fil = nodoabbcopiadoparalalistadefiltros;
                    filtros->insertar(nuevo);
                } else if(op2 == "3")
                {
                    //N
                    nodocircular *nuevo = new nodocircular();
                    nuevo->filtro = "DobleEspejo";
                    nuevo->capa = selected->nombre;
                    listacapas *nlist = new listacapas(selected->nombre);

                    //Nueva Lista de Capas
                    nodolistacapa *auxl = selected->listaC->inicio;
                    while(auxl != NULL)
                    {
                        //Nueva Matriz
                        matriz *nuevamatriz = new matriz(auxl->capa->capa,auxl->capa->nombre);
                        
                        nodofil *auxF = auxl->capa->filas->inicio;
                        while (auxF != NULL)
                        {
                            nodomatriz *auxM = auxF->der;
                            while (auxM != NULL)
                            {
                                nuevamatriz->insertar(auxM->fila,auxM->columna,auxM->r,auxM->g,auxM->b);
                                auxM = auxM->der;
                            }
                            auxF = auxF->sig;
                        }
                        //Nuevo nodo de capa
                        nodolistacapa *nuevonodocapa = new nodolistacapa(auxl->id,auxl->nombre,nuevamatriz);
                        //Inserto el nuevo nodo a la listanueva
                        nlist->insertar(nuevonodocapa);
                        auxl = auxl->sig;
                    }

                    int nf = 0;
                    nodofil *aaf = selected->listaC->todo->filas->inicio;
                    while(aaf != NULL)
                    {
                        nf = aaf->fil;
                        aaf = aaf->sig;
                    }
                    int nc = 0;
                    nodocol *aac = selected->listaC->todo->columnas->inicio;
                    while(aac != NULL)
                    {
                        nc = aac->col;
                        aac = aac->sig;
                    }
                    int tipo = select();
                    if(tipo == 1)
                    {
                        nodolistacapa *auxLC = nlist->inicio;
                        while(auxLC != NULL)
                        {
                            auxLC->capa->filMXY(nf,nc);
                            auxLC = auxLC->sig;
                        }
                        nodoabb *nodoabbcopiadoparalalistadefiltros = new nodoabb("DobleEspejo_Completo_" + selected->nombre,selected->dimH,selected->dimW,selected->pixH,selected->pixW,nlist);
                        //nodoabbcopiadoparalalistadefiltros->generar();
                        nuevo->fil = nodoabbcopiadoparalalistadefiltros;
                    } else
                    {
                        int si = 0;
                        matriz *sel;
                        do
                        {   
                            nodolistacapa *auxLC = nlist->inicio;
                            cout << "----- CAPAS -----" << endl;
                            string opc = "";
                            while(auxLC != NULL)
                            {
                                cout << auxLC->id << ". " << auxLC->nombre << endl;
                                auxLC = auxLC->sig;
                            }
                            cout << "Selecciona el numero de una capa: ";
                            cin >> opc;
                            cout << endl;
                            auxLC = nlist->inicio;
                            while(auxLC != NULL)
                            {
                                if(to_string(auxLC->id) == opc)
                                {
                                    sel = auxLC->capa;
                                    sel->filMXY(nf,nc);
                                    si = 1;
                                    break;
                                }
                                auxLC = auxLC->sig;
                            }
                            if(si == 0)
                            {
                                cout << "La numero de capa elegida no coincide con alguna de las capas listadas previamente\n" << endl;
                            }
                        } while (si != 1);
                        nodoabb *nodoabbcopiadoparalalistadefiltros = new nodoabb("DobleEspejos_Capa_" + sel->nombre + "_:" + selected->nombre,selected->dimH,selected->dimW,selected->pixH,selected->pixW,nlist);
                        //nodoabbcopiadoparalalistadefiltros->generar();
                        nuevo->fil = nodoabbcopiadoparalalistadefiltros;
                    }
                    filtros->insertar(nuevo);
                } else
                {
                    cout << "Error con la seleccion de espejo" << endl;
                }
                
            } while ((op2 != "1") && (op2 != "2") && (op2 != "3"));
        } else if(op == "4")
        {
            int fil = 0;
            int col = 0;
            cout << "Numero de Filas: ";
            cin >> fil;
            cout << "Numero de Colummas: ";
            cin >> col;
            cout << "Fil: " << fil << ", Col: " << col << endl;
            cout << endl;
            
            //Collage
            //N
            nodocircular *nuevo = new nodocircular();
            nuevo->filtro = "Collage";
            nuevo->capa = selected->nombre;
            listacapas *nlist = new listacapas(selected->nombre);

            //Nueva Lista de Capas
            nodolistacapa *auxl = selected->listaC->inicio;
            while(auxl != NULL)
            {
                //Nueva Matriz
                matriz *nuevamatriz = new matriz(auxl->capa->capa,auxl->capa->nombre);
                
                nodofil *auxF = auxl->capa->filas->inicio;
                while (auxF != NULL)
                {
                    nodomatriz *auxM = auxF->der;
                    while (auxM != NULL)
                    {
                        nuevamatriz->insertar(auxM->fila,auxM->columna,auxM->r,auxM->g,auxM->b);
                        auxM = auxM->der;
                    }
                    auxF = auxF->sig;
                }
                //Nuevo nodo de capa
                nodolistacapa *nuevonodocapa = new nodolistacapa(auxl->id,auxl->nombre,nuevamatriz);
                //Inserto el nuevo nodo a la listanueva
                nlist->insertar(nuevonodocapa);
                auxl = auxl->sig;
            }
            int nf = 0;
            nodofil *aaf = selected->listaC->todo->filas->inicio;
            while(aaf != NULL)
            {
                nf = aaf->fil;
                aaf = aaf->sig;
            }
            int nc = 0;
            nodocol *aac = selected->listaC->todo->columnas->inicio;
            while(aac != NULL)
            {
                nc = aac->col;
                aac = aac->sig;
            }
            nodolistacapa *auxLC = nlist->inicio;
            while(auxLC != NULL)
            {
                auxLC->capa->filCollage(fil,col,nf,nc);
                auxLC = auxLC->sig;
            }
            nodoabb *nodoabbcopiadoparalalistadefiltros = new nodoabb("Collage_"+selected->nombre+"_"+to_string(fil)+"x"+to_string(col),selected->dimH,selected->dimW,selected->pixH,selected->pixW,nlist);
            nodoabbcopiadoparalalistadefiltros->dimW = nodoabbcopiadoparalalistadefiltros->dimW * col;
            nodoabbcopiadoparalalistadefiltros->dimH = nodoabbcopiadoparalalistadefiltros->dimH * fil;
            //nodoabbcopiadoparalalistadefiltros->generar();
            nuevo->fil = nodoabbcopiadoparalalistadefiltros;
            filtros->insertar(nuevo);
        } else if(op == "5")
        {
            //Mosaico
            //N
            nodocircular *nuevo = new nodocircular();
            nuevo->filtro = "Mosaico";
            nuevo->capa = selected->nombre;
            listacapas *nlist = new listacapas(selected->nombre);
            
            //Nueva Lista de Capas
            nodolistacapa *auxl = selected->listaC->inicio;
            while(auxl != NULL)
            {
                //Nueva Matriz
                matriz *nuevamatriz = new matriz(auxl->capa->capa,auxl->capa->nombre);
                
                nodofil *auxF = auxl->capa->filas->inicio;
                while (auxF != NULL)
                {
                    nodomatriz *auxM = auxF->der;
                    while (auxM != NULL)
                    {
                        nuevamatriz->insertar(auxM->fila,auxM->columna,auxM->r,auxM->g,auxM->b);
                        auxM = auxM->der;
                    }
                    auxF = auxF->sig;
                }
                //Nuevo nodo de capa
                nodolistacapa *nuevonodocapa = new nodolistacapa(auxl->id,auxl->nombre,nuevamatriz);
                //Inserto el nuevo nodo a la listanueva
                nlist->insertar(nuevonodocapa);
                auxl = auxl->sig;
            }
            int nf = 0;
            nodofil *aaf = selected->listaC->todo->filas->inicio;
            while(aaf != NULL)
            {
                nf = aaf->fil;
                aaf = aaf->sig;
            }
            int nc = 0;
            nodocol *aac = selected->listaC->todo->columnas->inicio;
            while(aac != NULL)
            {
                nc = aac->col;
                aac = aac->sig;
            }
            nodolistacapa *auxLC = nlist->inicio;
            matriz *base = selected->listaC->todo;
            while(auxLC != NULL)
            {
                auxLC->capa->filMosaico(nf,nc,base);
                auxLC = auxLC->sig;
            }
            nodoabb *nodoabbcopiadoparalalistadefiltros = new nodoabb("Mosaico_"+selected->nombre,selected->dimH,selected->dimW,selected->pixH,selected->pixW,nlist);
            nodoabbcopiadoparalalistadefiltros->pixH = round(nodoabbcopiadoparalalistadefiltros->pixH/4);
            nodoabbcopiadoparalalistadefiltros->pixW = round(nodoabbcopiadoparalalistadefiltros->pixW/4);
            nodoabbcopiadoparalalistadefiltros->dimW = nodoabbcopiadoparalalistadefiltros->dimW * nodoabbcopiadoparalalistadefiltros->dimW;
            nodoabbcopiadoparalalistadefiltros->dimH = nodoabbcopiadoparalalistadefiltros->dimH * nodoabbcopiadoparalalistadefiltros->dimH;
            //nodoabbcopiadoparalalistadefiltros->generar();
            nuevo->fil = nodoabbcopiadoparalalistadefiltros;
        } else
        {
            cout << "Error con la seleccion de filtro" << endl;
        }
    } while ((op != "1") && (op != "2") && (op != "3") && (op != "4") && (op != "5"));
}

void editing4()
{
    cout << "========== EDICION MANUAL ==========" << endl;
    nodoabb *ed;
    string op = "";
    cout << "1. OG Image" << endl;
    cout << "2. Filters" << endl;
    cin >> op;
    cout << endl;
    string f, c, r, g, b, capa;
    if(op == "1")
    {
        ed = selected;
        cout << "===== ORIGINAL =====" << endl << endl;
        cout << "No. Fila: ";
        cin >> f;
        cout << "No. Columna: ";
        cin >> c;
        cout << "Capa: ";
        cin >> capa;
        cout << "Valor r: ";
        cin >> r;
        cout << "Valor g: ";
        cin >> g;
        cout << "Valor b: ";
        cin >> b;
        //
        nodolistacapa *auxLC = ed->listaC->inicio;
        int si = 0;
        while(auxLC != NULL)
        {
            if(auxLC->nombre == capa)
            {
                cout << auxLC->capa->nombre << endl;
                si = 1;
                nodomatriz *mod = auxLC->capa->buscar(stoi(f),stoi(c));
                if(mod != NULL)
                {
                    mod->r = stoi(r);
                    mod->g = stoi(g);
                    mod->b = stoi(b);
                } else
                {
                    cout << "No existe esa posicion en la capa" << endl;
                }
                break;
            }
            auxLC = auxLC->sig;
        }
        ed->listaC->sobreponer();
        if(si != 1)
        {
            cout << "No existe capa con ese nombre" << endl;
        }
    } else if(op == "2")
    {
        if(filtros->primero != NULL)
        {
            ed = selectFilter();
            if(ed != NULL)
            {
                cout << "===== Filtro: " << ed->nd << " =====" << endl << endl;
                cout << "No. Fila: ";
                cin >> f;
                cout << "No. Columna: ";
                cin >> c;
                cout << "Capa: ";
                cin >> capa;
                cout << "Valor r: ";
                cin >> r;
                cout << "Valor g: ";
                cin >> g;
                cout << "Valor b: ";
                cin >> b;
                //
                nodolistacapa *auxLC = ed->listaC->inicio;
                int si = 0;
                while(auxLC != NULL)
                {
                    if(auxLC->nombre == capa)
                    {
                        cout << auxLC->capa->nombre << endl;
                        si = 1;
                        nodomatriz *mod = auxLC->capa->buscar(stoi(f),stoi(c));
                        if(mod != NULL)
                        {
                            mod->r = stoi(r);
                            mod->g = stoi(g);
                            mod->b = stoi(b);
                        } else
                        {
                            cout << "No existe esa posicion en la capa" << endl;
                        }
                        break;
                    }
                    auxLC = auxLC->sig;
                }
                ed->listaC->sobreponer();
                if(si != 1)
                {
                    cout << "No existe capa con ese nombre" << endl;
                }
            } else
            {
                cout << "Problemas con encontrar el filtro" << endl;
            }
            
        } else
        {
            cout << "No hay filtros disponibles" << endl << endl;
        }
    } else
    {
        cout << "Opcion incorrecta" << endl << endl;
    }
}

void export5()
{
    cout << "========== EXPORTAR ==========" << endl;
    nodoabb *sel;
    nodocircular *aux = filtros->primero;
    string op;
    cout << "1. OG Image" << endl;
    cout << "2. Filters" << endl;
    cin >> op;
    if(op == "1")
    {
        sel = selected;
        sel->generar();
    } else if (op == "2")
    {
        if(filtros->primero != NULL)
        {
            sel = selectFilter();
            if(sel != NULL)
            {
                sel->generar();
            } else
            {
                cout << "Problemas con encontrar el filtro\n" << endl;
            }
        } else
        {
            cout << "No hay filtros disponibles\n" << endl;
        }
    } else
    {
        cout << "Opcion incorrecta\n" << endl;
    }
}

void reports6()
{
    string op = "";
    do
    {
        cout << "========== REPORTES ==========" << endl;
        cout << "1. Imported Images Report" << endl;
        cout << "2. Image Layer Report" << endl;
        cout << "3. Linear Matrix Report" << endl;
        cout << "4. Traversal Report" << endl;
        cout << "5. Filters Report" << endl;
        cout << "6. Return" << endl;
        cin >> op;
        cout << endl;
        if(op == "1")
        {
            arbolBin->graficar();
        } else if (op == "2")
        {
            if(arbolBin->raiz != NULL)
            {
                nodoabb *im = selectIm();
                if(im != NULL)
                {
                    string op01 = "";
                    cout << "1. Grafica Individual" << endl;
                    cout << "2. Graficar Todas las Capas" << endl;
                    cin >> op01;
                    cout << endl;
                    if(op01 == "1")
                    {
                        matriz *capa;
                        nodolistacapa *auxLC = im->listaC->inicio;
                        string op2 = "";
                        int si2 = 0;
                        do
                        {
                            auxLC = im->listaC->inicio;
                            cout << "==== Capas ====" << endl;
                            while(auxLC != NULL)
                            {
                                cout << auxLC->id << ". " << auxLC->nombre << endl;
                                auxLC = auxLC->sig;
                            }
                            cout << "Ingresa el numero de capa a graficar: ";
                            cin >> op2;
                            cout << endl;
                            auxLC = im->listaC->inicio;
                            while(auxLC != NULL)
                            {
                                if(to_string(auxLC->id) == op2)
                                {
                                    capa = auxLC->capa;
                                    si2 = 1;
                                    break;
                                }
                                auxLC = auxLC->sig;
                            }
                            if(si2 == 0)
                            {
                                cout << "El numero de capa ingresado es in correcto, vuelve a probar" << endl;
                            }
                        } while (si2 != 1);
                        capa->graficar(capa->capa,capa->nombre);
                    } else if(op01 == "2")
                    {
                        im->listaC->graficar_capas();
                    } else
                    {
                        cout << "Opcion Invalida" << endl;
                    }
                } else
                {
                    cout << "Error al seleccionar la imagen" << endl;
                }
            } else
            {
                cout << "No hay imagenes, para graficar alguna capa" << endl;
            }
            
        } else if (op == "3")
        {
            if(arbolBin->raiz != NULL)
            {
                nodoabb *im = selectIm();
                if(im != NULL)
                {
                    matriz *capa;
                    nodolistacapa *auxLC = im->listaC->inicio;
                    string op2 = "";
                    int si2 = 0;
                    do
                    {
                        auxLC = im->listaC->inicio;
                        cout << "==== Capas ====" << endl;
                        while(auxLC != NULL)
                        {
                            cout << auxLC->id << ". " << auxLC->nombre << endl;
                            auxLC = auxLC->sig;
                        }
                        cout << "Ingresa el numero de capa a linealizar: ";
                        cin >> op2;
                        cout << endl;
                        auxLC = im->listaC->inicio;
                        while(auxLC != NULL)
                        {
                            if(to_string(auxLC->id) == op2)
                            {
                                capa = auxLC->capa;
                                si2 = 1;
                                break;
                            }
                            auxLC = auxLC->sig;
                        }
                        if(si2 == 0)
                        {
                            cout << "El numero de capa ingresado es in correcto, vuelve a probar" << endl;
                        }
                    } while (si2 != 1);

                    int si3 = 0;
                    while (si3 != 1)
                    {
                        cout << "=== Tipo ===" << endl;
                        string op3 = "";
                        cout << "1. Linealizacion por Filas" << endl;
                        cout << "2. Linealizacion por Columnas" << endl;
                        cin >> op3;
                        cout << endl;
                        if(op3 == "1")
                        {
                            capa->xFilas();
                            si3 = 1;
                        } else if(op3 == "2")
                        {
                            capa->xColumnas();
                            si3 = 1;
                        } else
                        {
                            cout << "Opcion Invalida\n" << endl;
                        }
                    }
                } else
                {
                    cout << "Error al seleccionar la imagen" << endl;
                }
            } else
            {
                cout << "No hay imagenes, para graficar alguna capa" << endl;
            }
        } else if (op == "4")
        {
            string op2 = "";
            cout << "1. INORDER Traversal" << endl;
            cout << "2. POSTORDER Traversal" << endl;
            cout << "3. PREORDER Traversal" << endl;
            cin >> op2;
            if(op2 == "1")
            {
                arbolBin->grafIN();
            } else if(op2 == "2")
            {
                arbolBin->grafPOST();
            } else if(op2 == "3")
            {
                arbolBin->grafPRE();
            } else
            {
                cout << "Opcion incorrecta" << endl;
            }
        } else if (op == "5")
        {
            string op2 = "";
            nodoabb *sel;
            if(filtros->primero != NULL)
            {
                sel = selectFilterNo();
                if(sel != NULL)
                {
                    string op01 = "";
                    cout << "1. Grafica Individual" << endl;
                    cout << "2. Graficar Todas las Capas" << endl;
                    cin >> op01;
                    cout << endl;
                    if(op01 == "1")
                    {
                        nodolistacapa * auxLC = sel->listaC->inicio;
                        cout << "==== Capas ====" << endl;
                        while(auxLC != NULL)
                        {
                            cout << auxLC->id << ". " << auxLC->nombre << endl;
                            auxLC = auxLC->sig;
                        }
                        cin >> op2;
                        cout << endl;

                        auxLC = sel->listaC->inicio;
                        int si = 0;
                        while(auxLC != NULL)
                        {
                            if(to_string(auxLC->id) == op2)
                            {
                                auxLC->capa->graficar(auxLC->id,auxLC->nombre);
                                si = 1;
                                break;
                            }
                            auxLC = auxLC->sig;
                        }
                        if(si != 1)
                        {
                            cout << "No existe capa con ese nombre" << endl;
                        }
                    } else if(op01 == "2")
                    {
                        sel->listaC->graficar_capas();
                    } else
                    {
                        cout << "Opcion Invalida" << endl;
                    }
                } else
                {
                    cout << "Problemas con encontrar el filtro\n" << endl;
                }
            } else
            {
                cout << "No hay filtros disponibles\n" << endl;
            }
        } else if (op == "6")
        {
            //
        } else
        {
            cout << "\nOpcion incorrecta" << endl;
        }
        cout << endl;
    } while (op != "6");
}

int select()
{
    string op = "";
    int select = -1;
    do
    {
        cout << "========== APLICACION ==========" << endl;
        cout << "1. Imagen completa" << endl;
        cout << "2. Capa Espcifica" << endl;
        cin >> op;
        cout << endl;
        if (op == "1")
        {
            select = 1;
            break;
        }
        else if (op == "2")
        {
            select = 2;
            break;
        }
        else
        {
            cout << "Opcion incorrecta" << endl;
        }
        
    } while ((op!="1") || (op!="2"));
    return select;   
}

nodoabb* selectIm()
{
    cout << "\n====== Imagen =====" << endl;
    nodoabb *ret = NULL; 
    arbolBin->trasversalIN = new abblineal();
    arbolBin->recorridoIN(arbolBin->raiz);
    nodoabblineal *aux = arbolBin->trasversalIN->primero;
    while(aux != NULL)
    {
        cout << aux->pos << ". " << aux->nombre << endl;
        aux = aux->sig;
    }
    string op = "";
    string name = "";
    int si = 0;
    do
    {
        cout << "Elige un numero de imagen: ";
        cin >> op;
        aux = arbolBin->trasversalIN->primero;
        while(aux != NULL)
        {
            if(op == to_string(aux->pos))
            {
                name = aux->nombre;
                si = 1;
                ret = arbolBin->buscar(arbolBin->raiz,name);
                break;
            }
            aux = aux->sig;
        }
        if(si == 0)
        {
            cout << "Opcion incorrecta\n" << endl;
        }
    } while (si != 1);
    //selected = arbolBin->buscar(arbolBin->raiz,name);
    //cout << "Imagen seleccionada: " << name << endl;
    cout << endl;
    return ret;
}

nodoabb* selectFilter()
{
    nodoabb *ret = NULL;
    cout << "========== FILTROS ==========" << endl;
    string op = "";
    nodocircular *aux = filtros->primero;
    do
    {
        cout << aux->id << ". " << aux->fil->nombre << endl;
        aux = aux->sig;
    }while(aux != filtros->primero);
    cout << endl;
    cout << "Elige un numero de imagen: ";
    cin >> op;
    nodocircular *aux2 = filtros->primero;
    int si = 0;
    do
    {
        if(op == to_string(aux2->id))
        {
            ret = aux2->fil;
            si = 1;
            return ret;
            break;
        }
        aux2 = aux2->sig;
    }while(aux2 != filtros->primero);
    if (si == 0)
    {
        cout << "Error al seleccionar la imagen\n" << endl;
    }
    return ret;
}

nodoabb* selectFilterNo()
{
    nodoabb *ret = NULL;
    cout << "===== FILTROS =====" << endl;
    string op = "";
    nodocircular *aux = filtros->primero;
    do
    {
        if((aux->filtro != "Collage") && (aux->filtro != "Mosaico"))
        {
            cout << aux->id << ". " << aux->fil->nombre << endl;
        }
        aux = aux->sig;
    }while(aux != filtros->primero);
    cout << endl;
    cout << "Elige un numero de imagen: ";
    cin >> op;
    nodocircular *aux2 = filtros->primero;
    int si = 0;
    do
    {
        if(op == to_string(aux2->id) && (aux2->filtro != "Collage") && (aux2->filtro != "Mosaico"))
        {
            ret = aux2->fil;
            si = 1;
            return ret;
            break;
        }
        aux2 = aux2->sig;
    }while(aux2 != filtros->primero);
    if (si == 0)
    {
        cout << "Numero incorrecto\n" << endl;
    }
    return ret;
}