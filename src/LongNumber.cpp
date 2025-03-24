#include "LongNumber.hpp"
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include <sstream>

// -------------------- Вспомогательные функции --------------------

// Удаляет ведущие нули из строки
std::string LongNumber::trimLeadingZeros(const std::string& s) {
    size_t pos = s.find_first_not_of('0');
    return (pos == std::string::npos) ? "0" : s.substr(pos);
}

// Преобразует число типа long double в двоичную строку, представляющую целое число,
// равное round(|number| * 2^(prec)).
std::string LongNumber::fromLongDoubleToBinary(long double number, unsigned prec) {
    long double scaled = number * std::pow(2.0L, prec);
    long long intPart = static_cast<long long>(std::llround(scaled));
    if (intPart < 0) intPart = -intPart;
    if (intPart == 0) return "0";
    std::string bin;
    while (intPart > 0) {
        bin.push_back((intPart % 2) + '0');
        intPart /= 2;
    }
    std::reverse(bin.begin(), bin.end());
    return bin;
}

// Преобразует двоичную строку в long double (приблизительно)
long double LongNumber::binaryToLongDouble(const std::string& bin) {
    long double result = 0.0L;
    for (char c : bin) {
        result = result * 2 + (c - '0');
    }
    return result;
}

// Сложение двоичных строк (для неотрицательных чисел)
std::string LongNumber::addBinary(const std::string& a, const std::string& b) {
    int i = a.size() - 1, j = b.size() - 1, carry = 0;
    std::string res;
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) { sum += a[i--] - '0'; }
        if (j >= 0) { sum += b[j--] - '0'; }
        carry = sum / 2;
        res.push_back((sum % 2) + '0');
    }
    std::reverse(res.begin(), res.end());
    return trimLeadingZeros(res);
}

// Вычитание: a - b, где a >= b, оба неотрицательны
std::string LongNumber::subtractBinary(const std::string& a, const std::string& b) {
    int i = a.size() - 1, j = b.size() - 1, borrow = 0;
    std::string res;
    while (i >= 0) {
        int diff = (a[i] - '0') - borrow;
        if (j >= 0) {
            diff -= (b[j] - '0');
            j--;
        }
        if (diff < 0) { diff += 2; borrow = 1; }
        else { borrow = 0; }
        res.push_back(diff + '0');
        i--;
    }
    std::reverse(res.begin(), res.end());
    return trimLeadingZeros(res);
}

// Умножение двоичных строк (наивный алгоритм)
std::string LongNumber::multiplyBinary(const std::string& a, const std::string& b) {
    int n = a.size(), m = b.size();
    std::string res(n + m, '0');
    for (int i = n - 1; i >= 0; i--) {
        int carry = 0;
        for (int j = m - 1; j >= 0; j--) {
            int sum = (res[i+j+1]-'0') + (a[i]-'0')*(b[j]-'0') + carry;
            carry = sum / 2;
            res[i+j+1] = (sum % 2) + '0';
        }
        res[i] = ((res[i]-'0') + carry) + '0';
    }
    return trimLeadingZeros(res);
}

// Деление двоичных строк: возвращает пару {quotient, remainder}.
// Наивный алгоритм долгого деления, оба числа неотрицательны.
std::pair<std::string, std::string> LongNumber::divideBinary(const std::string& dividend, const std::string& divisor) {
    if (divisor == "0")
        throw std::runtime_error("Division by zero in LongNumber");
    std::string quotient;
    std::string remainder = "";
    for (char bit : dividend) {
        remainder.push_back(bit);
        remainder = trimLeadingZeros(remainder);
        int count = 0;
        while ((remainder.size() > divisor.size()) ||
              (remainder.size() == divisor.size() && remainder >= divisor)) {
            remainder = subtractBinary(remainder, divisor);
            count++;
        }
        quotient.push_back(count + '0');
    }
    quotient = trimLeadingZeros(quotient);
    if (quotient == "") quotient = "0";
    return { quotient, remainder };
}

// -------------------- Конструкторы --------------------

LongNumber::LongNumber() : isNegative(false), precision(0), value("0") { }

LongNumber::LongNumber(const LongNumber& other)
    : value(other.value), isNegative(other.isNegative), precision(other.precision) { }

LongNumber::LongNumber(long double number, unsigned prec)
    : isNegative(false), precision(prec) {
    if (number < 0.0L) {
        isNegative = true;
        number = -number;
    }
    value = fromLongDoubleToBinary(number, prec);
}

LongNumber::LongNumber(const std::string& numberStr, unsigned prec)
    : isNegative(false), precision(prec) {
    long double num = std::stold(numberStr);
    if (num < 0.0L) {
        isNegative = true;
        num = -num;
    }
    value = fromLongDoubleToBinary(num, prec);
}

LongNumber& LongNumber::operator=(const LongNumber& other) {
    if (this != &other) {
        value = other.value;
        isNegative = other.isNegative;
        precision = other.precision;
    }
    return *this;
}

LongNumber::~LongNumber() { }

// -------------------- Арифметические операторы --------------------

// Реализуем оператор сложения с поддержкой отрицательных чисел
LongNumber LongNumber::operator+(const LongNumber& other) const {
    if (precision != other.precision)
        throw std::runtime_error("Precision mismatch in addition");

    // Если знаки одинаковые, выполняем обычное сложение.
    if (isNegative == other.isNegative) {
        LongNumber result;
        result.precision = precision;
        result.value = addBinary(value, other.value);
        result.isNegative = isNegative;
        return result;
    } else {
        // Если знаки разные, вычитаем меньшее по абсолютной величине из большего.
        LongNumber A = *this;  A.isNegative = false;
        LongNumber B = other;  B.isNegative = false;
        if (A == B) {
            return LongNumber(0.0L, precision);
        } else if (A > B) {
            LongNumber result = A - B;
            result.isNegative = isNegative; // знак большего по модулю
            return result;
        } else {
            LongNumber result = B - A;
            result.isNegative = other.isNegative;
            return result;
        }
    }
}

LongNumber LongNumber::operator-(const LongNumber& other) const {
    if (precision != other.precision)
        throw std::runtime_error("Precision mismatch in subtraction");
    LongNumber result;
    result.precision = precision;
    // Предполагается, что *this >= other (для неотрицательных чисел)
    result.value = subtractBinary(value, other.value);
    result.isNegative = false;
    return result;
}

LongNumber LongNumber::operator*(const LongNumber& other) const {
    if (precision != other.precision)
        throw std::runtime_error("Precision mismatch in multiplication");
    LongNumber result;
    result.precision = precision;
    std::string mult = multiplyBinary(value, other.value);
    // После умножения общее количество битов дробной части увеличивается.
    // Для нормализации делим результат на 2^(precision)
    std::string scaling = "1";
    scaling.append(precision, '0'); // 2^(precision)
    auto divRes = divideBinary(mult, scaling);
    result.value = divRes.first;
    result.isNegative = (isNegative != other.isNegative);
    return result;
}

LongNumber LongNumber::operator/(const LongNumber& other) const {
    if (precision != other.precision)
        throw std::runtime_error("Precision mismatch in division");
    if (other.value == "0")
        throw std::runtime_error("Division by zero in LongNumber");
    LongNumber result;
    result.precision = precision;
    // Для сохранения точности масштабируем делимое: умножаем на 2^(precision)
    std::string scaling = "1";
    scaling.append(precision, '0');
    std::string scaledDividend = multiplyBinary(value, scaling);
    auto divRes = divideBinary(scaledDividend, other.value);
    result.value = divRes.first;
    result.isNegative = (isNegative != other.isNegative);
    return result;
}

// -------------------- Операторы сравнения --------------------

bool LongNumber::operator==(const LongNumber& other) const {
    return (isNegative == other.isNegative) && (precision == other.precision) && (value == other.value);
}

bool LongNumber::operator!=(const LongNumber& other) const {
    return !(*this == other);
}

bool LongNumber::operator<(const LongNumber& other) const {
    return this->toLongDouble() < other.toLongDouble();
}

bool LongNumber::operator>(const LongNumber& other) const {
    return this->toLongDouble() > other.toLongDouble();
}

// -------------------- Управление точностью --------------------

void LongNumber::setPrecision(unsigned p) {
    long double val = this->toLongDouble();
    precision = p;
    value = fromLongDoubleToBinary(std::fabs(val), p);
}

unsigned LongNumber::getPrecision() const {
    return precision;
}

// -------------------- Преобразование в long double --------------------
long double LongNumber::toLongDouble() const {
    long double intVal = binaryToLongDouble(value);
    long double scaled = intVal / std::pow(2.0L, precision);
    return (isNegative ? -scaled : scaled);
}

// -------------------- Строковое представление --------------------
std::string LongNumber::toString(unsigned decimalDigits) const {
    long double scaled = binaryToLongDouble(value) / std::pow(2.0L, precision);
    std::ostringstream out;
    out.precision(decimalDigits);
    out << std::fixed << (isNegative ? -scaled : scaled);
    return out.str();
}

// -------------------- Пользовательский литеральный оператор --------------------
LongNumber operator"" _longnum(long double val) {
    return LongNumber(val, 16);
}
