#include "../include/LongNumber.hpp"

// Пользовательский литеральный оператор:
// Позволяет писать 3.1415_longnum для создания LongNumber
LongNumber operator""_longnum(long double value) {
    // Допустим, по умолчанию ставим точность 16 бит
    return LongNumber(value, 16);
}

