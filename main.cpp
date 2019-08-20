#include <iostream>
#include <string>

#include "Clases/abb.cpp"
#include "Clases/matriz.cpp"
#include "Clases/listacapas.cpp"

using namespace std;

void menu();

int main()
{
    //cout << "Proyecto No. 1 - 201603168\n" << endl;
    //abb *aABB = new abb();
    //aABB->graficar();
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
    //menu();
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
            //metodo1
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
