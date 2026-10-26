#include <iostream>

int main () {
    // Try to get compile eror
    //int x{4.9};
    int x{4};
    std::cout << x << '\n';

    std::cout << "Bool: " << sizeof(bool) << '\n';
    std::cout << "char: " << sizeof(char) << '\n';
    std::cout << "int: " << sizeof(int) << '\n';
    std::cout << "unsigned int: " << sizeof(unsigned int) << '\n';
    std::cout << "double: " << sizeof(double) << '\n';
    std::cout << "long: " << sizeof(long) << '\n';

    constexpr int gravity {10};
    std::cout << "Gravitational Acceleration: " << gravity << '\n';

    double input{};
    std::cout << "Enter value of pi (2 decimals): ";
    std::cin >> input;
    const double pi{input};
    std::cout << "PI: " << pi << '\n';

    char letter{'A'};
    std::cout << "Letter:" <<  letter << '\n';
    std::cout << "The ASCII value of the above letter: " << static_cast<int>(letter) << '\n';

    return 0;
}