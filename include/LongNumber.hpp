#ifndef LONGNUMBER_HPP
#define LONGNUMBER_HPP

#include <string>
#include <utility> // для std::pair

// Класс «Длинное Число» с фиксированной точкой в двоичной системе
class LongNumber {
public:
    // Конструкторы и деструктор
    LongNumber();
    LongNumber(const LongNumber& other);
    LongNumber(long double number, unsigned prec);
    LongNumber(const std::string& numberStr, unsigned prec);
    LongNumber& operator=(const LongNumber& other);
    ~LongNumber();

    // Арифметические операторы
    LongNumber operator+(const LongNumber& other) const;
    LongNumber operator-(const LongNumber& other) const;
    LongNumber operator*(const LongNumber& other) const;
    LongNumber operator/(const LongNumber& other) const;

    // Операторы сравнения
    bool operator==(const LongNumber& other) const;
    bool operator!=(const LongNumber& other) const;
    bool operator<(const LongNumber& other) const;
    bool operator>(const LongNumber& other) const;

    // Методы управления точностью
    void setPrecision(unsigned p);
    unsigned getPrecision() const;

    // Преобразование в long double (приблизительно)
    long double toLongDouble() const;

    // Строковое представление числа (возвращает двоичное представление с точкой)
    std::string toString(unsigned decimalDigits) const;

private:
    std::string value;  // Внутреннее представление числа в двоичной системе (целая и дробная части слитно)
    bool isNegative;
    unsigned precision; // Количество битов, отведённых под дробную часть

    // Вспомогательный метод для инициализации из long double
    void fromLongDouble(long double number, unsigned prec);

    // Статические функции для работы с бинарными строками

    static std::string trimLeadingZeros(const std::string& s);
    static std::string fromLongDoubleToBinary(long double number, unsigned prec);
    static long double binaryToLongDouble(const std::string& bin);
    static std::string addBinary(const std::string& a, const std::string& b);
    static std::string subtractBinary(const std::string& a, const std::string& b);
    static std::string multiplyBinary(const std::string& a, const std::string& b);
    static std::pair<std::string, std::string> divideBinary(const std::string& dividend, const std::string& divisor);
};

// Пользовательский литеральный оператор для создания LongNumber
LongNumber operator"" _longnum(long double value);

#endif // LONGNUMBER_HPP
