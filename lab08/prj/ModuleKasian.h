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

class ClassLab12_Kasian {
private:
    double radius; // Радіус основи циліндра/труби
    double height; // Висота/довжина циліндра/труби

public:
    // Конструктор з параметрами за замовчуванням
    ClassLab12_Kasian(double r = 1.0, double h = 1.0);

    // Методи-мутатори (сетери) з валідацією ОДЗ
    void setRadius(double r);
    void setHeight(double h);
    void setAttributes(double r = 1.0, double h = 1.0);

    // Методи-инспектори (гетери)
    double getRadius() const;
    double getHeight() const;

    // Обчислювальний метод
    double getLateralArea() const;
};

// Конструктор ініціалізує стан через метод комплексної установки
ClassLab12_Kasian::ClassLab12_Kasian(double r, double h) {
    setAttributes(r, h);
}

// Забезпечення валідації радіуса (ОДЗ: r > 0)
void ClassLab12_Kasian::setRadius(double r) {
    if (r > 0.0) {
        radius = r;
    } else {
        radius = 1.0; // Автокоригування у разі некоректних даних
    }
}

// Забезпечення валідації висоти (ОДЗ: h > 0)
void ClassLab12_Kasian::setHeight(double h) {
    if (h > 0.0) {
        height = h;
    } else {
        height = 1.0; // Автокоригування у разі некоректних даних
    }
}

// Комплексна зміна атрибутів
void ClassLab12_Kasian::setAttributes(double r, double h) {
    setRadius(r);
    setHeight(h);
}

// Гетер радіуса
double ClassLab12_Kasian::getRadius() const {
    return radius;
}

// Гетер висоти
double ClassLab12_Kasian::getHeight() const {
    return height;
}

// Обчислення площі бічної поверхні: S = 2 * pi * r * h
double ClassLab12_Kasian::getLateralArea() const {
    const double PI = 3.141592653589793;
    return 2.0 * PI * radius * height;}
#endif // MODULESKASIAN_H_INCLUDED
