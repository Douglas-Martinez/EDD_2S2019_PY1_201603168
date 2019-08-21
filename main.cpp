#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Clases/abb.cpp"
#include "Clases/matriz.cpp"
#include "Clases/listacapas.cpp"

using namespace std;

void menu();
void insert1();
void select2();

static abb *arbolBin = new abb();
static nodoabb *selected;

int main()
{
    cout << "Proyecto No. 1 - 201603168\n" << endl;

    //menu();
    insert1();
    insert1();
    insert1();
    select2();
    selected->generar();
    
    return 0;
}

/*
Mario/Mario_Bros.csv
R/R.csv
Mario/Luigi_Rojo.csv
*/

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
            select2();
        } else if(op.compare("3") == 0)
        {
            //metodo1
        } else if(op.compare("4") == 0)
        {
            //metodo1
        } else if(op.compare("5") == 0)
        {
            //metodo1
        } else if(op.compare("6") == 0)
        {
            //metodo1
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
    string init = "";
    cout << "Ingresa la direccion de tu archivo inicial" << endl;
    cin >> init;

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
                            if((c != "x") && (c != "X"))
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
        cout << "Imagen ingresada\n" << endl;
        archivo.close();
    } else
    {
        cout << "No se pudo abrir el archivo" << endl;
    }
}

void select2()
{
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
        cout << "Elige un numero de imagen ";
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
}