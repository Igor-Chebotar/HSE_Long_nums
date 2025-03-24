#include "../include/LongNumber.hpp"
#include <iostream>
#include <locale>

int main() {
    std::setlocale(LC_ALL, "ru_RU.UTF-8");  // корректный вывод русских символов (если нужно)

    // Демонстрация: создание длинных чисел
    LongNumber a(1.5L, 16);  // 1.5 с 16 битами точности
    LongNumber b(2.25L, 16);

    // Арифметика
    LongNumber sum = a + b;
    LongNumber diff = b - a;
    LongNumber prod = a * b;
    LongNumber quot = b / a;

    // Сравнение
    bool equal = (a == b);
    bool greater = (b > a);

    // Вывод
    std::cout << "a = " << a.toString(10) << "\n";
    std::cout << "b = " << b.toString(10) << "\n";
    std::cout << "a + b = " << sum.toString(10) << "\n";
    std::cout << "b - a = " << diff.toString(10) << "\n";
    std::cout << "a * b = " << prod.toString(10) << "\n";
    std::cout << "b / a = " << quot.toString(10) << "\n";

    std::cout << "a == b: " << (equal ? "true" : "false") << "\n";
    std::cout << "b > a: " << (greater ? "true" : "false") << "\n";

    // Литеральный оператор
    LongNumber pi_literal = 3.1415_longnum;
    std::cout << "Pi literal: " << pi_literal.toString(10) << "\n";

    return 0;
}
