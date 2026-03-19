#include <iostream>
#include <windows.h>
#include <clocale>
#include "ModuleKasian.h"
using namespace std;

int main()
{
    SetConsoleCP(65001);        // Ввід UTF-8
    SetConsoleOutputCP(65001);  // Вивід UTF-8
    setlocale(LC_ALL, ".UTF-8"); // Системна локаль
    double x, y, z;
    cout << "Введіть x" << endl;
    cin >> x;
    cout << "Введіть y" << endl;
    cin >> y;
    cout << "Введіть z" << endl;
    cin >> z;

    s_calculation(x, y, z);
    return 0;
}
