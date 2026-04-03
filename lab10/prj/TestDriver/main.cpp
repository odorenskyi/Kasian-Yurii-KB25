#include <iostream>
#include <string>
#include <windows.h>
#include <clocale>
#include "ModuleKasian.h"

using namespace std;

int main() {

    SetConsoleOutputCP(65001);
    int choice;
    string file1, file2;
    double x, y, z;
    int b;

    while (true) {
        cout << "\n--- ТЕСТОВИЙ ДРАЙВЕР (Касян Юрій) ---" << endl;
        cout << "1. Виконати Task 10.1 (Аналіз тексту та запис звіту)" << endl;
        cout << "2. Виконати Task 10.2 (Підрахунок пунктуації у файлі)" << endl;
        cout << "3. Виконати Task 10.3 (Математика + Двійкова система)" << endl;
        cout << "0. Вихід" << endl;
        cout << "Ваш вибір: ";
        cin >> choice;

        if (choice == 0) break;

        switch (choice) {
            case 1:
                cout << "Введіть назву вхідного файлу (наприклад, input.txt): ";
                cin >> file1;
                cout << "Введіть назву файлу для звіту (наприклад, report.txt): ";
                cin >> file2;
                Task10_1(file1, file2);
                cout << "Завдання 10.1 виконано!" << endl;
                break;

            case 2:
                cout << "Введіть назву файлу для аналізу пунктуації: ";
                cin >> file1;
                Task10_2(file1);
                cout << "Завдання 10.2 виконано!" << endl;
                break;

            case 3:
                cout << "Введіть назву файлу для дозапису результатів: ";
                cin >> file1;
                cout << "Введіть x, y, z (через пробіл): ";
                cin >> x >> y >> z;
                cout << "Введіть натуральне число b: ";
                cin >> b;
                Task10_3(file1, x, y, z, b);
                cout << "Завдання 10.3 виконано!" << endl;
                break;

            default:
                cout << "Невірний вибір, спробуйте ще раз." << endl;
        }
    }

    return 0;
}
