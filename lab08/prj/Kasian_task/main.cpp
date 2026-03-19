#include <iostream>
#include <windows.h>
#include <clocale>
#include <iomanip>
#include "ModuleKasian.h"

using namespace std;

int main()
{
    SetConsoleOutputCP(65001);
    cout << "\xC2\xA9 Касян Юрій" << endl;
    double x, y, z;
    cout << "Введіть число x" << endl;
    cin >> x;
    cout << "Введіть число y" << endl;
    cin >> y;
    cout << "Введіть число z" << endl;
    cin >> z;
    char a, b;
    cout << "Введіть символ a" << endl;
    cin >> a;
    cout << "Введіть символ b" << endl;
    cin >> b;

    cout<<"Чи a+7=b?"<<endl;
    if (a+7==b){
        cout<<"true";
    }
    else
        cout <<"false";
    cout << "\nЗначення у різних системах числення" << endl;

    cout << "x: " << dec << x << " Десяткова|"
         << hex << showbase << (int)x << " Шістнадцяткова" << endl;

    cout << "y: " << dec << y << " Десяткова|"
         << hex << (int)y << " Шістнадцяткова" << endl;

    cout << "z: " << dec << z << " Десяткова|"
         << hex << (int)z << " Шістнадцяткова" << endl;

    cout<<"вивід S на основі перших трьох значень"<<endl;
    s_calculation(x, y, z);

    return 0;
}
