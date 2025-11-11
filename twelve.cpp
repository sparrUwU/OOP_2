#include "twelve.hpp"
#include <stdexcept>
#include <algorithm>
#include <cstring>
using namespace std;

Twelve::Twelve() {
    size = 1;
    digits = new unsigned char[1];
    digits[0] = '0';
}

Twelve::Twelve(const initializer_list<unsigned char>& list) {
    if (list.size() == 0) {
        throw invalid_argument("Initializer list cannot be empty");
    }
    
    size = list.size();
    digits = new unsigned char[size];
    
    size_t i = 0;
    for (auto it = list.begin(); it != list.end(); ++it, ++i) {
        if (!isValidDigit(*it)) {
            delete[] digits;
            throw invalid_argument("Invalid digit in initializer list");
        }
        digits[i] = *it;
    }
    
    removeLeadingZeros();
}

Twelve::Twelve(const string& str) {
    if (str.empty()) {
        throw invalid_argument("String cannot be empty");
    }
    
    size = str.length();
    digits = new unsigned char[size];
    
    for (size_t i = 0; i < size; ++i) {
        if (!isValidDigit(str[i])) {
            delete[] digits;
            throw invalid_argument("Invalid digit in string");
        }
        digits[i] = str[i];
    }
    
    removeLeadingZeros();
}

Twelve::Twelve(const Twelve& other) {
    size = other.size;
    digits = new unsigned char[size];
    std::memcpy(digits, other.digits, size);
}

Twelve::Twelve(Twelve&& other) noexcept {
    digits = other.digits;
    size = other.size;
    other.digits = nullptr;
    other.size = 0;
}

Twelve::~Twelve() noexcept {
    delete[] digits;
}

Twelve& Twelve::operator=(const Twelve& other) {
    if (this != &other) {
        delete[] digits;
        size = other.size;
        digits = new unsigned char[size];
        std::memcpy(digits, other.digits, size);
    }
    return *this;
}

Twelve& Twelve::operator=(Twelve&& other) noexcept {
    if (this != &other) {
        delete[] digits;
        digits = other.digits;
        size = other.size;
        other.digits = nullptr;
        other.size = 0;
    }
    return *this;
}

int Twelve::digitToValue(unsigned char digit) const {
    if (digit >= '0' && digit <= '9') {
        return digit - '0';
    } else if (digit == 'A' || digit == 'a') {
        return 10;
    } else if (digit == 'B' || digit == 'b') {
        return 11;
    }
    throw invalid_argument("Invalid digit");
}

unsigned char Twelve::valueToDigit(int value) const {
    if (value >= 0 && value <= 9) {
        return '0' + value;
    } else if (value == 10) {
        return 'A';
    } else if (value == 11) {
        return 'B';
    }
    throw invalid_argument("Invalid value for digit");
}

void Twelve::removeLeadingZeros() {
    size_t leadingZeros = 0;
    while (leadingZeros < size - 1 && digits[leadingZeros] == '0') {
        leadingZeros++;
    }
    
    if (leadingZeros > 0) {
        size_t newSize = size - leadingZeros;
        unsigned char* newDigits = new unsigned char[newSize];
        std::memcpy(newDigits, digits + leadingZeros, newSize);
        delete[] digits;
        digits = newDigits;
        size = newSize;
    }
}

bool Twelve::isValidDigit(unsigned char digit) {
    return (digit >= '0' && digit <= '9') || 
           (digit == 'A' || digit == 'a') || 
           (digit == 'B' || digit == 'b');
}

Twelve Twelve::add(const Twelve& other) const {
    size_t maxSize = std::max(size, other.size) + 1;
    unsigned char* result = new unsigned char[maxSize];
    
    int carry = 0;
    int i = size - 1;
    int j = other.size - 1;
    int k = maxSize - 1;
    
    for (size_t idx = 0; idx < maxSize; ++idx) {
        result[idx] = '0';
    }
    
    while (i >= 0 || j >= 0 || carry > 0) {
        int sum = carry;
        if (i >= 0) sum += digitToValue(digits[i--]);
        if (j >= 0) sum += digitToValue(other.digits[j--]);
        
        carry = sum / 12;
        result[k--] = valueToDigit(sum % 12);
    }
    
    Twelve temp;
    delete[] temp.digits;
    temp.digits = result;
    temp.size = maxSize;
    temp.removeLeadingZeros();
    
    return temp;
}

Twelve Twelve::subtract(const Twelve& other) const {
    if (lessThan(other)) {
        throw std::invalid_argument("Cannot subtract larger number");
    }
    
    if (equals(other)) {
        return Twelve();
    }
    
    size_t resultSize = size;
    unsigned char* result = new unsigned char[resultSize];
    
    int borrow = 0;
    int i = size - 1;
    int j = other.size - 1;
    int k = resultSize - 1;
    
    while (i >= 0) {
        int top = digitToValue(digits[i--]);
        int bottom = (j >= 0) ? digitToValue(other.digits[j--]) : 0;
        
        if (borrow) {
            top--;
            borrow = 0;
        }
        
        if (top < bottom) {
            top += 12;
            borrow = 1;
        }
        
        result[k--] = valueToDigit(top - bottom);
    }
    
    Twelve temp;
    delete[] temp.digits;
    temp.digits = result;
    temp.size = resultSize;
    temp.removeLeadingZeros();
    
    Twelve finalResult;
    delete[] finalResult.digits;
    finalResult.digits = new unsigned char[temp.size];
    finalResult.size = temp.size;
    std::memcpy(finalResult.digits, temp.digits, temp.size);
    
    return finalResult;
}

bool Twelve::equals(const Twelve& other) const {
    if (size != other.size) return false;
    for (size_t i = 0; i < size; ++i) {
        if (digits[i] != other.digits[i]) return false;
    }
    return true;
}

bool Twelve::lessThan(const Twelve& other) const {
    if (size != other.size) {
        return size < other.size;
    }
    
    for (size_t i = 0; i < size; ++i) {
        int val1 = digitToValue(digits[i]);
        int val2 = digitToValue(other.digits[i]);
        if (val1 != val2) {
            return val1 < val2;
        }
    }
    return false;
}

bool Twelve::greaterThan(const Twelve& other) const {
    return !lessThan(other) && !equals(other);
}

std::string Twelve::toString() const {
    return string(digits, digits + size);
}

size_t Twelve::getSize() const {
    return size;
}