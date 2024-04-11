#include "BigInteger.h"
#include <iomanip>

int main()
{
    // factorial calculating
    auto fact = 51_bi;
    auto res = 1_bi;
    for(auto i = 1_bi; i != fact; ++i)
    {
        res *= i;
    }

    std::cout << fact - 1_bi <<  "! = " << res << '\n';

    BigInteger a;
    BigInteger b;
    std::cout << "Enter first value: ";
    std::cin >> a;
    std::cout << "Enter second value: ";
    std::cin >> b;

    std::cout << "a is " << a << '\n';
    std::cout << "b is " << b << '\n';
    std::cout << a << " + " << b << " = " << (a + b) << '\n';
    std::cout << a << " - " << b << " = " << (a - b) << '\n';
    std::cout << a << " * " << b << " = " << (a * b) << '\n';
    std::cout << a << " / " << b << " = " << (a / b) << '\n';
    std::cout << a << " ^ " << b << " = " << (a ^ b) << '\n';

    // some random examples:
    std::cout << ++"--------+++---++-+-+432"_bi << '\n';
    std::cout << "a is " << a << ", ++a is " << ++a << '\n';
    std::cout << "a is " << a << ", b is " << b << ", a < b is " <<
        std::boolalpha << (a < b) << '\n';
    std::cout << "a is " << a << ", a /= 10 is " << (a /= 10_bi) << '\n';
    std::cout << "b is " << b << ", (500 * b - 1000) ^ 2 is " << 
        ((500_bi * b - 1000_bi) ^ 2_bi) << '\n';
}
