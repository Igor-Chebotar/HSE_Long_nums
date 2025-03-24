#include "../include/LongNumber.hpp"
#include <iostream>
#include <cmath>

// Утилита для сравнения double с некоторой допустимой погрешностью
bool almostEqual(long double a, long double b, long double eps = 1e-9L) {
    return fabsl(a - b) < eps;
}

static int testCount = 0;
static int failCount = 0;

void check(bool condition, const std::string& testName) {
    ++testCount;
    if (condition) {
        std::cout << testName << ": OK" << std::endl;
    } else {
        std::cout << testName << ": FAIL" << std::endl;
        ++failCount;
    }
}

int main() {
    // 1) Тест конструктора по умолчанию
    {
        LongNumber a;
        check(a.toLongDouble() == 0.0L, "Default constructor");
    }

    // 2) Тест конструктора из литерала
    {
        LongNumber b(3.5L, 10);
        check(almostEqual(b.toLongDouble(), 3.5L), "Constructor from long double");
    }

    // 3) Тест копирования
    {
        LongNumber b(2.25L, 8);
        LongNumber c(b);
        check(almostEqual(c.toLongDouble(), 2.25L), "Copy constructor");
    }

    // 4) Тест операторов +, -
    {
        LongNumber x(1.0L, 8);
        LongNumber y(2.0L, 8);
        LongNumber sum = x + y; // 3.0
        LongNumber diff = y - x; // 1.0
        check(almostEqual(sum.toLongDouble(), 3.0L), "Operator +");
        check(almostEqual(diff.toLongDouble(), 1.0L), "Operator -");
    }

    // 5) Тест операторов сравнения
    {
        LongNumber a(2.0L, 8);
        LongNumber b(2.0L, 8);
        LongNumber c(2.1L, 8);

        check(a == b, "Operator ==");
        check(a != c, "Operator !=");
        check(a < c,  "Operator <");
        check(c > a,  "Operator >");
    }

    // Вывод итогов
    std::cout << "Tests passed: " << (testCount - failCount) << "/" << testCount << std::endl;
    return failCount;
}
