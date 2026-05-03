#ifndef MODULE_SOKOLOV_H_INCLUDED
#define MODULE_SOKOLOV_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include "struct_type_project_1.h"

using namespace std;

Reestr* deleteRecord(Reestr* head, const string& target_nomer) {
    if (head == nullptr) {
        cout << "Реєстр порожній. Вилучати нічого.\n";
        return nullptr;
    }

    if (head->nomer == target_nomer) {
        Reestr* temp = head;
        head = head->next;
        delete temp;
        cout << "Запис із номером " << target_nomer << " успішно вилучено.\n";
        return head;
    }

    Reestr* current = head;
    while (current->next != nullptr && current->next->nomer != target_nomer) {
        current = current->next;
    }

    if (current->next != nullptr) {
        Reestr* temp = current->next;
        current->next = current->next->next;
        delete temp;
        cout << "Запис із номером " << target_nomer << " успішно вилучено.\n";
    } else {
        cout << "Автомобіль з номером " << target_nomer << " не знайдено в реєстрі.\n";
    }

    return head;
}

void exitAndSaveRegistry(Reestr* head, const string& filename) {
    ofstream outFile(filename);

    if (!outFile.is_open()) {
        cout << "Помилка! Не вдалося створити або відкрити файл для збереження.\n";
        return;
    }

    Reestr* current = head;
    while (current != nullptr) {
        outFile << current->l_name << "\n" << current->f_name << "\n"
                << current->s_name << "\n" << current->marka << "\n"
                << current->year << "\n" << current->data << "\n"
                << current->nomer << "\n" << current->prumitku << "\n";
        current = current->next;
    }

    outFile.close();
    cout << "Дані реєстру успішно збережено у файл: " << filename << "\n";
}

#endif // MODULE_SOKOLOV_H_INCLUDED
