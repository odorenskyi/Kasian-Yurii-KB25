#include <iostream>
#include <conio.h>
#include <windows.h>
#include <clocale>
#include "ModuleKasian.h"
using namespace std;

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL, ".UTF-8");
    char ch;

    while (true) {
        cout << "\n--- Головне меню ---" << endl;
        cout << "v - Виконати s_calculation" << endl;
        cout << "n - Задача 9.1 (Зарплата)" << endl;
        cout << "m - Задача 9.2 (Шкарпетки)" << endl;
        cout << "q - Задача 9.3 (Біти)" << endl;
        cout << "w, W - Вихід" << endl;
        cout << "Оберіть дію(вводити таким самим чином, як написано вище!): ";
        cin >> ch;

        if (ch == 'w' || ch == 'W') {
            cout << "Завершення роботи..." << endl;
            break;
        }
        switch (ch) {
            case 'v':
                double x, y, z;
                cout << "Введіть x" << endl;
                cin >> x;
                cout << "Введіть y" << endl;
                cin >> y;
                cout << "Введіть z" << endl;
                cin >> z;
                s_calculation(x, y, z);
                break;
            case 'n':
                task9_1();
                break;
            case 'm':
                task9_2();
                break;
            case 'q':
                task9_3();
                break;
            default:
                cout << "\a" << endl;
                break;
        }
    }
    return 0;
}
