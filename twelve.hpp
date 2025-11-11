#ifndef TWELVE_H
#define TWELVE_H

#include <string>
#include <initializer_list>
using namespace std;

class Twelve {
private:
    unsigned char* digits;
    size_t size;          
    
    int digitToValue(unsigned char digit) const;
    unsigned char valueToDigit(int value) const;
    void removeLeadingZeros();
    
public:
    Twelve();
    Twelve(const initializer_list<unsigned char>& list);
    Twelve(const string& str);
    
    Twelve(const Twelve& other);
    
    Twelve(Twelve&& other) noexcept;
    
    virtual ~Twelve() noexcept;
    
    Twelve& operator=(const Twelve& other);
    Twelve& operator=(Twelve&& other) noexcept;
    Twelve add(const Twelve& other) const;
    Twelve subtract(const Twelve& other) const;
    bool equals(const Twelve& other) const;
    bool lessThan(const Twelve& other) const;
    bool greaterThan(const Twelve& other) const;

    std::string toString() const;
    size_t getSize() const;
    static bool isValidDigit(unsigned char digit);
};

#endif