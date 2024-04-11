#include "BigInteger.h" 

BigInteger::BigInteger(unsigned long long value)
    : digits(std::to_string(value)),
      sign(Sign::Positive) 
{
    std::reverse(digits.begin(), digits.end());
}

BigInteger::BigInteger(const std::string& s) :
    digits(s)
{
    size_t signs_count{};
    if(!isBigInt(digits, sign, signs_count))
    {
        throw std::runtime_error("Invalid value for BigInteger");
    }
    std::reverse(digits.begin(), digits.end());
    digits.erase(digits.size() - signs_count, digits.size());
}

bool BigInteger::isBigInt(const std::string& s,
                          bool& sign,
                          size_t& signs_count) const
{
    size_t len = s.size();
    if(len < 1)
    {
        return false;
    }
    const auto& sign_pack = skipSigns(digits);
           signs_count = sign_pack.first;
    size_t dash_count  = sign_pack.second;
    sign = dash_count % 2;
    if(signs_count == len)
    {
        return false;
    }
    if((len - signs_count > 1) &&
       (s[signs_count] == '0') &&
       (s[signs_count + 1] == '0'))
    { // leading zeros
        return false;
    }
    for(size_t i = signs_count; i < len; ++i)
    {
        if(!std::isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}

const std::pair<size_t, size_t>
BigInteger::skipSigns(const std::string& s) const
{
    size_t signs_count = 0;
    size_t dash_count = 0;
    for(const auto& ch : s)
    {
        if(ch == '-')
        {
            ++dash_count;
            ++signs_count;
        }
        else if(ch == '+')
        {
            ++signs_count;
        }
        else
        {
            break;
        }
    }
    return std::make_pair(signs_count, dash_count);
}

BigInteger& BigInteger::operator+()
{
    return *this;
}

BigInteger& BigInteger::operator++()
{
    *this += "1"_bi;
    return *this;
}

BigInteger BigInteger::operator++(int)
{
    BigInteger bi;
    bi = (*this);
    ++(*this);
    return bi;
}

BigInteger& BigInteger::operator-()
{
    sign = !sign;
    return *this;
}

BigInteger& BigInteger::operator--()
{
    *this -= 1_bi;
    return *this;
}

BigInteger BigInteger::operator--(int)
{
    BigInteger bi;
    bi = *this;
    --(*this);
    return bi;
}

BigInteger& BigInteger::operator+=(const BigInteger& bi)
{
    if(sign == bi.sign)
    {
        return sum(bi);
    }
    return sub(bi);
}

BigInteger BigInteger::operator+(const BigInteger& bi) const
{
    BigInteger res;
    res = *this;
    res += bi;
    return res;
}

BigInteger& BigInteger::operator-=(const BigInteger& bi)
{
    if(sign == bi.sign)
    {
        return sub(bi);
    }
    return sum(bi);
}

BigInteger BigInteger::operator-(const BigInteger& bi) const
{
    BigInteger res;
    res = *this;
    res -= bi;
    return res;
}

BigInteger& BigInteger::sum(const BigInteger& bi)
{
    size_t carry = 0;
    size_t firstSize = digits.size();
    size_t secondSize = bi.digits.size();

    if(secondSize > firstSize)
    {
        digits.append(secondSize - firstSize, '0');
    }

    for(size_t i = 0; i < digits.size(); ++i)
    {
        if(i < secondSize)
        {
            digits[i] += bi.digits[i] - '0' + carry;
        }
        else
        {
            digits[i] += carry;
        }
        if(digits[i] > '9')
        {
            digits[i] -= 10;
            carry = 1;
        }
        else
        {
            carry = 0;
        }
    }
    if(carry)
    {
        digits.push_back('1');
    }
    return *this;
}

BigInteger& BigInteger::sub(const BigInteger& bi)
{
    std::string& result = this->digits;
    bool a_less_b = lessThan(bi);
    const std::string& firstOp = a_less_b ? bi.digits : this->digits;
    const std::string& secondOp = a_less_b ? this->digits : bi.digits;
    bool outSign = a_less_b ^ sign;
    size_t carry = 0;
    size_t firstSize = firstOp.size();
    size_t secondSize = secondOp.size();

    if(secondSize < firstSize)
    {
        result.append(firstSize - secondSize, '0');
    }

    for(size_t i = 0; i < result.size(); ++i)
    {
        if(i < secondSize)
        {
            result[i] = firstOp[i] + '0' - secondOp[i] - carry;
        }
        else
        {
            result[i] = firstOp[i] - carry;
        }
        if(result[i] < '0')
        {
            carry = 1;
            result[i] += 10;
        }
        else
        {
            carry = 0;
        }
    }
    removeLeadingZeros();
    sign = outSign;
    if(result.length() == 1 && result[0] == '0')
    {
        sign = Sign::Positive;
    }
    return *this;
}

void BigInteger::removeLeadingZeros()
{
    size_t count = 0;
    for(size_t i = digits.size() - 1; i != size_t(0); --i)
    {
        if(digits[i] == '0')
        {
            count++;
        }
        else
        {
            break;
        }
    }
    digits.erase(digits.size() - count);
}

BigInteger& BigInteger::operator*=(const BigInteger& bi)
{ 
    if(digits.empty() || bi.digits.empty())
    {
        *this = 0_bi;
        return *this;
    }
    bool outSign = sign != bi.sign;
    size_t firstSize = digits.size();
    size_t secondSize = bi.digits.size();

    std::vector<int> acc(firstSize + secondSize, 0);
    for(size_t i = 0; i != firstSize; ++i)
    {
        for(size_t j = 0; j != secondSize; ++j)
        {
            acc[i + j] += ((digits[i] - '0') * (bi.digits[j] - '0'));
        }
    }

    digits.resize(acc.size());
    for(size_t carry = 0, i = 0, t; i != acc.size(); ++i)
    {
        t = carry + acc[i];
        acc[i] = t % 10;
        carry = t / 10;
        digits[i] = '0' + static_cast<char>(acc[i]);
    }

    sign = outSign;
    removeLeadingZeros();
    return *this;
}

BigInteger BigInteger::operator*(const BigInteger& bi) const
{
    BigInteger res(*this);
    res *= bi;
    return res;
}

BigInteger& BigInteger::operator^=(const BigInteger& bi)
{ 
    auto mul(*this);
    if(bi.sign == Sign::Negative)
    {
        *this = 0_bi;
        return *this; 
    }
    for(auto i = 1_bi; i != bi.abs(); ++i)
    {
        *this *= mul;
    }
    if(sign == Sign::Negative)
    {
        sign = bi.isOdd();
    }
    return *this;
}

BigInteger BigInteger::operator^(const BigInteger& bi) const
{
    BigInteger res(*this);
    res ^= bi;
    return res;
}

bool BigInteger::isOdd() const
{
    return (digits.at(0) - '0' % 2 != 0);
}

BigInteger& BigInteger::operator/=(const BigInteger& bi)
{
    if(bi == 0_bi)
    {
        throw std::runtime_error("Division by zero");
    }
    if(lessThan(bi))
    {
        *this = 0_bi;
        return *this;
    }
    else if(*this == bi)
    {
        *this = 1_bi;
        return *this;
    }
    bool outSign = sign != bi.sign;
    size_t i, resInd = 0, num;
    std::vector<int> res(digits.size(), 0);
    BigInteger t(0);

    for(i = digits.size() - 1; (t * 10_bi + \
           BigInteger(digits[i] - '0')).lessThan(bi); --i)
    {
        t = t * 10_bi + BigInteger(digits[i] - '0');
    }

    for(; i != size_t(-1); --i)
    {
        t = t * 10_bi + BigInteger(digits[i] - '0');
        for(num = 9; (bi * BigInteger(num)).abs() > t; --num);
        t -= bi * BigInteger(num);
        res[resInd++] = num;
    }

    for(i = 0; i != resInd; ++i)
    {
        digits[i] = res[resInd - i - 1] + '0';
    }
    digits.resize(resInd);
    sign = outSign;
    return *this;
}

BigInteger BigInteger::operator/(const BigInteger& bi) const
{
    BigInteger res(*this);
    res /= bi;
    return res;
}

BigInteger BigInteger::abs() const
{
    BigInteger res(*this);
    if(sign == Sign::Negative)
        return -res;
    return res;
}

bool BigInteger::operator==(const BigInteger& bi) const
{
    return (digits == bi.digits)
        && (sign == bi.sign);
}

bool BigInteger::operator!=(const BigInteger& bi) const
{
    return !(*this == bi);
}

bool BigInteger::operator<(const BigInteger& bi) const
{
    bool asign = this->sign;
    bool bsign = bi.sign;
    if(asign == bsign)
    {
        if(asign)
        {
            return !lessThan(bi);
        }
        else
        {
            return lessThan(bi);
        }
    }
    return asign;
}

bool BigInteger::operator<=(const BigInteger& bi) const
{
    return (*this < bi) || (*this == bi);
}

bool BigInteger::operator>(const BigInteger& bi) const
{
    return !(*this <= bi);
}

bool BigInteger::operator>=(const BigInteger& bi) const
{
    return !(*this < bi);
}

bool BigInteger::lessThan(const BigInteger& subtrahend) const
{
    const std::string& a = this->digits;
    const std::string& b = subtrahend.digits;

    size_t len = a.size();

    if(len > b.size())
    {
        return false;
    }
    else if(len < b.size())
    {
        return true;
    }

    for(size_t i = len - 1; i != size_t(-1); --i)
    {
        if(a[i] < b[i])
        {
            return true;
        }
        else if(a[i] == b[i])
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}

std::ostream& operator<<(std::ostream& os, const BigInteger& bi)
{
    if(bi.sign)
    {
        os << '-';
    }
    for(size_t i = bi.digits.size() - 1; i != size_t(-1); --i)
    {
        os << bi.digits[i];
    }
    return os;
}

std::istream& operator>>(std::istream& in, BigInteger& bi)
{
    std::string s;
    in >> s;
    bi = BigInteger(s); // calls move assigment operator
    return in;
}

BigInteger operator ""_bi(const char* const s, size_t)
{
    return BigInteger(s);
}

BigInteger operator"" _bi(unsigned long long num)
{
    return BigInteger(num);
}
