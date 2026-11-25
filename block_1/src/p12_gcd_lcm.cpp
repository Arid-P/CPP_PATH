#include <cstdint>
#include <iostream>

std::int64_t compute_gcd(std::int64_t a, std::int64_t b) {
    while (b > 0) {
        std::int64_t temp{b};
        b = a % b;
        a = temp;
    }

    return a;
}

std::int64_t compute_lcm(std::int64_t a, std::int64_t b) {
    std::int64_t gcd{compute_gcd(a, b)};

    if (gcd == 0) {
        std::cout << "The GCD comes to be 0 somehow." << '\n';
        return 0;
    }

    return (a / gcd) * b;
}

int main() {
    std::cout << "--- Program 12: GCD & LCM Calculator ---" << '\n';

    std::int64_t a{}, b{};
    std::cout << "Enter first integer (a): ";
    std::cin >> a;
    std::cout << "Enter second integer (b): ";
    std::cin >> b;

    if (a <= 0 || b <= 0) {
        std::cout << "The intgers must be positive integers!" << '\n';
        return 0;
    }

    // I am doing the if else only for asthetics and nothing else, so ignore
    if (a > b) {
        std::int64_t temp{a};
        a = b;
        b = temp;
    }
    // Finished

    std::int64_t gcd{compute_gcd(a, b)}, lcm{compute_lcm(a, b)};

    std::cout << "For numbers " << a << " and " << b << ":" << '\n';
    std::cout << "- GCD (HCF): " << gcd << '\n';
    std::cout << "- LCM:       " << lcm << '\n';

    return 0;
}