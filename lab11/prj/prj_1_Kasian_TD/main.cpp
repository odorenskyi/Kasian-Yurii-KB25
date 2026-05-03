#include <iostream>
#include <string>
#include <windows.h>
#include <ModuleKasian.h>
#include <struct_type_project_1.h>
#include <ModulesKarabash/ModulesKarabash.h>

using namespace std;

// Ваші правильні прототипи (використовують логіку списку)
void Dodavannya(Reestr*& head);
void searchnom(Reestr* head);
Reestr* loadFromTxtFile(string fileName);
void outputRegistry(Reestr* head);

int main()
{
    // Налаштування кодування для коректного відображення кирилиці
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    // Для списку нам потрібен лише вказівник на "голову"
    // Ініціалізуємо його результатом завантаження з файлу
    Reestr* database = loadFromTxtFile("database.txt");

    int choice;
    bool running = true;

    cout << "=== ТЕСТОВИЙ ДРАЙВЕР: РЕЄСТР АВТОМОБІЛІВ МВС (СПИСОК) ===" << endl;

    while (running) {
        cout << "\nМЕНЮ УПРАВЛІННЯ:" << endl;
        cout << "1. Додати новий автомобіль" << endl;
        cout << "2. Пошук за держ. номером" << endl;
        cout << "3. Переглянути весь реєстр" << endl;
        cout << "0. Вихід" << endl;
        cout << "Ваш вибір: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        switch (choice) {
            case 1:
                // Передаємо тільки вказівник на голову (за посиланням)
                Dodavannya(database);
                break;
            case 2:
                // Пошук по списку починаючи з голови
                searchnom(database);
                break;
            case 3:
                // Вивід усіх елементів списку
                outputRegistry(database);
                break;
            case 0:
                running = false;
                break;
            default:
                cout << "Невірний пункт меню!" << endl;
        }
    }

    // Тут варто було б додати функцію очищення пам'яті списку,
    // але згідно з вашими прототипами, робота завершена.
    cout << "Програма завершена." << endl;

    return 0;
}
