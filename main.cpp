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

static abb *arbolBin = new abb();

int main()
{
    //cout << "Proyecto No. 1 - 201603168\n" << endl;
    //abb *aABB = new abb();
    //aABB->graficar();
    /*
    matriz *matrix = new matriz(1,"Uno1");
    matrix->insertar(2,3);
    matrix->insertar(2,1);
    matrix->insertar(5,6);

    matriz *matrix2 = new matriz(2,"Dos2");
    matrix2->insertar(1,2);
    matrix2->insertar(3,1);
    matrix2->insertar(4,4);
    matrix2->insertar(2,1);

    listacapas *lista1 = new listacapas("Mario");
    lista1->insertar(new nodolistacapa(matrix2->capa,matrix2->nombre,matrix2));
    lista1->insertar(new nodolistacapa(matrix->capa,matrix->nombre,matrix));
    //lista1->graficar_capas();
    //lista1->sobreponer();
    //lista1->todo->graficar(lista1->todo->capa);
    lista1->linealizar();
    //lista1->todo->graficar(-1);
    lista1->linealizada->graficar();
    */
    //menu();
    insert1();
    //arbolBin->raiz->listaC->graficar_capas();
    //arbolBin->raiz->listaC->sobreponer();
    arbolBin->raiz->listaC->linealizar();
    arbolBin->raiz->listaC->todo->graficar(arbolBin->raiz->listaC->todo->capa);
    arbolBin->raiz->listaC->linealizada->graficar();
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
            //metodo1
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
    string init = "R/R.csv";
    //cout << "Ingresa la direccion de tu archivo inicial" << endl;
    //cin >> init;

    ifstream archivo;
    archivo.open("R/R.csv",ios::in);
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
        cout << "Imagen ingresada" << endl;
    } else
    {
        cout << "No se pudo abrir el archivo" << endl;
    }
    archivo.close();
}