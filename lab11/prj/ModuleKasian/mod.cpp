#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "struct_type_project_1.h"

using namespace std;

// Припускаємо, що в struct_type_project_1.h структура має вигляд:
/*
struct Reestr {
    string l_name, f_name, s_name, marka, data, nomer, prumitku;
    int year;
    Reestr* next; // Обов'язково для списку
};
*/

// Прототипи згідно з вашим запитом
Reestr* loadFromTxtFile(string fileName);
void outputRegistry(Reestr* head);

// Допоміжні функції валідації
bool isValidCarNumber(string n) {
    if (n.length() != 8) return false;
    if (!isalpha(n[0]) || !isalpha(n[1])) return false;
    if (!isdigit(n[2]) || !isdigit(n[3]) || !isdigit(n[4]) || !isdigit(n[5])) return false;
    if (!isalpha(n[6]) || !isalpha(n[7])) return false;
    return true;
}

bool isValidDate(string dateStr) {
    if (dateStr.length() != 10) return false;
    int day, month, year;
    char dot1, dot2;
    stringstream ss(dateStr);
    if (!(ss >> day >> dot1 >> month >> dot2 >> year)) return false;
    if (dot1 != '.' || dot2 != '.') return false;
    if (month < 1 || month > 12) return false;
    if (year < 1886 || year > 2026) return false;
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) daysInMonth[1] = 29;
    return (day >= 1 && day <= daysInMonth[month - 1]);
}

// Переписана функція додавання для списку
void Dodavannya(Reestr*& head) {
    cout << "\n--- Реєстрація нового транспортного засобу ---" << endl;

    Reestr* newNode = new Reestr;
    newNode->next = nullptr;

    cout << "Прізвище власника*: "; cin >> newNode->l_name;
    cout << "Ім'я*: "; cin >> newNode->f_name;
    cout << "По батькові(-): "; cin >> newNode->s_name;

    cout << "Марка автомобіля*: ";
    cin.ignore();
    getline(cin, newNode->marka);

    cout << "Рік випуску (1886-2026): ";
    while (!(cin >> newNode->year) || newNode->year < 1886 || newNode->year > 2026) {
        cout << "Помилка! Введіть коректний рік: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    while (true) {
        cout << "Дата реєстрації (дд.мм.рррр)*: ";
        cin >> newNode->data;
        if (isValidDate(newNode->data)) break;
        cout << "ПОМИЛКА: Некоректний формат!" << endl;
    }

    while (true) {
        cout << "Введіть державний номер (AA1111BB)*: ";
        cin >> newNode->nomer;
        transform(newNode->nomer.begin(), newNode->nomer.end(), newNode->nomer.begin(), ::toupper);

        if (!isValidCarNumber(newNode->nomer)) {
            cout << "ПОМИЛКА: Невірний формат номера!" << endl;
            continue;
        }

        // Перевірка унікальності у списку
        bool isDuplicate = false;
        Reestr* temp = head;
        while (temp != nullptr) {
            if (temp->nomer == newNode->nomer) {
                isDuplicate = true;
                break;
            }
            temp = temp->next;
        }

        if (isDuplicate) {
            cout << "ПОМИЛКА: Номер вже існує!" << endl;
        } else break;
    }

    cout << "Примітки: ";
    cin.ignore();
    getline(cin, newNode->prumitku);

    // Додавання в кінець списку (або в початок для простоти)
    newNode->next = head;
    head = newNode;

    cout << "\nРЕЗУЛЬТАТ: Запис додано успішно." << endl;
}

// Переписана функція пошуку для списку
void searchnom(Reestr* head) {
    cout << "\n--- Пошук у реєстрі МВС ---" << endl;

    if (head == nullptr) {
        cout << "Реєстр порожній." << endl;
        return;
    }

    string searchKey;
    cout << "Введіть номер для пошуку: ";
    cin >> searchKey;
    transform(searchKey.begin(), searchKey.end(), searchKey.begin(), ::toupper);

    Reestr* current = head;
    bool found = false;

    while (current != nullptr) {
        if (current->nomer == searchKey) {
            found = true;
            cout << "\nЗНАЙДЕНО!" << endl;
            cout << "Власник: " << current->l_name << " " << current->f_name << endl;
            cout << "Авто: " << current->marka << " (" << current->year << ")" << endl;
            cout << "Номер: " << current->nomer << endl;
            break;
        }
        current = current->next;
    }

    if (!found) cout << "Запис не знайдено." << endl;
}
