# cppBigInteger
This is a very simple implementation of long arithmetic for signed integer.\
The implementation is not optimal and contains operations whose [asymptotic
complexity](https://en.wikipedia.org/wiki/Asymptotic_computational_complexity) is very high.
# Supported operations
- Addition
- Subtraction
- Multiplication
- Division 
- Exponentiation
- Comparison
# Usage
```
// factorial of 50 calculating
auto fact = 51_bi;
auto res = 1_bi;
for(auto i = 1_bi; i != fact; ++i)
{
    res *= i;
}

std::cout << fact - 1_bi <<  "! = " << res << '\n';
// outputs: 50! = 30414093201713378043612608166064768844377641568960512000000000000
```

see more in [main.cpp](main.cpp) file
