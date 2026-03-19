#include <iostream>
#include <cassert>
#include <cmath>


double s_calculation(double x, double y, double z) {
    const double PI = 3.14159265358979323846;
    if (x < 0) return -1;
    double s;
    s = std::abs(std::pow((y * z), std::abs(x)) - (y / PI) - std::sqrt(x));
    std::cout << s;
    return 0;
}


