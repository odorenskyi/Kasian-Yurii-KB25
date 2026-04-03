#include <cassert>
#include <cmath>
#include <iostream>  // Для виведення повідомлень про помилки в консоль (cerr)
#include <fstream>   // Основна бібліотека для роботи з файлами (ifstream - читання, ofstream - запис)
#include <string>    // Для роботи з типом даних string та методами обробки рядків
#include <vector>    // Для потенційного зберігання списків слів (якщо знадобиться розширення)
#include <sstream>   // Для зручного розбиття зчитаного рядка на окремі слова (токенізація)
#include <cctype>    // Для функцій перевірки символів, як-от ispunct() (пунктуація)
#include <ctime>     // Для отримання поточного системного часу та дати
#include <bitset>    // Альтернативний спосіб переведення в двійкову систему
#include <algorithm> // Для функції reverse (реверс двійкового рядка)


double s_calculation(double x, double y, double z) {
    const double PI = 3.14159265358979323846;
    if (x < 0) return -1;
    double s;
    s = std::abs(std::pow((y * z), std::abs(x)) - (y / PI) - std::sqrt(x));
    std::cout << s;
    return 0;
}
int task9_1() {
    int hod;
    int all_zarp = 0;

    for (int i = 0; i < 5; i++) {
        bool isValid = false;
        while (!isValid) {
            std::cout << "Введіть кількість годин за " << i + 1 << " день: ";
            if (!(std::cin >> hod)) {
                std::cout << "Помилка! Введіть число." << std::endl;
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                continue;
            }
            if (hod >= 0 && hod <= 24) {
                if (hod <= 8) {
                    all_zarp += hod * 40;
                } else {
                    all_zarp += (hod * 40) + 300;
                }
                isValid = true;
            } else {
                std::cout << "Невірна кількість годин (має бути 0-24). Спробуйте ще раз." << std::endl;}
        }
    }
    std::cout << "Податки:" << std::endl;
    std::cout << "Прибутковий(15%):" << all_zarp*0.15 << " грн" <<std::endl;
    std::cout << "Пенсійний(2%):" << all_zarp*0.02 << " грн" <<std::endl;
    std::cout << "Страхування(0.6%):" << all_zarp*0.006 << " грн" <<std::endl;
    std::cout << "Страхування по втраті працездатності(1%):" << all_zarp*0.01 << " грн" <<std::endl;
    std::cout << "Фінальна зарплата:" << all_zarp-all_zarp*(0.15+0.02+0.006+0.01) << " грн" <<std::endl;
    return 0;}

int task9_2() {
    int ua_size;
    bool isValid = false;

    while (!isValid) {
        std::cout << "Введіть розмір чоловічих шкарпеток (UA): ";
        if (!(std::cin >> ua_size)) {
            std::cout << "Помилка! Будь ласка, введіть числове значення." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }}

        switch (ua_size) {
            case 23:
                std::cout << "Відповідні розміри:" << std::endl;
                std::cout << "ЄС: 37/38" << std::endl;
                std::cout << "Великобританія, США: 8" << std::endl;
                isValid = true;
                break;
            case 25:
                std::cout << "Відповідні розміри:" << std::endl;
                std::cout << "ЄС: 39/40" << std::endl;
                std::cout << "Великобританія, США: 9" << std::endl;
                isValid = true;
                break;
            case 27:
                std::cout << "Відповідні розміри:" << std::endl;
                std::cout << "ЄС: 41/42" << std::endl;
                std::cout << "Великобританія, США: 10" << std::endl;
                isValid = true;
                break;
            case 29:
                std::cout << "Відповідні розміри:" << std::endl;
                std::cout << "ЄС: 43/44" << std::endl;
                std::cout << "Великобританія, США: 11" << std::endl;
                isValid = true;
                break;
            case 31:
                std::cout << "Відповідні розміри:" << std::endl;
                std::cout << "ЄС: 45/46" << std::endl;
                std::cout << "Великобританія, США: 12" << std::endl;
                isValid = true;
                break;
            default:
                std::cout << "Невірний розмір (доступні: 23, 25, 27, 29, 31). Спробуйте ще раз." << std::endl;
                break;
        }

    return 0;
}

int task9_3() {
    int n;
    bool isValid = false;
    while (!isValid) {
        std::cout << "Введіть натуральне число N (0-7483650): ";
        if (!(std::cin >> n)) {
            std::cout << "Помилка! Будь ласка, введіть числове значення." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        if (n >= 0 && n <= 7483650) {
            isValid = true;
        } else {
            std::cout << "Число поза діапазоном. Спробуйте ще раз." << std::endl;
            continue;
        }
        bool bitD7 = (n & 128);
        int count = 0;
        int tempN = n;

        if (bitD7) {
            for (int i = 0; i < 32; i++) {
                count += ((n >> i) & 1) ? 0 : 1;
            }
        } else {
            while (tempN > 0) {
                count += (tempN & 1) ? 1 : 0;
                tempN >>= 1;
            }
        }
        std::cout << "Результат підрахунку: " << count << std::endl;
    }

    return 0;
}

std::string trimPunctuation(std::string word) {
    // В C++98 замість word.back() використовуємо word[word.length() - 1]
    // Замість word.pop_back() використовуємо erase
    while (!word.empty() && ispunct((unsigned char)word[word.length() - 1])) {
        word.erase(word.length() - 1, 1);
    }
    // Замість word.front() використовуємо word[0]
    while (!word.empty() && ispunct((unsigned char)word[0])) {
        word.erase(0, 1);
    }
    return word;
}

std::string toBinary(int n) {
    if (n == 0) return "0";
    std::string binary = "";
    while (n > 0) {
        binary += (n % 2 == 0 ? "0" : "1");
        n /= 2;
    }
    std::reverse(binary.begin(), binary.end());
    return binary;
}



void Task10_1(std::string inFileName, std::string outFileName) {
    std::ifstream inputFile(inFileName.c_str());
    std::ofstream outputFile(outFileName.c_str());

    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cerr << "Error opening files!" << std::endl;
        return;
    }

    outputFile << "ЗВІТ АНАЛІЗУ ТЕКСТУ" << std::endl;
    outputFile << "Касян Юрій" << std::endl;
    outputFile << "ЦНТУ, Кропивницький, Україна" << std::endl;
    outputFile << "2026" << std::endl;
    outputFile << "------------------------------------------" << std::endl;

    std::string line;
    int paragraphCount = 0;
    bool hasUkraine = false, hasUniversity = false, hasNotebook = false;

    while (std::getline(inputFile, line)) {
        if (!line.empty()) {
            paragraphCount++;
            std::stringstream ss(line);
            std::string rawWord;
            while (ss >> rawWord) {
                std::string word = trimPunctuation(rawWord);
                if (word == "Україна") hasUkraine = true;
                if (word == "університет") hasUniversity = true;
                if (word == "блокнот") hasNotebook = true;
            }
        }
    }

    outputFile << "Кількість абзаців: " << paragraphCount << std::endl;
    outputFile << "Україна: " << (hasUkraine ? "ТАК" : "НІ") << std::endl;
    outputFile << "університет: " << (hasUniversity ? "ТАК" : "НІ") << std::endl;
    outputFile << "блокнот: " << (hasNotebook ? "ТАК" : "НІ") << std::endl;

    inputFile.close();
    outputFile.close();
}

void Task10_2(std::string fileName) {
    std::ifstream inFile(fileName.c_str());
    if (!inFile.is_open()) return;

    int punctCount = 0;
    char ch;
    while (inFile.get(ch)) {
        if (ispunct((unsigned char)ch)) punctCount++;
    }
    inFile.close();

    std::ofstream outFile(fileName.c_str(), std::ios::app);
    std::time_t now = std::time(0);
    char* dt = std::ctime(&now);

    outFile << "\n\n[10.2] Пунктуація: " << punctCount << ". Час: " << dt;
    outFile.close();
}

void Task10_3(std::string fileName, double x, double y, double z, int b) {
    std::ofstream outFile(fileName.c_str(), std::ios::app);
    if (!outFile.is_open()) return;

    double mathResult = s_calculation(x, y, z);
    std::string binaryB = toBinary(b);

    outFile << "\n[10.3] s_calc=" << mathResult << " | b(bin)=" << binaryB << std::endl;
    outFile.close();
}
