#include "../include/LongNumber.hpp"
#include <iostream>
#include <cstdlib>  // для std::atoi
#include <stdexcept>

// Функция вычисляет число π по алгоритму Нилаканты
LongNumber computePiNilakantha(unsigned decimalDigits) {
    // Устанавливаем двоичную точность: для 10 десятичных знаков можно взять, например, 64 бита,
    // а для более высокой точности можно масштабировать. Здесь используем коэффициент 4.
    unsigned binaryPrecision = decimalDigits * 4;
    if (binaryPrecision < 16) binaryPrecision = 16;

    // Количество членов ряда
    int N = 1000; // Для 10 знаков обычно 1000 итераций даст достаточную точность

    // Начальное значение: π = 3
    LongNumber pi(3.0L, binaryPrecision);

    // Вычисляем сумму членов ряда: term = (-1)^(n+1) / (2n*(2n+1)*(2n+2))
    LongNumber sum(0.0L, binaryPrecision);
    for (int n = 1; n <= N; ++n) {
        LongNumber sign = (n % 2 == 1) ? LongNumber(1.0L, binaryPrecision)
                                       : LongNumber(-1.0L, binaryPrecision);
        LongNumber denom = LongNumber(2.0L * n, binaryPrecision) *
                             LongNumber(2.0L * n + 1, binaryPrecision) *
                             LongNumber(2.0L * n + 2, binaryPrecision);
        LongNumber term = sign / denom;
        sum = sum + term;
    }

    // Итог: π = 3 + 4 * сумма членов ряда
    LongNumber four(4.0L, binaryPrecision);
    LongNumber piTerm = four * sum;
    pi = pi + piTerm;
    return pi;
}


int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: pi_calculator <decimal_digits>\n";
        return 1;
    }

    unsigned decimalDigits = std::atoi(argv[1]);
    if (decimalDigits == 0) {
        std::cerr << "Invalid number of decimal digits.\n";
        return 1;
    }

    try {
        LongNumber pi = computePiNilakantha(decimalDigits);
        std::cout << "Pi ~ " << pi.toString(decimalDigits) << std::endl;
    } catch (const std::runtime_error &e) {
        std::cerr << "Error computing pi: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}

