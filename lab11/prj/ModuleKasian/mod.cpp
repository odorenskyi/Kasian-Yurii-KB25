#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm> // Для трансформації регістру
using namespace std;

// Структура даних
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

bool isValidCarNumber(string n) {
    // Стандартний номер має бути рівно 8 символів (напр. AA1111BB)
    if (n.length() != 8) return false;

    // Перевіряємо перші дві літери (регіон)
    if (!isalpha(n[0]) || !isalpha(n[1])) return false;

    // Перевіряємо 4 цифри посередині
    if (!isdigit(n[2]) || !isdigit(n[3]) || !isdigit(n[4]) || !isdigit(n[5])) return false;

    // Перевіряємо останні дві літери (серія)
    if (!isalpha(n[6]) || !isalpha(n[7])) return false;

    return true;
}
/**
 * Зберігає весь масив структур у текстовий файл
 */
void saveDatabaseToFile(Reestr* db, int count, string filename = "Reestr.txt") {
    ofstream outFile(filename);
    if (!outFile) {
        cout << "Помилка: Не вдалося створити файл для збереження!" << endl;
        return;
    }

    for (int i = 0; i < count; i++) {
        // Записуємо поля через розділювач '|'
        outFile << db[i].l_name << "|" << db[i].f_name << "|" << db[i].s_name << "|"
                << db[i].marka << "|" << db[i].year << "|" << db[i].data << "|"
                << db[i].nomer << "|" << db[i].prumitku << endl;
    }

    outFile.close();
    cout << "[Система] Дані успішно синхронізовано з файлом " << filename << endl;
}

/**
 * Завантажує дані з файлу в динамічний масив при старті програми
 */
void loadDatabaseFromFile(Reestr*& db, int& count, int& capacity, string filename = "Reestr.txt") {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "[Система] Файл бази не знайдено. Буде створено нову базу." << endl;
        return;
    }

    string line;
    while (getline(inFile, line)) {
        // Перевірка на потребу розширення масиву (ваша логіка Reallocation)
        if (count >= capacity) {
            int new_capacity = (capacity == 0) ? 2 : capacity * 2;
            Reestr* new_db = new Reestr[new_capacity];
            for (int i = 0; i < count; i++) new_db[i] = db[i];
            delete[] db;
            db = new_db;
            capacity = new_capacity;
        }

        stringstream ss(line);
        string tempYear;

        // Зчитуємо кожне поле до розділювача '|'
        getline(ss, db[count].l_name, '|');
        getline(ss, db[count].f_name, '|');
        getline(ss, db[count].s_name, '|');
        getline(ss, db[count].marka, '|');
        getline(ss, tempYear, '|');
        if(!tempYear.empty()) db[count].year = stoi(tempYear);
        getline(ss, db[count].data, '|');
        getline(ss, db[count].nomer, '|');
        getline(ss, db[count].prumitku); // останнє поле до кінця рядка

        count++;
    }
    inFile.close();
    cout << "[Система] Завантажено " << count << " записів з файлу." << endl;
}

bool isValidDate(string dateStr) {
    if (dateStr.length() != 10) return false; // Перевірка довжини рядка

    int day, month, year;
    char dot1, dot2;
    stringstream ss(dateStr);

    // Очікуємо формат: число.число.число
    if (!(ss >> day >> dot1 >> month >> dot2 >> year)) return false;
    if (dot1 != '.' || dot2 != '.') return false;

    // Валідація місяця
    if (month < 1 || month > 12) return false;

    // Валідація року (згідно з вашими вимогами 1886-2026)
    if (year < 1886 || year > 2026) return false;

    // Валідація днів у місяці
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // Перевірка на високосний рік для лютого
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        daysInMonth[1] = 29;

    if (day < 1 || day > daysInMonth[month - 1]) return false;

    return true;
}

/**
 * Функція додавання запису до реєстру
 * db - вказівник на динамічний масив структур (передається за посиланням)
 * count - поточна кількість записів
 * capacity - поточна виділена місткість масиву
 */
void Dodavannya(Reestr*& db, int& count, int& capacity) {
    cout << "\n--- Реєстрація нового транспортного засобу ---" << endl;

    // 1. ПЕРЕВІРКА ТА РОЗШИРЕННЯ ПАМ'ЯТІ
    if (count >= capacity) {
        int new_capacity = (capacity == 0) ? 1 : capacity * 2;
        Reestr* new_db = new Reestr[new_capacity];

        // Копіювання даних у новий блок
        for (int i = 0; i < count; i++) {
            new_db[i] = db[i];
        }

        delete[] db;      // Звільнення пам'яті
        db = new_db;      // Перенаправлення вказівника на новий масив
        capacity = new_capacity;
        cout << "[Система: Пам'ять розширено до " << capacity << " комірок]" << endl;
    }

    // Тимчасова структура для валідації вводу
    Reestr temp;

    // 2. ВВЕДЕННЯ ДАНИХ ТА ВАЛІДАЦІЯ
    cout << "Прізвище власника*: "; cin >> temp.l_name;
    cout << "Ім'я*: "; cin >> temp.f_name;
    cout << "По батькові: "; cin >> temp.s_name;

    cout << "Марка автомобіля*: ";
    cin.ignore(); // Очищення буфера після cin
    getline(cin, temp.marka);

    // Перевірка року випуску (Межі: 1886 - 2026)
    cout << "Рік випуску (1886-2026): ";
    while (!(cin >> temp.year) || temp.year < 1886 || temp.year > 2026) {
        cout << "Помилка! Введіть коректний рік: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    while (true) {
        cout << "Дата реєстрації (дд.мм.рррр)*: ";
        cin >> temp.data;

        if (isValidDate(temp.data)) {
            break; // Дата коректна
        } else {
            cout << "ПОМИЛКА: Некоректна дата або формат! Спробуйте ще раз (напр. 15.05.2023)." << endl;
        }
    }


    // Валідація номера та унікальності
    string inputNomer;
    while (true) {
        cout << "Введіть державний номер (формат AA1111BB, латинські літери)*: ";
        cin >> inputNomer;

        // 1. Приводимо до верхнього регістру для одноманітності
        for (int i = 0; i < inputNomer.length(); i++) {
            inputNomer[i] = toupper(inputNomer[i]);
        }

        // 2. Перевірка на формат
        if (!isValidCarNumber(inputNomer)) {
            cout << "ПОМИЛКА: Невірний формат номера! Має бути 2 літери, 4 цифри, 2 літери." << endl;
            continue;
        }

        // 3. Перевірка на унікальність
        bool isDuplicate = false;
        for (int i = 0; i < count; i++) {
            if (db[i].nomer == inputNomer) {
                isDuplicate = true;
                break;
            }
        }

        if (isDuplicate) {
            cout << "ПОМИЛКА: Автомобіль з номером " << inputNomer << " вже зареєстрований!" << endl;
        } else {
            // Якщо всі перевірки пройдені
            temp.nomer = inputNomer;
            break;
        }
    }

    cout << "Примітки: ";
    cin.ignore();
    getline(cin, temp.prumitku);

    // 3. ПЕРЕВІРКА ПОВНОТИ (Критерій успіху)
    if (temp.l_name.empty() || temp.f_name.empty() || temp.marka.empty() || temp.nomer.empty()) {
        cout << "\nРЕЗУЛЬТАТ НЕВДАЧІ: Не всі обов'язкові поля заповнені!" << endl;
        return;
    }

    // 4. ФІКСАЦІЯ ЗМІН
    db[count] = temp;
    count++;
    saveDatabaseToFile(db, count);

    cout << "\nРЕЗУЛЬТАТ УСПІХУ: Запис про автомобіль [" << temp.nomer << "] додано." << endl;
}

// Структура вже визначена у вашому проекті, тут для контексту
/*
struct Reestr {
    string l_name, f_name, s_name, marka, data, nomer, prumitku;
    int year;
};
*/

/**
 * Функція пошуку запису за державним номером
 * db - вказівник на масив структур
 *  count - поточна кількість записів у базі
 */
void searchnom(Reestr* db, int count) {
    cout << "\n--- Пошук у реєстрі МВС ---" << endl;

    // 1. ПЕРЕВІРКА НА ПОРОЖНЕЧУ
    if (count == 0) {
        cout << "Повідомлення: Реєстр порожній. Пошук неможливий." << endl;
        return;
    }

    // 2. ЗАПИТ КРИТЕРІЮ ПОШУКУ
    string searchKey;
    cout << "Введіть державний номер для пошуку: ";
    cin >> searchKey;

    // 3. ПІДГОТОВКА (НОРМАЛІЗАЦІЯ)
    // Перетворюємо введений номер у верхній регістр для надійності
    transform(searchKey.begin(), searchKey.end(), searchKey.begin(), ::toupper);

    // 4. ІНІЦІАЛІЗАЦІЯ ПРАПОРЦЯ
    bool found = false;

    // 5. ЦИКЛ ПЕРЕБОРУ (ЛІНІЙНИЙ ПОШУК)
    for (int i = 0; i < count; i++) {
        // Копіюємо номер з бази для порівняння (теж у верхньому регістрі)
        string currentNomer = db[i].nomer;
        transform(currentNomer.begin(), currentNomer.end(), currentNomer.begin(), ::toupper);

        // 5.1. ПОРІВНЯННЯ
        if (currentNomer == searchKey) {
            // 5.2. ДІЯ ПРИ ЗБІГУ (РЕЗУЛЬТАТ УСПІХУ)
            found = true;
            cout << "\n========================================" << endl;
            cout << "         ЗНАЙДЕНО ЗАПИС!               " << endl;
            cout << "========================================" << endl;
            cout << "Власник:       " << db[i].l_name << " " << db[i].f_name << " " << db[i].s_name << endl;
            cout << "Автомобіль:    " << db[i].marka << endl;
            cout << "Рік випуску:   " << db[i].year << endl;
            cout << "Дата реєстрації: " << db[i].data << endl;
            cout << "Держ. номер:   " << db[i].nomer << endl;
            cout << "Примітки:      " << db[i].prumitku << endl;
            cout << "========================================\n" << endl;

            break; // Перериваємо цикл, бо номер унікальний
        }
    }

    // 6. ОБРОБКА РЕЗУЛЬТАТУ "НЕ ЗНАЙДЕНО" (РЕЗУЛЬТАТ НЕВДАЧІ)
    if (!found) {
        cout << "Повідомлення: Запис із номером [" << searchKey << "] відсутній у базі." << endl;
    }

    // 7. ЗАВЕРШЕННЯ РОБОТИ ФУНКЦІЇ
}

