#include <iostream>
#include <string>
#include <windows.h>
# include "struct_type_project_1.h"
# include "module_Sokolov.h"
# include "ModuleKasian.h"
# include "ModulesKarabash.h"

using namespace std;

void Dodavannya(Reestr*& head);
void searchnom(Reestr* head);

int main() {
    // Налаштування кирилиці для консолі
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Ініціалізація реєстру
    Reestr* registryHead = nullptr;
    string filename = "Reestr.txt";

    // Автоматичне завантаження реєстру при запуску (модуль Karabash)
    registryHead = loadFromTxtFile(filename);

    int choice;
    do {
        cout << "\n--- Електронний реєстр автомобілів МВС ---" << endl;
        cout << "1. Вивести весь реєстр на екран або записати у вказаний файл" << endl;
        cout << "2. Додати новий запис" << endl;
        cout << "3. Пошук запису за державним номером" << endl;
        cout << "4. Вилучити запис за номером" << endl;
        cout << "5. Завершити роботу та зберегти дані" << endl;
        cout << "Ваш вибір: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                // Функція виведення з модуля Karabash
                outputRegistry(registryHead);
                break;

            case 2:
                // Функція додавання з модуля Kasian (змінює голову списку)
                Dodavannya(registryHead);
                break;

            case 3:
                // Функція пошуку з модуля Kasian
                searchnom(registryHead);
                break;

            case 4: {
                // Функція видалення з модуля Sokolov
                string target;
                cout << "Введіть державний номер для вилучення: ";
                getline(cin, target);
                registryHead = deleteRecord(registryHead, target);
                break;
            }

            case 5:
                // Збереження у файл перед виходом (модуль Sokolov)
                exitAndSaveRegistry(registryHead, filename);
                cout << "Дані успішно збережено. Програма завершена." << endl;
                break;

            default:
                cout << "Помилка! Оберіть пункт від 1 до 5." << endl;
                break;
        }
    } while (choice != 5);

    // Звільнення динамічної пам'яті
    while (registryHead != nullptr) {
        Reestr* temp = registryHead;
        registryHead = registryHead->next;
        delete temp;
    }

    return 0;
}
