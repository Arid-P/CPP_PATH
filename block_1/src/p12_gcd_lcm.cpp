#include <iostream>

int compute_gcd(int a, int b) {
    while (b > 0) {
        int temp{b};
        b = a % b;
        a = temp;
    }

    return a;
}

int compute_lcm(int a, int b) {
    int gcd{compute_gcd(a, b)};
    return (a*b)/gcd;
}

int main() {
    std::cout << "--- Program 12: GCD & LCM Calculator ---" << '\n';

    int a{}, b{};
    std::cout << "Enter first integer (a): ";
    std::cin >> a;
    std::cout << "Enter second integer (b): ";
    std::cin >> b;

    // I am doing the if else only for asthetics and nothing else, so ignore
    if (a > b){
        int temp{a};
        a = b;
        b = temp;
    }
    // Finished
    
    int gcd{compute_gcd(a, b)}, lcm{compute_lcm(a, b)};

    std::cout << "For numbers " << a << " and " << b << ":" << '\n';
    std::cout << "- GCD (HCF): " << gcd << '\n';
    std::cout << "- LCM:       " << lcm << '\n';

    return 0;
}