#include <cstdint>
#include <iostream>

int main() {
    // Overflow
    std::uint8_t u{250};
    int i{1};
    int limit{15};

    while (i < limit) {
        std::cout << "Value of u + " << i << " = " << static_cast<int>(u) << ";  ";
        u++;
        i++;
        std::cout << "Plain cout without casting: (" << u << ")" << '\n';
    }

    // The weird Arithmetic
    int a{-7}, b{3};
    std::cout << "Enter 2 nums separated by space: ";
    std::cin >> a >> b;

    std::cout << "a: " << a << " , b: " << b << '\n';
    std::cout << "a / b: " << a / b << '\n';
    std::cout << "a % b: " << a % b << '\n';

    return 0;
}