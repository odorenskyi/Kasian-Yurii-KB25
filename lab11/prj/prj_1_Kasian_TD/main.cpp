#include <iostream>
#include <string>
#include <windows.h>
#include <ModuleKasian.h>

using namespace std;

struct Reestr {
    string l_name;
    string f_name;
    string s_name;
    string marka;
    int year;
    string data;
    string nomer;
    string prumitku;
};
void Dodavannya(Reestr*& db, int& count, int& capacity);
void searchnom(Reestr* db, int count);
void loadDatabaseFromFile(Reestr*& db, int& count, int& capacity, string filename);
void saveDatabaseToFile(Reestr* db, int count, string filename);

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    int count = 0;      // Поточна кількість записів
    int capacity = 2;   // Початкова місткість (мала для перевірки Reallocation)
    Reestr* database = new Reestr[capacity];

    loadDatabaseFromFile(database, count, capacity, "Reestr.txt");

    int choice;
    bool running = true;

    cout << "=== ТЕСТОВИЙ ДРАЙВЕР: РЕЄСТР АВТОМОБІЛІВ МВС ===" << endl;

    while (running) {
        cout << "\nМЕНЮ УПРАВЛІННЯ:" << endl;
        cout << "1. Додати новий автомобіль (Тест TC-ADD)" << endl;
        cout << "2. Пошук за держ. номером (Тест TC-SRCH)" << endl;
        cout << "3. Переглянути статус пам'яті" << endl;
        cout << "0. Вихід" << endl;
        cout << "Ваш вибір: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        switch (choice) {
            case 1:
                Dodavannya(database, count, capacity);
                break;
            case 2:
                searchnom(database, count);
                break;
            case 3:
                cout << "--- Стан системи ---" << endl;
                cout << "Записів у базі: " << count << endl;
                cout << "Виділено пам'яті: " << capacity << " об'єктів" << endl;
                break;
            case 0:
                running = false;
                break;
            default:
                cout << "Невірний пункт меню!" << endl;
        }
    }

    saveDatabaseToFile(database, count, "Reestr.txt");
    // Звільнення пам'яті перед виходом
    delete[] database;
    cout << "Програма завершена. Пам'ять звільнена." << endl;

    return 0;
}
