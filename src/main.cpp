#include "../include/LongNumber.hpp"
#include <iostream>
#include <clocale>  // Для std::setlocale

int main() {
    // Устанавливаем локаль (UTF-8).
    // В Windows может понадобиться переключить консоль на UTF-8 командой: chcp 65001
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    // Создаем объект с конструктором по умолчанию
    LongNumber a;

    // Создаем объект из литерала с плавающей точкой и точностью 16 бит
    LongNumber b(3.1415L, 16);

    // Выполняем операцию сложения (пока заглушка)
    LongNumber c = a + b;

    // Выводим значение точности (пример проверки работы метода)
    std::cout << "Точность: " << c.getPrecision() << std::endl;

    return 0;
}
