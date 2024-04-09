#include "BigInteger.h"

int main()
{
    std::cout << ++"--------+++---++-+-+432"_bi << '\n';
//    std::cout << 500_bi << " + " << -20_bi << " = " 
//        << 500_bi + +-20_bi << '\n';
//    auto fact = 5001_bi;
//    auto res = 1_bi;
//    for(auto i = 1_bi; i != fact; ++i)
//    {
//        res *= i;
//    }
//
//    std::cout << fact - 1_bi <<  "! = " << res << '\n';

    BigInteger a;
    BigInteger b;
    std::cout << "Enter first value: ";
    std::cin >> a;
    std::cout << "Enter second value: ";
    std::cin >> b;

//     std::cout << "a is " << a << '\n';
//     std::cout << "b is " << b << '\n';
//     std::cout << a << " - " << b << " = " << a - b << '\n';

    std::cout << "a is " << a << '\n';
    std::cout << "b is " << b << '\n';
    std::cout << a << " ^ " << b << " = " << (a ^ b) << '\n';

    
}
