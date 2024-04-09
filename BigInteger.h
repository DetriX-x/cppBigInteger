#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <exception>
#include <utility>
#include <cmath>

class BigInteger
{
private:
    std::string digits;
    bool sign;

    void removeLeadingZeros();

    BigInteger& sum(const BigInteger& bi);

    BigInteger& sub(const BigInteger& bi);

    bool lessThan(const BigInteger& subtrahend) const;

    bool isBigInt(const std::string& s,
                  bool& sign,
                  size_t& signs_count) const;
    const std::pair<size_t, size_t>
        skipSigns(const std::string& s) const; 
public:
    // ctors
    
    explicit BigInteger(unsigned long long value = 0);

    explicit BigInteger(const std::string& s);

    // public functions

    BigInteger& operator+();
    BigInteger& operator++();
    BigInteger operator++(int);
 
    BigInteger& operator-();
    BigInteger& operator--();
    BigInteger operator--(int);
     
    BigInteger& operator+=(const BigInteger& bi);
    BigInteger operator+(const BigInteger& bi) const;

    BigInteger& operator-=(const BigInteger& bi);
    BigInteger operator-(const BigInteger& bi) const;

    BigInteger& operator*=(const BigInteger& bi);
    BigInteger operator*(const BigInteger& bi) const;

    BigInteger& operator^=(const BigInteger& bi);
    BigInteger operator^(const BigInteger& bi) const;

    BigInteger& operator/=(const BigInteger& bi);
    BigInteger operator/(const BigInteger& bi) const;

    bool operator==(const BigInteger& bi) const;

    bool operator!=(const BigInteger& bi) const;

    bool operator<(const BigInteger& bi) const;

    bool operator<=(const BigInteger& bi) const;

    bool operator>(const BigInteger& bi) const;

    bool operator>=(const BigInteger& bi) const;

    friend std::ostream& operator<<(std::ostream& os, const BigInteger& bi);
    friend std::istream& operator>>(std::istream& in, BigInteger& bi);

    inline bool getSign() const
    {
        return sign;
    }

    enum Sign : bool 
    {
        Positive, Negative
    };
};

BigInteger operator"" _bi(const char* s, size_t);

BigInteger operator"" _bi(unsigned long long num);
#endif
