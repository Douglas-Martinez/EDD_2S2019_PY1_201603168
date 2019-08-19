#include <iostream>
#include <string>

#include "Clases/abb.cpp"
#include "Clases/matriz.cpp"

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
    matrix->graficar();
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
