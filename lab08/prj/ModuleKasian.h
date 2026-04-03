#ifndef MODULESKASIAN_H_INCLUDED
#define MODULESKASIAN_H_INCLUDED

#include <string> // Необхідно для std::string

// Прототипи функцій з ЛР 08 та 09
double s_calculation(double x, double y, double z);
int task9_1();
int task9_2();
int task9_3();

// Прототипи функцій для ЛР 10
// Використовуємо std:: перед string, щоб уникнути помилок компіляції
// у файлах, де не прописано 'using namespace std'
void Task10_1(std::string inFileName, std::string outFileName);
void Task10_2(std::string fileName);
void Task10_3(std::string fileName, double x, double y, double z, int b);

#endif // MODULESKASIAN_H_INCLUDED
