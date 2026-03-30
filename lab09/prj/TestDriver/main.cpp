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
    task9_1();
    task9_2();
    task9_3();
    return 0;
}
