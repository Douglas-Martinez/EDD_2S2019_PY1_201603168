#include <iostream>
#include <string>

#include "abb.cpp"

using namespace std;

void menu();

int main()
{
    string lol = "";
    cout << "Proyecto No. 1 - 201603168" << endl;
    cout << endl;

    //abb* arbolb = new abb();
    //arbolb->graficar();
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
