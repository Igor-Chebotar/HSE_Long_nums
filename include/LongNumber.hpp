#include <vector>
#include <cstdint>

// Класс LongNumber представляет число с фиксированной точкой
// в двоичной системе с заданной точностью.
class LongNumber{
  public:
    // --- Конструкторы и деструктор ---
    LongNumber();  // Конструктор по умолчанию
    LongNumber(const LongNumber& other);  // Конструктор копирования
    LongNumber(long double number, unsigned precision);  // Конструктор из литерала
    LongNumber& operator=(const LongNumber& other);  // Оператор присваивания
    ~LongNumber();  // Деструктор

    // --- Перезагрузка арифметических операторов ---
    LongNumber operator+(const LongNumber& other) const;
    LongNumber operator-(const LongNumber& other) const;
    LongNumber operator*(const LongNumber& other) const;
    LongNumber operator/(const LongNumber& other) const;

    // ---Перегрузка операторов сравнения ---
    bool operator==(const LongNumber& other) const;
    bool operator!=(const LongNumber& other) const;
    bool operator<(const LongNumber& other) const;
    bool operator>(const LongNumber& other) const;

    // --- Методы управления точностью ---
    void setPrecision(unsigned presicion);
    unsigned getPrecision() const;

  private:
    // Внутреннее представление числа.
    std::vector<uint8_t> digits;  // каждая ячейка хранит одну "цифру" (в двоичном виде)
    bool isNegative;              // знак числа
    unsigned precision;           // количество битов после запятой
};
