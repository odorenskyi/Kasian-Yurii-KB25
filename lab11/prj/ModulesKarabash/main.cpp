#include <iostream>
#include <fstream>
#include <string>
#include "struct_type_project_1.h"

// Функція зчитує дані з txt файлу та будує динамічний список
// Повертає вказівник на початок (голову) списку
Reestr* loadFromTxtFile(string fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Помилка: файл не знайдено!" << endl;
        return nullptr;
    }

    Reestr* head = nullptr;
    Reestr* tail = nullptr;

    string l_name;
    // Зчитуємо перше поле, щоб перевірити чи файл не порожній
    while (file >> l_name) {
        // Створюємо новий елемент у динамічній пам'яті
        Reestr* newNode = new Reestr;

        // Заповнюємо дані
        newNode->l_name = l_name;
        file >> newNode->f_name;
        file >> newNode->s_name;
        file >> newNode->marka;
        file >> newNode->year;
        file >> newNode->data;
        file >> newNode->nomer;

        // Для приміток використовуємо getline, бо там можуть бути пробіли
        file.ignore(); // Очищуємо буфер після зчитування номера
        getline(file, newNode->prumitku);

        newNode->next = nullptr;

        // Додаємо елемент у список
        if (head == nullptr) {
            head = newNode; // Перший елемент стає головою
            tail = newNode;
        } else {
            tail->next = newNode; // Приєднуємо до кінця
            tail = newNode;
        }
    }

    file.close();
    return head;
}

// Функція для виведення/запису всього реєстру
void outputRegistry(Reestr* head) {
    // 1) Початок
    int choice;
    bool valid = false;

    if (head == nullptr) {
        cout << "Реєстр порожній!" << endl;
        return;
    }

    do {
        // 2) Виведення повідомлення про вибір
        cout << "\nОберіть дію: \n1 - Виведення інформації на екран; \n2 - Запис інформації у заданий текстовий файл. \nВаш вибір: ";

        // 3) Зчитування вибору
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Помилка введення! Введіть число." << endl;
            continue;
        }

        // 4) Якщо вибір 1 - виведення на екран
        if (choice == 1) {
            Reestr* current = head;
            cout << "\n--- Вміст реєстру ---" << endl;
            while (current != nullptr) {
                cout << current->l_name << " " << current->f_name << " " << current->s_name << " "
                     << current->marka << " " << current->year << " " << current->data << " "
                     << current->nomer << " " << current->prumitku << endl;
                current = current->next;
            }
            valid = true;
        }
        // 5) Якщо вибір 2 - запис у файл
        else if (choice == 2) {
            string fileName;
            cout << "Введіть ім'я або шлях до файлу (.txt): ";
            cin >> fileName;

            ofstream outFile(fileName);
            if (outFile.is_open()) {
                Reestr* current = head;
                while (current != nullptr) {
                    outFile << current->l_name << " " << current->f_name << " "
                            << current->s_name << " " << current->marka << " "
                            << current->year << " " << current->data << " "
                            << current->nomer << " " << current->prumitku << endl;
                    current = current->next;
                }
                outFile.close();
                cout << "Дані успішно записані у файл: " << fileName << endl;
                valid = true;
            } else {
                cout << "Помилка створення файлу!" << endl;
            }
        }
        // 6) Інакше - повідомлення про помилку та повтор
        else {
            cout << "Невірний вибір! Спробуйте ще раз (1 або 2)." << endl;
        }
    } while (!valid);

    // 7) Кінець
}

